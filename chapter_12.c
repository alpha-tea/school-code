#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATA_MAX 256
#define MEM_MAX 1500
#define MAX_ROWS 12
#define MAX_COLUMNS 12
#define MAX_SIZE 12
/*
 *  Глава 12. матрицы произвольных размерностей и базовые алгоритмы интерпритации данных.
 */

enum mx_flags { mx_nop = 0x00, mx_ok = 0x00, mx_error = 0x01, mx_char = 0x02, mx_word = 0x04, mx_column = 0x08,
                mx_row = 0x10, mx_horiz = 0x20, mx_vert = 0x40, mx_all = 0x80, mx_rand = 0x100, mx_input = 0x200,
                mx_equal = 0x400, mx_less = 0x800, mx_more = 0x1000, mx_even = 0x2000, mx_odd = 0x4000
};

enum mx_actions {
    act_nop = 0x00, act_create = 0x01, act_copy = 0x02, act_move = 0x04, act_destroy = 0x08, act_assign = 0x10,
    act_neg = 0x20, act_add = 0x40, act_mul = 0x80, act_xchg = 0x100, act_seq = 0x200, act_rand = 0x400,
    act_roll = 0x800, act_min = 0x1000, act_max = 0x2000, act_uniq = 0x4000, act_data = 0x8000
};

// act data использовать данные

struct Matrix {
    void* matrix;
    unsigned int rows, columns, data_size;
    enum mx_flags flags;
};

//Статичные переменные для всей главы.
static int arithmetic_step = 1;       // Шаг арифметической прогрессии
static double geometric_ratio = 2.0;  // Знаменатель геометрической прогрессии
static unsigned int memory = MEM_MAX;
static char flags_info[DATA_MAX], actions_info[DATA_MAX];
static char* flags_names[] = { "nope_ok", "error", "char", "word",
    "column", "row", "horizontal", "vertical", "all", "random", "input",
    "equal", "less", "more", "even", "odd"
};

static const char char_first = 'A';
static const char char_last = 'Z';
static const short word_first = 1;
static const short word_last = 9;

static char* types_names[] = {
    "undefined", "char", "word"
};

static const unsigned short types_all = sizeof(types_names) / sizeof(char*);
static const unsigned short flags_all = sizeof(flags_names) / sizeof(char*);
static const unsigned int types_sizes[] = {0, sizeof(char), sizeof(short)};

static char* matrix_actions_name[] = {
    "nop", "create", "copy", "move", "destroy",
    "assign", "neg", "add", "mul", "xchg",
    "seq", "rand", "roll", "min", "max",
    "uniq", "data"
};

char* flags_text(enum mx_flags state, enum mx_actions action, unsigned int type);

unsigned int type_index(enum mx_flags type)
{// Вспомогательная функция для получения индекса типа
    ;
}

unsigned int is_types(enum mx_flags types)
{// Вспомогательная функция для проверки количества типов данных.
    return ((types & mx_char) != 0) + ((types & mx_word) != 0);
}

enum mx_flags is_type_ok(void* data, enum mx_flags type)
{
    if (data == NULL || is_types(type) != 1)
        return mx_error;
    switch (type & (mx_char | mx_word)) {
    case mx_char: {
        char value = *((char*)data);
        return (value >= char_first && value <= char_last) ? mx_ok : mx_error;
    }
    case mx_word: {
        short value = *((short*)data);
        return (value >= word_first && value <= word_last) ? mx_ok : mx_error;
    }
    default:
        return mx_error;
    }
}

const char* type_name(enum mx_flags type)
{
    for (unsigned int i = 1, flag = mx_char; i < types_all; ++i, flag <<= 1)
        if (type & flag)
            return types_names[i];
    return types_names[0];
}

unsigned int type_size(enum mx_flags type)
{
    for (unsigned int i = 1, flag = mx_char; i < types_all; ++i, flag <<= 1)
        if (type & flag)
            return types_sizes[i];
    return types_sizes[0];
}

char* type_text(char* text, void* data, enum mx_flags type)
{
    if (text == NULL || is_types(type) != 1) {
        printf("\nWarning type to text: incorrect arguments\n");
        return text;
    }
    memset(text, 0, DATA_MAX);
    switch (type & (mx_char | mx_word)) {
    case mx_char:                                           // Интервал
        text[0] = (data != NULL) ? *((char*)data) : ' ';
        break;
    case mx_word:
        sprintf_s(text, DATA_MAX, "%+hd", (data != NULL) ? *(short*)data : 0);
        break;
    default:
        strcpy_s(text, DATA_MAX, "undefined");
    }
    return text;
}

enum mx_flags type_compare(void* left, void* right, enum mx_flags type)
{// Сравнение данных в соответствие заданному типу, проверки только на NULL.
    // Функция дополнительная, возвращаем <, ==, > - левый операнд меньше, равен или больше операнда справа.
    if (left == NULL || right == NULL || is_types(type) != 1) {
        printf("\nWarning type compare, some arguments maybe incorrect;\n");
        return mx_error;
    }
    switch (type & (mx_char | mx_word)) {
    case mx_char:
        if (*((char*)left) > *((char*)right))
            return mx_more;
        else if (*((char*)left) < *((char*)right))
            return mx_less;
        else
            return mx_equal;
    case mx_word:
        if (*((short*)left) > *((short*)right))
            return mx_more;
        else if (*((short*)left) < *((short*)right))
            return mx_less;
        else
            return mx_equal;
    default:
        printf("\nWarning type to text, some arguments maybe incorrect;\n");
        return mx_error;
    }
}

enum mx_flags type_assign(void* left, void* right, enum mx_flags type)
{// Вспомогательный оператор присвоения значений или позже вынести в общий оператор.
    // switch, скопировать в left - right с учётом типа.
    if (left == NULL || right == NULL || is_types(type) != 1) {
        printf("\nWarning type to assign types, some arguments maybe incorrect;\n");
        return mx_error;
    }
    switch (type & (mx_char | mx_word)) {
    case mx_char:
        *((char*)left) = *((char*)right);
        break;
    case mx_word:
        *((short*)left) = *((short*)right);
        break;
    default:
        printf("\nWarning type to assign types, some arguments maybe incorrect;\n");
        return mx_error;
    }
    return mx_ok;
}

enum mx_flags type_xchg(void* left, void* right, enum mx_flags type)
{  // Обмен содержимого одного типа.
    if (left == NULL || right == NULL || is_types(type) != 1) {
        printf("\nWarning type xchg, some arguments maybe incorrect (left: %p, right: %p, type: %s);\n",
               left, right, flags_text(type, act_nop, 0));
        return mx_error;
    }
    switch (type & (mx_char | mx_word)) {
    case mx_char: {
        *((char*)left) ^= *((char*)right);
        *((char*)right) ^= *((char*)left);
        *((char*)left) ^= *((char*)right);
        break;
    }
    case mx_word: {
        short temp = *((short*)left);
        *((short*)left) = *((short*)right);
        *((short*)right) = temp;
        break;
    }
    default:
        printf("\nWarning type xchg: type of data is undefined;\n");
        return mx_error;
    }
    return mx_ok;
}

enum mx_flags type_neg(void* left, enum mx_flags type)
{   // вспомогательная функция построение дополнения до двух для объекта для заданного типа
    if (left == NULL || is_types(type) != 1 || is_type_ok(left, type) != mx_ok) {
        printf("\nWarning type neg: left (%p) or types (%s) incorrect arguments\n",
               left, flags_text(type, act_nop, 0));
        return mx_error;
    }
    switch (type & (mx_char | mx_word)) {
    case mx_char:                               // на завтра
        //*((char*)left) = -(*((char*)left));
        if (*((char*)left) != 'A')
            *((char*)left) = char_last - (*((char*)left) - char_first) + 1;
        //*((char*)left) = (char)((~(unsigned char)*((char*)left)) + 1);
        break;
    case mx_word:
        if (*((short*)left) < 0 && *((short*)left) == SHRT_MIN)
            printf("\nWarning type neg: word (%hd) is out of range(%hd %hd);\n",
                   *((short*)left), SHRT_MIN, SHRT_MAX);
        *((short*)left) = -(*((short*)left));
        break;
    default:
        printf("\nWarning type neg: type of data is undefined;\n");
        return mx_error;
    }
    return mx_ok;
}

enum mx_flags type_add(void* left, void* right, enum mx_flags type)
{// Сложение элементов с учётом типа.
    if (left == NULL || right == NULL || is_types(type) != 1
        || is_type_ok(left, type) != mx_ok || is_type_ok(right, type) != mx_ok) {
        printf("\nError type add: left (%p) right(%p) or type(%s) is incorrect;\n",
               left, right, flags_text(type, act_nop, 0));
        return mx_error;
    }
    switch (type & (mx_char | mx_word)) {
    case mx_char:
        *((char*)left) += (*((char*)right) - char_first);
        if (*((char*)left) < char_first || *((char*)left) > char_last) {
            *((char*)left) = ((*((char*)left) - char_first) % (char_last - char_first + 1));
            *((char*)left) += (*((char*)left) >= 0) ? char_first : char_last;
        }
        break;
    case mx_word:                                           // возможно предупреждение
        *((short*)left) += *((short*)right);
        break;
    default:
        printf("\ntype add warning: type is undefined;\n");
        return mx_error;
    }
    return mx_ok;
}

enum mx_flags is_correct(struct Matrix* obj)
{//Функция проверки структуры объекта на корректность. Работает тихо!!
    if (obj == NULL)
        return mx_error;
    if ((obj->data_size > 0 && (obj->matrix == NULL || obj->rows == 0 || obj->columns == 0 ||
                                is_types(obj->flags) != 1)) ||
        (obj->data_size == 0 && (obj->matrix != NULL || obj->rows > 0 || obj->columns > 0 ||
                                 is_types(obj->flags) != 0))) {
        return mx_error;
    }
    return mx_ok;
}

enum mx_flags type_mul(void* left, void* right, enum mx_flags type)
{
    if (left == NULL || right == NULL || is_types(type) != 1
        || is_type_ok(left, type) != mx_ok || is_type_ok(right, type) != mx_ok) {
        printf("\nError type mul: left (%p) right(%p) or type(%s) is incorrect;\n",
               left, right, flags_text(type, act_nop, 0));
        return mx_error;
    }
    switch (type & (mx_char | mx_word)) {
    case mx_char:                                           // подумать над пределами
        *((char*)left) = (*((char*)left) - char_first) * (*((char*)right) - char_first) + char_first;
        if (*((char*)left) < char_first || *((char*)left) > char_last) {
            *((char*)left) = ((*((char*)left) - char_first) % (char_last - char_first + 1));
            *((char*)left) += (*((char*)left) >= 0) ? char_first : char_last;
        }
        break;
    case mx_word:
        if ((*((short*)left) == SHRT_MIN && *((short*)right) == -1) ||
            (*((short*)left) == -1 && *((short*)right) == SHRT_MIN))
            printf("\nWarning type mul: left or right may be out of range(%hd %hd);\n",
                   SHRT_MIN, SHRT_MAX);
        //printf("!!! %d %d;\n", *((short*)left), *((short*)right));
        *((short*)left) *= *((short*)right);
        break;
    default:
        printf("\ntype mul warning: type is undefined;\n");
        return mx_error;
    }
    return mx_ok;
}

unsigned int size(struct Matrix* obj)
{//Вычисляем количество элементов в матрице (rows * columns)
    if (is_correct(obj) != mx_ok)
        return 0;
    return (unsigned int)(obj->rows * obj->columns);
}

void* linear(struct Matrix* obj, unsigned int row, unsigned int col)
{// Возвращает линейный адрес смещения в байтах от старта матрицы до заданных строки и столбца.
    if (is_correct(obj) != mx_ok || size(obj) == 0 || row >= obj->rows || col >= obj->columns) {
        printf("\nLinear warning: linear offset (%p) size (%hu) rows (%hu) columns (%hu);\n",
               obj, size(obj), row, col);
        return NULL;
    }
    return &(((char*)obj->matrix)[(row * obj->columns + col) * type_size(obj->flags)]);
}

char* flags_text(enum mx_flags state, enum mx_actions action, unsigned int type)
{//Возвращает в виде текстовой строки все флаги, без доп символов, в статичную переменную.  type, 0 - флаги, иначе actions
    char* info = (type == 0) ? flags_info : actions_info;
    info[0] = '\0';
    // Определяем параметры в зависимости от типа
    unsigned int* value = (type == 0) ? (unsigned int*)&state: (unsigned int*)&action;
    char** names = (type == 0) ? flags_names : matrix_actions_name;
    if (*value != mx_nop && *value != act_nop) {
        for (unsigned int flag_bit = 1, flag_idx = 1; flag_bit != 0; flag_idx++, flag_bit <<= 1) {
            if (*value & flag_bit) {
                if (info[0] != '\0')
                    strncat_s(info, DATA_MAX, " ", 1);                  // Уточнить в справочнике
                strncat_s(info, DATA_MAX, names[flag_idx], strlen(names[flag_idx]));
            }
        }
    } else
        strncat_s(info, DATA_MAX, names[mx_nop], strlen(names[mx_nop]));
    return info;
}

enum mx_flags info(struct Matrix* obj, unsigned int row, unsigned int col, enum mx_flags type)
{//Общая информация о матрице, в статичную строку без доп символов.
    if (is_correct(obj) != mx_ok || ((type & mx_row) && row >= obj->rows) ||
        ((type & mx_column) && col >= obj->columns)) {
        printf("Error info: matrix (%p) incorret, (%u %u) out of range, flags (%s);/n",
               obj, row, col, flags_text(type, act_nop, 0));
        return mx_error;
    }
    printf("Matrix info (%p), rows and columns (%ux%u) and flags (%s)",
           obj, obj->rows, obj->columns, flags_text(obj->flags, act_nop, 0));
    printf("\n%s", (obj->matrix == NULL) ? "unallocated" : "allocated");
    if (obj->matrix == NULL || obj->rows == 0 || obj->columns == 0) {
        printf("\n");
        return mx_error;
    }
    printf(" address of data (%p) and data size = %u bytes;\n", obj->matrix, obj->data_size);
    char add_data[DATA_MAX], mul_data[DATA_MAX];
    for (unsigned int i = 0; i < type_size(obj->flags); ++i) {
        switch (obj->flags & (mx_char | mx_word)) {             // сделать красивее
        case mx_char:
            add_data[i] = char_first;
            mul_data[i] = char_first + 1;
            break;
        case mx_word:
            ((short*)add_data)[i] = 0;
            ((short*)mul_data)[i] = 1;
            break;
        default:
            break;
        }
    }
    unsigned int start_row = (type & mx_row) ? row : 0, end_row = (type & mx_row) ? row : obj->rows - 1;
    unsigned int start_col = (type & mx_column) ? col : 0,
        end_col = (type & mx_column) ? col : obj->columns - 1;
    unsigned int count = 0;
    for (unsigned int i = start_row; i <= end_row; i++) {
        if (((type & mx_even & mx_row) && (i % 2 == 0)) ||
            (((type & mx_odd & mx_row) && (i % 2 == 1))))
            continue;
        for (unsigned int j = start_col; j <= end_col; j++) {
            if (((type & mx_even & mx_column) && (i % 2 == 0)) ||
                (((type & mx_odd & mx_column) && (i % 2 == 1))))
                continue;
            type_add(&add_data, linear(obj, i, j), obj->flags);
            type_mul(&mul_data, linear(obj, i, j), obj->flags);
            count++;
        }
    }
    char avr_c = ((*(char*)add_data) - char_first) / count + char_first;
    char gvr_c = ((*(char*)mul_data) - char_first) / count + char_first;
    short avr_w = (*(short*)add_data) / count;
    short gvr_w = (*(short*)mul_data) / count;
    if (type & mx_char)
        printf("Sum of chars and int: %hhd(%c), elements %hhu, avr is '%c', gvr is '%c', prod %c;\n",
               *(char*)add_data, *(char*)add_data, count, avr_c, gvr_c, (*(char*)mul_data));
    if (type & mx_word)
        printf("Sum of short and int: %hd, elements %hhu, avr is '%hd', gvr is '%hd', prod %hd;\n",
               *(short*)add_data, count, avr_w, gvr_w, *(short*)mul_data);
    return mx_ok;
}

enum mx_flags create(struct Matrix* obj, unsigned int rows, unsigned int columns,
                     void* data, enum mx_flags type)
{// Создание и инициализация матрицы с выделением динамической памяти под заданный тип элемента.
    // Возваращем ошибку, если не достаточно модельной памяти или флаги не верны. Данные по умолчанию нули или пробелы.
    /*
  если data - NULL, значит заполнить значением по умолчанию пробелом или нулем. А если флаг random поднят,
  то случайными значениями с учетом random_max статичной переменной, а буквы просто по алфавиту
  */
    if (is_correct(obj) != mx_ok || obj->data_size > 0 || rows > MAX_ROWS || columns > MAX_COLUMNS
        || rows == 0 || columns == 0 || is_types(type) != 1) {
        printf("\nerror create matrix: [%p] with flags '%s' or sizes(%u,%u) are incorrect\n",
               obj, flags_text(obj->flags, act_nop, 0), rows, columns);
        return mx_error;
    }
    unsigned int req_mem = rows * columns * type_size(type);
    char init_char = (data != NULL) ? *(char*)data : char_first;
    char init_text[DATA_MAX], data_text[DATA_MAX];
    short init_word = (data != NULL) ? *(short*)data : 0;
    type_text(data_text, data, type);
    sprintf_s(init_text, DATA_MAX, "'%s'(%s)", type_name(type), data_text);
    //printf("Data type: %s (%u bytes/element)\n", type_name, element_size);
    if (req_mem > memory) {
        printf("\nerror create matrix: not enough memory: %d bytes, available: %d bytes\n",
               req_mem, memory);
        return mx_error;
    }
    if ((obj->matrix = malloc(req_mem)) == NULL) {
        printf("error: Memory allocation failed\n");
        exit(1);
    }
    printf("\nCreating matrix: [%p] sizes(%u,%u) - ok, initial value(%s) and flags (%s);\n",
           obj, rows, columns, init_text, flags_text(type, act_nop, 0));
    obj->rows = rows; obj->columns = columns; obj->data_size = req_mem;
    obj->flags = type & (mx_char | mx_word);
    for (unsigned int i = 0; i < rows * columns; ++i) {         // next var. - assign
        if (type & mx_input) {
            printf("Input (%u,%u) element: ", i / columns, i % columns);
            scanf("%s", init_text);
        }
        switch (type & (mx_char | mx_word)) {
        case mx_char:
            if (type & mx_rand)
                init_char = char_first + rand() % (char_last - char_first + 1);
            else if (type & mx_input)
                init_char = init_text[0];
            ((char*)obj->matrix)[i] = init_char;
            break;
        case mx_word:
            if (type & mx_rand)
                init_word = word_first + rand() % (word_last - word_first + 1);
            else if (type & mx_input)
                init_word = init_text[0];
            ((short*)obj->matrix)[i] = init_word;
            break;
        default:
            printf("create warning: type of data undefined\n");
        }
    }
    memory -= req_mem;
    printf("Matrix created, sizes(%u,%u), %u bytes allocated, remaining memory: %u bytes\n",
           rows, columns, obj->data_size, memory);
    return mx_ok;
}

enum mx_flags mx_copy(struct Matrix* dst, struct Matrix* src,
                      unsigned int row_first, unsigned int col_first,
                      unsigned int row_last, unsigned int col_last)
{// Копирование части матрицы из заданной области                           // ! Испольщовать create  При копировании использовать реинтерпритацию данных (указатели).
    //Дополнительно осуществить копирование участками памяти.
    if (is_correct(src) != mx_ok || is_correct(dst) != mx_ok || size(dst) || !size(src)) {
        printf("error copy: from [%p] to [%p] or incorrect sizes\n", src, dst);
        return mx_error;
    }
    if (row_first >= src->rows || row_last >= src->rows ||
        col_first >= src->columns || col_last >= src->columns ||
        row_first > row_last || col_first > col_last) {
        printf("error copy: coordinates out of bounds\n");
        printf("Source: %dx%d, requested: [%d,%d]-[%d,%d]\n",
               src->rows, src->columns, row_first, col_first, row_last, col_last);
        return mx_error;
    }
    unsigned int rows_new = row_last - row_first + 1, cols_new = col_last - col_first + 1;
    printf("\nMatrix copy from [%p] to [%p], size %u, copying area: [%u,%u]-[%u,%u] (%ux%u), flags '%s'\n",
           src, dst, size(src), row_first, col_first, row_last, col_last, rows_new, cols_new,
           flags_text(src->flags, act_nop, 0));
    if ((create(dst, rows_new, cols_new, NULL, src->flags)) != mx_ok) {
        printf("error copy: failed to create destination matrix\n");
        return mx_error;
    }
    dst->flags = src->flags;
    for (unsigned int i = 0; i < rows_new; i++)
        for (unsigned int j = 0; j < cols_new; j++)
            type_assign(linear(dst, i, j), linear(src, row_first + i, col_first + j), src->flags);
    printf("Copy completed successfully! Memory: %u bytes\n", memory);
    return mx_ok;
}

enum mx_flags destroy(struct Matrix* obj)
{
    if (is_correct(obj) != mx_ok || size(obj) == 0) {
        printf("\nerror destroy: invalid matrix [%p]\n", obj);
        return mx_error;
    }
    memory += obj->data_size;
    printf("\nDestroy matrix: [%p], free %u elements and %u bytes, available memory %u;\n",
           obj, size(obj), obj->data_size, memory);
    free(obj->matrix);
    obj->matrix = NULL;
    obj->rows = obj->columns = obj->data_size = 0;
    obj->flags = mx_nop;
    return mx_ok;
}

enum mx_flags move(struct Matrix** dst, struct Matrix** src)
{// Перемещение структуры матрицы но без перемещения элементов в динамической памяти. Занулить заголовок src но не удалять данные.
    if (dst == NULL || src == NULL) {
        printf("\nerror move: adresses [%p] [%p] are NULL\n", dst, src);
        return mx_error;
    }
    if (is_correct(*src) != mx_ok || is_correct(*dst) != mx_ok || size(*src) == 0 || size(*dst) != 0) {
        printf("\nerror move: source matrix [%p] is NULL or invalid\n", *src);
        return mx_error;
    }
    (*dst)->matrix = (*src)->matrix;
    (*dst)->data_size = (*src)->data_size;
    (*dst)->columns = (*src)->columns;
    (*dst)->rows = (*src)->rows;
    (*dst)->flags = (*src)->flags;
    (*src)->matrix = NULL;
    (*src)->data_size = (*src)->columns = (*src)->rows = 0;
    (*src)->flags = mx_nop;
    printf("\nMatrix move from [%p] to [%p], data size %u moved, source structure cleared;\n\n",
           src, dst, (*dst)->data_size);
    return mx_ok;
}

void print(struct Matrix* obj, unsigned int row, unsigned int column, enum mx_flags style)
{// Вывод на экран всей матрицы или её части по заданному стилю.                        // Исправить вывод short и использовать вспомогательные функции.
    printf("\nMatrix print\n");
    if (is_correct(obj) != mx_ok) {
        printf("error: Invalid matrix \n");
        return;
    }
    printf("Print maxtrix...");
    if (((style & mx_row) && row >= obj->rows) ||
        ((style & mx_column) && column >= obj->columns)) {
        printf("error: Coordinates [%u, %u] out of bounds for matrix size %ux%u\n",
               row, column, obj->rows, obj->columns);
        return;
    }
    printf("Printing matrix %dx%d with style [%s]\n", obj->rows, obj->columns, flags_text(style, 0, 0));
    unsigned int start_row = 0, end_row = obj->rows;
    unsigned int start_col = 0, end_col = obj->columns;
    start_row = (style & mx_row) ? row : start_row;
    end_row = (style & mx_row) ? row + 1 : end_row;
    start_col = (style & mx_column) ? column : start_col;
    end_col = (style & mx_column) ? column + 1 : end_col;
    for (unsigned int i = start_row; i < end_row; i++) {
        for (unsigned int j = start_col; j < end_col; j++) {
            void* lin = linear(obj, i, j);
            if (obj->flags & mx_char)
                printf("%c ", *((char*)lin));
            else if (obj->flags & mx_word)
                printf("%hu ", ((short*)obj->matrix)[i * obj->columns + j]);
        }
        printf("\n");
    }
    printf("\n");
}

int is_element_zero(struct Matrix* obj, unsigned int index) {           // убрать, реализация в compact
    if (obj->flags & mx_char)
        return ((char*)obj->matrix)[index] == ' ';
    if (obj->flags & mx_word)
        return ((short*)obj->matrix)[index] == 0;
    return 1;
}

enum mx_flags compact(struct Matrix* obj, void* data)
{// Сжатие или уплотнение матрицы. Удаляются полнстью нулевые стоки или столбцы.
    printf("\nMatrix compact (refactored version)\n");
    if (is_correct(obj) != mx_ok || size(obj) == 0 || data == NULL) {
        printf("error compact: matrix(%p) empty or no object(%p);\n", obj, data);
        return mx_error;
    }
    unsigned int keep_r[MAX_SIZE],  keep_c[MAX_SIZE], new_rows = 0, new_cols = 0;
    for (unsigned int i = 0; i < MAX_SIZE; ++i)
        keep_r[i] = keep_c[i] = 0;                      // или memset
    for (unsigned int i = 0; i < obj->rows; i++)
        for (unsigned int j = 0; j < obj->columns; j++)
            if (type_compare(linear(obj, i, j), data, obj->flags) != mx_equal)
                keep_r[i] = keep_c[j] = 1;
    char txt[DATA_MAX];
    printf("Compacting matrix(%p), data(%s) from %ux%u to %ux%u, rows:", obj, type_text(txt, data, obj->flags),
           obj->rows, obj->columns, new_rows, new_cols);
    for (unsigned int i = 0; i < obj->rows; i++)
        if (keep_r[i])
            new_rows++;
        else
            printf(" %u", i);
    printf("; columns:");
    for (unsigned int j = 0; j < obj->columns; j++)
        if (keep_c[j])
            new_cols++;
        else
            printf(" %u", j);
    if (new_rows == 0 || new_cols == 0) {
        printf("; matrix is effectively empty after compaction, destroying.\n");
        return destroy(obj);
    }
    if (new_rows == obj->rows && new_cols == obj->columns) {
        printf("; no empty rows or columns found. Compact not needed.\n");
        return mx_ok;
    }
    struct Matrix temp = { NULL, 0, 0, 0, mx_nop }, *ptr_temp = &temp;
    printf("\n");
    if (create(&temp, new_rows, new_cols, NULL, obj->flags) != mx_ok)
        return mx_error;
    for (unsigned int i = 0, k = 0, j, l; i < obj->rows; i++) {
        if (!keep_r[i])
            continue;
        for (j = 0, l = 0; j < obj->columns; j++)
            if (keep_c[j])
                type_assign(linear(&temp, k, l++), linear(obj, i, j), obj->flags);
        k++;
    }
    destroy(obj);
    move(&obj, &ptr_temp);
    printf("Compact complete, new sizes %ux%u. Total free memory: %u\n", obj->rows, obj->columns, memory);
    return mx_ok;
}

enum mx_flags operator(struct Matrix* dst, struct Matrix* src, enum mx_actions action)
{// Исходная матрица должна сохраниться
    printf("\nMatrix operator: %s\n", flags_text(0, action, 1));
    if (is_correct(dst) != mx_ok) {
        printf("error: Invalid destination matrix\n");
        return is_correct(dst);
    }
if (action != act_neg && is_correct(src) != mx_ok) {
    printf("error: Invalid source matrix\n");
    return is_correct(src);
}
if ((action == act_add || action == act_mul || action == act_xchg) &&
    (dst->rows != src->rows || dst->columns != src->columns)) {
    printf("error: Matrix sizes must match for this operation\n");
    printf("Destination: %dx%d, Source: %dx%d\n",
           dst->rows, dst->columns, src->rows, src->columns);
    return mx_error;
}
if ((action == act_add || action == act_mul || action == act_xchg) &&
    dst->flags != src->flags) {
    printf("error: Matrix types must match for this operation\n");
    return mx_error;
}
switch (action) {
case act_neg: { // Отрицание элементов dst
    printf("Performing negation on destination matrix\n");
    unsigned int count = dst->rows * dst->columns;
    if (dst->flags & mx_char) {
        char* data = (char*)dst->matrix;
        for (unsigned int i = 0; i < count; i++)
            data[i] = -data[i];
    } else if (dst->flags & mx_word) {
        short* data = (short*)dst->matrix;
        for (unsigned int i = 0; i < count; i++)
            data[i] = -data[i];
    }
    break;
}
case act_add: { // Сложение матриц dst + src
    printf("Performing matrix addition\n");
    unsigned int count = dst->rows * dst->columns;
    if (dst->flags & mx_char) {
        char* dst_data = (char*)dst->matrix;
        char* src_data = (char*)src->matrix;
        for (unsigned int i = 0; i < count; i++)
            dst_data[i] += src_data[i];
    } else if (dst->flags & mx_word) {
        short* dst_data = (short*)dst->matrix;
        short* src_data = (short*)src->matrix;
        for (unsigned int i = 0; i < count; i++)
            dst_data[i] += src_data[i];
    }
    break;
}
case act_mul: { // Умножение матриц dst * src
    printf("Performing element-wise matrix multiplication\n");
    unsigned int count = dst->rows * dst->columns;
    if (dst->flags & mx_char) {
        char* dst_data = (char*)dst->matrix;
        char* src_data = (char*)src->matrix;
        for (unsigned int i = 0; i < count; i++)
            dst_data[i] *= src_data[i];
    } else if (dst->flags & mx_word) {
        short* dst_data = (short*)dst->matrix;
        short* src_data = (short*)src->matrix;
        for (unsigned int i = 0; i < count; i++)
            dst_data[i] *= src_data[i];
    }
    break;
}
case act_xchg: { // Обмен значениями между dst и src
    printf("Performing element exchange between matrices\n");
    unsigned int count = dst->rows * dst->columns;
    if (dst->flags & mx_char) {
        char* dst_data = (char*)dst->matrix;
        char* src_data = (char*)src->matrix;
        for (unsigned int i = 0; i < count; i++) {
            char temp = dst_data[i];
            dst_data[i] = src_data[i];
            src_data[i] = temp;
        }
    } else if (dst->flags & mx_word) {
        short* dst_data = (short*)dst->matrix;
        short* src_data = (short*)src->matrix;
        for (unsigned int i = 0; i < count; i++) {
            short temp = dst_data[i];
            dst_data[i] = src_data[i];
            src_data[i] = temp;
        }
    }
    break;
}
default:
    printf("error: Unsupported operation\n");
    return mx_error;
}
printf("Operation completed successfully\n");
return mx_ok;
}

unsigned int find(struct Matrix* dst, struct Matrix* src, void* data, unsigned int *row, unsigned int *col,
                  enum mx_actions action, enum mx_flags type)
{  // Поиск заданного элемента(ов) в исходной матрице и сохранение в пустой вектор назначения с учетом параметров.
    // Если флаг "все" включены, то поиск идет по всем возможным, иначе до первого найденного.
    // Если один элемент найден, то параметры row, col сохраняется позиция элемента при поиске всех - первый.
    // Функция работает тихо, только упоминание самой функции, объектов и аргументов.
    // Количество уникальных дополнительно по возможности, для теста матрицу брать небольшую.
    // Действие может быть только одно за каждый вызов.
    // Действия которые поддерживаются: equal, less, more, min, max, unique. Подробнее:
    //  - найти первый или все элементы равные, меньше или больше значения данных;
    //  - найти элементы мин-макс(имальные) с учетом флагов, вся матрица, строка или столбец и т.д.
    //  - найти все уникальные элементы(дополнительно).
    // Поддерживаемы флаги:
    // - all, поиск всех элементов удовлетворяющих условию, иначе только первого;
    // - row, column - только строка, столбец или отдельный элемент;
    // - vertical, horizontal - поиск в прямом или обратном порядке строк/столбцов;         сделать отдельные переменные с шагом +1/-1 строка столбец
    // - odd, even - нечетные или четные индексы;
    // Немного пожеланий, использовать один общий цикл для элементов и вспомогательные функции.
    if (is_correct(src) != mx_ok || size(src) == 0 || is_correct(dst) != mx_ok ||
        size(dst) != 0 || row == NULL || col == NULL) {
        printf("\nMatrix find error: invalid arguments. src must be valid and non-empty, dst must be empty, and pointers non-NULL.\n");
        printf("Received parameters:\nsrc matrix: [%p], size: %u\ndst matrix: [%p], size: %u\nrow ptr:\t[%p]\n"
               "col ptr:\t[%p]\naction:\t'%s'\ntype:\t'%s'\n", src, size(src), dst, size(dst), row, col,
               flags_text(mx_nop, action, 1), flags_text(type, act_nop, 0));
        return 0;
    }
    if ((action == act_data) && (data == NULL || (type & (mx_equal | mx_less | mx_more)) == 0)) {
        printf("\nMatrix find error: action 'data' requires valid data and a comparison type (equal, less, or more).\n");
        return 0;
    }
    printf("\nMatrix find: action '%s', type '%s' from src [%p] to dst [%p]\n",
           flags_text(mx_nop, action, 1), flags_text(type, act_nop, 0), src, dst);

    unsigned int start_r = 0, end_r = src->rows;
    unsigned int start_c = 0, end_c = src->columns;
    if (type & mx_row) {
        if (*row >= src->rows)
            return 0;
        start_r = *row;
        end_r = *row + 1;
    }
    if (type & mx_column) {
        if (*col >= src->columns)
            return 0;
        start_c = *col;
        end_c = *col + 1;
    }
    void* found_items[MAX_ROWS * MAX_COLUMNS];
    unsigned int found_count = 0;
    unsigned int total_elements = size(src);
    if (action == act_min || action == act_max) {
        void* extremum = NULL;
        for (unsigned int r = start_r; r < end_r; ++r) {
            for (unsigned int c = start_c; c < end_c; ++c) {
                void* current = linear(src, r, c);
                if (extremum == NULL) {
                    extremum = current;
                    continue;
                }
                enum mx_flags cmp_res = type_compare(current, extremum, src->flags);
                if ((action == act_min && cmp_res == mx_less) || (action == act_max && cmp_res == mx_more))
                    extremum = current;
            }
        }
        if (extremum == NULL)
            return 0;
        data = extremum;
        action = act_data;
        type |= mx_equal;
    }
    int stop_search = 0;

    int row_step = (type & mx_vert) ? -1 : 1;
    int col_step = (type & mx_horiz) ? -1 : 1;
    int r_loop_start = (type & mx_vert) ? end_r - 1 : start_r;

    for (int r = r_loop_start; (type & mx_vert) ? (r >= (int)start_r) : (r < (int)end_r); r += row_step) {
        int c_loop_start = (type & mx_horiz) ? end_c - 1 : start_c;
        for (int c = c_loop_start; (type & mx_horiz) ? (c >= (int)start_c) : (c < (int)end_c); c += col_step) {
            // Фильтрация по четности/нечетности индексов
            if ((type & mx_row) && (type & mx_even) && (r % 2 != 0))
                continue;
            if ((type & mx_row) && (type & mx_odd) && (r % 2 == 0))
                continue;
            if ((type & mx_column) && (type & mx_even) && (c % 2 != 0))
                continue;
            if ((type & mx_column) && (type & mx_odd) && (c % 2 == 0))
                continue;
            void* current_element = linear(src, r, c);
            int is_match = 0;
            switch (action) {
            case act_data: {
                enum mx_flags cmp = type_compare(current_element, data, src->flags);
                if (((type & mx_equal) && cmp == mx_equal) ||
                    ((type & mx_less) && cmp == mx_less) ||
                    ((type & mx_more) && cmp == mx_more)) {
                    is_match = 1;
                }
                break;
            }
            case act_uniq: {
                unsigned int occurrences = 0;
                for (unsigned int i = 0; i < total_elements; ++i) {
                    void* check_element = &((char*)src->matrix)[i * type_size(src->flags)];
                    if (type_compare(current_element, check_element, src->flags) == mx_equal)
                        occurrences++;
                }
                if (occurrences == 1)
                    is_match = 1;
                break;
            }
            default:
                break;
            }
            if (is_match) {
                if (found_count == 0) { // Сохраняем координаты первого найденного
                    *row = r;
                    *col = c;
                }
                found_items[found_count++] = current_element;
                if (!(type & mx_all)) { // Если не ищем все, выходим после первого
                    stop_search = 1;
                    break;
                }
            }
        }
        if (stop_search)
            break;
    }
    if (found_count > 0) {
        if (create(dst, 1, found_count, NULL, src->flags) == mx_ok)
            for (unsigned int i = 0; i < found_count; ++i)
                type_assign(linear(dst, 0, i), found_items[i], src->flags);
        else {
            printf("\nMatrix find error: failed to create destination matrix for results.\n");
            return 0;
        }
    }
    return found_count;
}

enum mx_flags insert(struct Matrix* dst, struct Matrix* src,
                     unsigned int row, unsigned int col, enum mx_flags type)
{// Вставка в матрицу назначения исходной матрицы. Размерности должны совпадать с учётом флагов и координат.
    if (is_correct(dst) != mx_ok || is_correct(src) != mx_ok || size(dst) == 0 || size(src) == 0 ||
        !(type ^ (mx_row | mx_column)) || type_name(dst->flags) != type_name(src->flags) ||
        ((type & mx_row) && (src->rows + dst->rows >= MAX_ROWS || src->columns != dst->columns)) ||
        ((type & mx_column) && (src->columns + dst->columns >= MAX_COLUMNS || src->rows != dst->rows))) {
        printf("\nerror insert matrix: to(%p) from(%p) sizes %ux%u, and start %ux%u and flags '%s';\n",
               dst, src, size(dst), size(dst), row, col, flags_text(type, act_nop, 0));
        return mx_error;
    }
    printf("\nInsert matrix: to(%p) from(%p) sizes %ux%u, and start %ux%u and flags '%s';\n",
           dst, src, size(dst), size(dst), row, col, flags_text(type, act_nop, 0));
    struct Matrix xchg = {NULL, 0, 0, 0, mx_nop}, *xchg_ptr = &xchg, *from_ptr = dst;
    unsigned int i, j, k = (type & mx_row) ? src->rows : 0, l = (type & mx_column) ? src->columns : 0,
        src_i = 0, src_j = 0, dst_i = 0, dst_j = 0, *from_i = &dst_i, *from_j = &dst_j;
    if (create(&xchg, dst->rows + k, dst->columns + l, NULL, src->flags) != mx_ok)
        return mx_error;
    for (i = 0; i < xchg.rows; ++i, (*from_i)++) {
        if ((type & mx_row)) {
            if (i >= row && i < row + k) {
                from_i = &src_i;
                from_ptr = src;
            } else {
                from_i = &dst_i;
                from_ptr = dst;
            }
        }
        for (j = 0, src_j = 0, dst_j = 0; j < xchg.columns; j++, (*from_j)++) {
            if ((type & mx_column)) {
                if (j >= col && j < col + l) {
                    from_j = &src_j;
                    from_ptr = src;
                } else {
                    from_j = &dst_j;
                    from_ptr = dst;
                }
            }
            char txt[DATA_MAX];
            printf("Assign from %u:%u to %u:%u, value '%s';\n", *from_i, *from_j, i, j,
                   type_text(txt, linear(from_ptr, *from_i, *from_j), from_ptr->flags));
            type_assign(linear(xchg_ptr, i, j), linear(from_ptr, *from_i, *from_j), xchg.flags);
        }
    }
    destroy(dst);
    move(&dst, &xchg_ptr);
    return mx_ok;
}

enum mx_flags cut(struct Matrix* dst, unsigned int first, unsigned int last, enum mx_flags type)
{// Удаление из матрица полных строк и/или стобцов, матрица назначения изменяет размеры.
    ;
}
unsigned int update(struct Matrix* dst, struct Matrix* data, unsigned int row,
                    unsigned int col, enum mx_actions action, enum mx_flags type)
{//Обновление матрицы, вовращает количество заменённых объектов. Обновляет по вектору data, если предумотренно параметрами.

}

enum mx_flags check_array_order(void* array, unsigned int count, enum mx_flags data_type)
{
    if (count <= 1)
        return mx_equal;
    int all_equal = 1;
    int increasing = 1;
    int decreasing = 1;
    for (unsigned int i = 1; i < count && (increasing || decreasing); i++) {
        void* prev = (char*)array + (i-1) * types_sizes[(data_type >> 7)];
        void* curr = (char*)array + i * types_sizes[(data_type >> 7)];
        enum mx_flags cmp = type_compare(prev, curr, data_type);
        if (cmp != mx_equal)
            all_equal = 0;
        if (cmp == mx_more)
            increasing = 0;
        if (cmp == mx_less)
            decreasing = 0;
    }
    if (all_equal)
        return mx_equal;
    if (increasing)
        return mx_less;
    if (decreasing)
        return mx_more;
    return mx_nop;
}

enum mx_flags is_order(struct Matrix* obj, enum mx_flags type)
{   // Определение упорядоченности матрицы/строки/столбца
    printf("\nMatrix order check: %s\n", flags_text(type, 0, 0));
    if (is_correct(obj) != mx_ok) {
        printf("error: Invalid matrix\n");
        return is_correct(obj);
    }
    if (size(obj) == 0) {
        printf("Matrix is empty\n");
        return mx_equal; // Пустая матрица считается упорядоченной
    }
    enum mx_flags data_type = obj->flags & (mx_char | mx_word);
    enum mx_flags result = mx_equal;
    int first_check = 1;
    int continue_checking = 1;
    if (type & mx_row) {
        printf("Checking row order\n");
        for (unsigned int i = 0; i < obj->rows && continue_checking; i++) {
            void* row_start = (char*)obj->matrix + i * obj->columns * types_sizes[(data_type >> 7)];
            enum mx_flags row_order = check_array_order(row_start, obj->columns, data_type);
            if (first_check) {
                result = row_order;
                first_check = 0;
            } else if (result != row_order) {
                result = mx_nop;
                continue_checking = 0;
            }
        }
        if (result != mx_nop) {
            printf("Rows are ordered: %s\n", flags_text(result, 0, 0));
            return result;
        }
    }
    // Проверка по столбцам
    if (type & mx_column) {
        printf("Checking column order\n");
        first_check = 1;
        continue_checking = 1;
        unsigned int element_size = types_sizes[(data_type >> 7)];
        void* column_data = malloc(obj->rows * element_size);
        if (column_data == NULL) {
            printf("error: Memory allocation failed for column check\n");
            return mx_error;
        }
        for (unsigned int j = 0; j < obj->columns && continue_checking; j++) {
            // Собираем столбец j во временный массив
            for (unsigned int i = 0; i < obj->rows; i++) {
                void* src = (char*)obj->matrix + (i * obj->columns + j) * element_size;
                void* dst = (char*)column_data + i * element_size;
                memcpy(dst, src, element_size);
            }
            enum mx_flags col_order = check_array_order(column_data, obj->rows, data_type);
            if (first_check) {
                result = col_order;
                first_check = 0;
            } else if (result != col_order) {
                result = mx_nop;
                continue_checking = 0;
            }
        }
        free(column_data);
        if (result != mx_nop) {
            printf("Columns are ordered: %s\n", flags_text(result, 0, 0));
            return result;
        }
    }
    if (!(type & mx_row) && !(type & mx_column)) {
        printf("Checking entire matrix as linear array\n");
        result = check_array_order(obj->matrix, obj->rows * obj->columns, data_type);
        if (result != mx_nop) {
            printf("Matrix is ordered: %s\n", flags_text(result, 0, 0));
            return result;
        }
    }
    printf("Matrix is not ordered\n");
    return mx_nop;
}

void chapter_12()
{
    /*
        find
        insert и cut по возможности
        update
    */
    srand((unsigned int)time(NULL));
    printf("Chapter 12;\n");
    printf("\nMain data structure of 'Matrix' about matrix, size %u bytes.\n", (unsigned int)sizeof(struct Matrix));
    printf("Field:\t\tOffset:\tType:\tSize:\tComment:\n");
    printf("matrix\t\t%u\taddress\t%u\tpointer to dynamic array of matrix elements.\n",
           (unsigned int)offsetof(struct Matrix, matrix), (unsigned int)sizeof(void*));
    printf("rows\t\t%u\tuint\t%u\tnumber of rows in the matrix.\n",
           (unsigned int)offsetof(struct Matrix, rows), (unsigned int)sizeof(unsigned int));
    printf("columns\t\t%u\tuint\t%u\tnumber of columns in the matrix.\n",
           (unsigned int)offsetof(struct Matrix, columns), (unsigned int)sizeof(unsigned int));
    printf("data_size\t%u\tuint\t%u\ttotal size of matrix data in bytes.\n",
           (unsigned int)offsetof(struct Matrix, data_size), (unsigned int)sizeof(unsigned int));
    printf("flags\t\t%u\tbits\t%u\tmatrix type and status flags.\n",
           (unsigned int)offsetof(struct Matrix, flags), (unsigned int)sizeof(enum mx_flags));
    printf("\n");
    struct Matrix matrix_a = {NULL, 0, 0, 0, mx_nop};
    struct Matrix matrix_b = {NULL, 0, 0, 0, mx_nop};
    struct Matrix matrix_c = {NULL, 0, 0, 0, mx_nop};
    struct Matrix* ptr_a = &matrix_a;
    struct Matrix* ptr_b = &matrix_b;
    struct Matrix* ptr_c = &matrix_c;

    //printf("type size char %u, word %u;\n", type_size(mx_char), type_size(mx_word));
    //return;
    //printf("(%s)", flags_text(mx_row | mx_err_mem | mx_ok, act_nop, 0));
    //short data[1][2] = {{1,2}};
    //short (*ptr)[][2] = &data;
    //printf("%hd\n", (*ptr)[0][1]);
    //return;
    // ! Тестирование всё так в норме, но можно result держать как одну и ту же переменную.
    // Что еще можно потестировать:
    // - попытаться создать матрицу с неверными размерами и потестировать ошибку;
    // - скопировать не только всю матрицу, но и отдельный элемент;
    // - попытаться переместить матрицу в занятую матрицу, после удалить объект назначения и снова;
    // - в функции печати вывести полную матрицу, строку, столбец и отдельный элемент;
    // - ну и может что-то еще придумаем... :)

    printf("Function:\tLeft:\tRight:\tFlags:\tResult:\t\tComment:\n");
    printf("----------------------------------------------------------------------------\n");

    char data_text[DATA_MAX] = {'D', 'E', 'X'}, text[DATA_MAX];
    short data_short[DATA_MAX] = {1, 2, 3, 4, 5};

    printf("is_types\t-\t-\t%s\t%u\t\tTypes counter in flags\n",
           flags_text(mx_char, 0, 0), is_types(mx_char));
    printf("is_type_ok\t%c\t-\t%s\t", data_text[0], flags_text(mx_char, 0, 0));
    printf("%s\t\tData in valid range\n", flags_text(is_type_ok(&data_text[0], mx_char), 0, 0));
    printf("type_name\t-\t-\t%s\t%s\t\tGet type name\n",
           flags_text(mx_word, 0, 0), type_name(mx_word));
    printf("type_size\t-\t-\t%s\t%u\t\tGet type size\n",
           flags_text(mx_char, 0, 0), type_size(mx_char));
    printf("type_text\t%c\t-\t%s\t%s\t\tConvert to text\n",
           data_text[0], flags_text(mx_char, 0, 0),
           type_text(text, &data_text[0], mx_char));
    printf("type_compare\t%c\t%c\t%s\t", data_text[0], data_text[1], flags_text(mx_char, 0, 0));
    printf("%s\t\tCompare values\n",
           flags_text(type_compare(&data_text[0], &data_text[1], mx_char), 0, 0));
    printf("type_assign\t%hd\t%hd\t%s\t", data_short[0], data_short[1], flags_text(mx_word, 0, 0));
    type_assign(&data_short[0], &data_short[1], mx_word);
    printf("%hd\t\tAssign value\n", data_short[0]);
    printf("type_neg\t%hd\t-\t%s\t", data_short[0], flags_text(mx_word, 0, 0));
    type_neg(&data_short[0], mx_word);
    printf("%hd\t\tNegate value\n", data_short[0]);
    printf("type_neg\t%c\t-\t%s\t", data_text[0], flags_text(mx_char, act_nop, 0));
    type_neg(&data_text[0], mx_char);
    printf("%c\t\tNegate value\n", data_text[0]);
    printf("type_add\t%c\t%c\t%s\t", data_text[1], data_text[2], flags_text(mx_char, 0, 0));
    type_add(&data_text[1], &data_text[2], mx_char);
    printf("%c\t\tAdd values\n", data_text[1]);
    printf("type_mul\t%c\t%c\t%s\t", data_text[0], data_text[1], flags_text(mx_char, 0, 0));
    type_mul(&data_text[0], &data_text[1], mx_char);
    printf("%c\t\tMultiply values\n", data_text[0]);
    printf("type_xchg\t%c\t%c\t%s\t", data_text[0], data_text[1], flags_text(mx_char, 0, 0));
    type_xchg(&data_text[0], &data_text[1], mx_char);
    printf("%c-%c\t\tXchg values\n", data_text[0], data_text[1]);
    printf("----------------------------------------------------------------------------\n");
    printf("Character range: '%c' to '%c'\n", char_first, char_last);
    printf("Word range: %hd to %hd\n", word_first, word_last);
    printf("\n=== MATRIX POINTERS STATUS ===\n");
    printf("Matrix A: %p (rows: %u, columns: %u)\n", ptr_a, ptr_a->rows, ptr_a->columns);
    printf("Matrix B: %p (rows: %u, columns: %u)\n", ptr_b, ptr_b->rows, ptr_b->columns);
    printf("Matrix C: %p (rows: %u, columns: %u)\n", ptr_c, ptr_c->rows, ptr_c->columns);
    printf("All matrices are initialized but not allocated yet.\n");
    // 1. Тест создания матрицы с неверными размерами
    printf("\n=== Test 1: Invalid matrix creation ===\n");
    enum mx_flags result = create(ptr_a, 0, 5, NULL, mx_char);  // Нулевые строки
    printf("Create 0x5 matrix: %s\n", flags_text(result, 0, 0));
    // 2. Создание матрицы A (3x4, тип char, случайные значения)
    printf("\n\n=== Test 2: Valid matrix creation ===\n");
    result = create(ptr_a, 3, 4, NULL, mx_char | mx_rand);
    if (result != mx_ok) {
        printf("Failed to create Matrix A\n");
        return;
    } else
        printf("create return result: '%s' and matrix has %u elements;\n", flags_text(result, act_nop, 0), size(ptr_a));
    print(ptr_a, 0, 0, mx_all);
    //print(ptr_a, 0, 0, mx_row);
    //print(ptr_a, 0, 0, mx_column);     // Проверить
    // 3. Создание матрицы B (2x2, тип short, нули)
    printf("\n\n=== Test 3: Second matrix creation ===\n");
    short data = 10;
    create(ptr_b, 2, 2, &data, mx_word);
    print(ptr_b, 0, 0, mx_all);

    printf("\n=== Linear test for word matrix ===\n");
    // Один тест - проверяем элемент (1,1)
    void* addr = linear(ptr_b, 1, 1);
    printf("linear(1,1): %p -> value=%hd (expected: 10)\n", addr, *((short*)addr));
    // 4. Копирование всей матрицы A в C
    printf("\n\n=== Test 4: Full matrix copy ===\n");
    print(ptr_a, 0, 0, mx_all);
    mx_copy(ptr_c, ptr_a, 0, 0, 2, 3);  // Всю матрицу 3x4
    print(ptr_c, 0, 0, mx_all);
    // 5. Копирование отдельного элемента
    printf("\n\n=== Test 5: Single element copy ===\n");
    destroy(ptr_c);  // Очищаем для нового теста
    print(ptr_a, 0, 0, mx_all);
    result = mx_copy(ptr_c, ptr_a, 1, 1, 1, 2);  // Один элемент
    ((char*)ptr_c->matrix)[0] = 'A';
    ((char*)ptr_c->matrix)[1] = 'C';
    print(ptr_c, 0, 0, mx_all);
    info(ptr_c, 1, 2, mx_char);
    print(ptr_b, 0, 0, mx_all);
    info(ptr_b, 0, 0, mx_word | mx_row | mx_even);
    // 6. Перемещение матрицы в занятую матрицу
    printf("=== Test 6: Move to occupied matrix ===\n");
    printf("Before move - Matrix B:\n");
    print(ptr_b, 0, 0, mx_all);
    printf("Before move - Matrix C:\n");
    print(ptr_c, 0, 0, mx_all);
    move(&ptr_b, &ptr_c);
    destroy(ptr_c);
    move(&ptr_c, &ptr_b);
    printf("Move B to C: %s\n", flags_text(result, 0, 0));
    printf("Matrix B:\n");
    print(ptr_b, 0, 0, mx_all);
    printf("Matrix C:\n");
    print(ptr_c, 0, 0, mx_all);

    printf("Source Matrix A (before copy):\n");
    print(ptr_a, 0, 0, mx_all);
    // Уничтожим C, чтобы подготовить его для копирования
    destroy(ptr_c);
    printf("\nCopying 2x2 sub-matrix from A[1,1] to A[2,2] into C...\n");
    result = mx_copy(ptr_c, ptr_a, 1, 1, 2, 2); // Копируем блок 2x2 из A
    if (result == mx_ok) {
        printf("Resulting Matrix C (after copy):\n");
        print(ptr_c, 0, 0, mx_all);
    } else {
        printf("Sub-matrix copy failed with result: %s\n", flags_text(result, 0, 0));
    }
    info(ptr_a, 0, 0, mx_all | mx_char);
    printf("\nInfo for row 1 of Matrix A:\n");
    info(ptr_a, 1, 0, mx_row | mx_char);
    printf("\nInfo for column 2 of Matrix A:\n");
    info(ptr_a, 0, 2, mx_column | mx_char);
    printf("\nInfo for odd-indexed columns in row 1 of Matrix A:\n");
    info(ptr_a, 1, 0, mx_row | mx_odd | mx_column | mx_char);

    struct Matrix matrix_result = {NULL, 0, 0, 0, mx_nop};
    struct Matrix* ptr_res = &matrix_result;
    unsigned int found_row = 0, found_col = 0;
    unsigned int count;
    *((char*)linear(ptr_a, 0, 1)) = 'X';
    *((char*)linear(ptr_a, 1, 2)) = 'Y';
    *((char*)linear(ptr_a, 2, 0)) = 'X';
    *((char*)linear(ptr_a, 2, 3)) = 'Z';
    printf("Matrix A (3x4) after modification:\n");
    print(ptr_a, 0, 0, mx_all);
    *((char*)linear(ptr_a, 0, 0)) = 'X';                // Переделать под update
    *((char*)linear(ptr_a, 0, 1)) = 'X';
    *((char*)linear(ptr_a, 0, 2)) = 'X';
    *((char*)linear(ptr_a, 0, 3)) = 'X';
    printf("Before compaction:\n");
    print(ptr_a, 0, 0, mx_all);
    result = compact(ptr_a, &data_text[2]);
    printf("Compaction result: %s\n", flags_text(result, 0, 0));
    print(ptr_a, 0, 0, mx_all);

    destroy(ptr_b);
    destroy(ptr_c);
    create(ptr_b, 1, 1, NULL, mx_rand | mx_word);
    create(ptr_c, 1, 1, NULL, mx_rand | mx_word);
    print(ptr_b, 0, 0, mx_all);
    print(ptr_c, 0, 0, mx_all);
    insert(ptr_b, ptr_c, 1, 0, mx_row);
    print(ptr_b, 0, 0, mx_all);
    insert(ptr_b, ptr_b, 0, 1, mx_column);
    print(ptr_b, 0, 0, mx_all);
    *((short*)linear(ptr_b, 0, 1)) = 1;
    *((short*)linear(ptr_b, 1, 1)) = 3;
    print(ptr_b, 0, 0, mx_all);
    insert(ptr_b, ptr_b, 1, 0, mx_row);
    print(ptr_b, 0, 0, mx_all);
    return;
    printf("\n=== Test 6.5: Find first 'X' in matrix A ===\n");
    char char_to_find = 'X';
    count = find(ptr_res, ptr_a, &char_to_find, &found_row, &found_col, act_data, mx_equal | mx_char);
    printf("Result: Found %u element(s). First occurrence at [%u, %u] (expected [0, 1]).\n", count, found_row, found_col);
    printf("Data found:\n");
    print(ptr_res, 0, 0, mx_all);
    destroy(ptr_res); // Очищаем результат для следующего теста

    return;
    // 7. Повторное создание и перемещение
    printf("=== Test 7: Recreate and move again ===\n");
    result = create(ptr_c, 2, 2, NULL, mx_char | mx_rand);
    if (result == mx_ok) {
        printf("Recreated Matrix C:\n");
        print(ptr_c, 0, 0, mx_all);

        result = move(&ptr_b, &ptr_c);
        printf("Second move C to B: %s\n", flags_text(result, 0, 0));
    }


    // 8. Расширенная печать
    printf("=== Test 8: Extended printing ===\n");
    printf("Matrix A remains:\n");
    print(ptr_a, 0, 0, mx_all);

    // Печать разных представлений
    print(ptr_a, 1, 0, mx_row);           // Строка 1
    print(ptr_a, 0, 2, mx_column);        // Столбец 2
    print(ptr_a, 2, 3, mx_row | mx_column); // Элемент [2][3]

    // Печать несуществующих элементов
    print(ptr_a, 5, 0, mx_row);           // Несуществующая строка
    print(ptr_a, 0, 5, mx_column);        // Несуществующий столбец

    // 9. Тест ввода с клавиатуры (закомментирован для автоматического тестирования)
    /*
    printf("=== Test 9: Keyboard input ===\n");
    destroy(ptr_c);
    result = create(ptr_c, 2, 2, NULL, mx_char | mx_input);
    if (result == mx_ok) {
        print(ptr_c, 0, 0, mx_all);
    }
    */
    // 11. Уничтожение матриц
    printf("=== Test 11: Cleanup ===\n");
    destroy(ptr_a);
    destroy(ptr_b);
    destroy(ptr_c);

    printf("Final memory check: %u bytes used, %u bytes free (total: %u bytes)\n",
           MEM_MAX - memory, memory, MEM_MAX);

    // 12. Тест уничтожения NULL матрицы                                    // с 11 вместе
    printf("=== Test 12: Destroy NULL matrix ===\n");
    destroy(NULL);
    return;
}
