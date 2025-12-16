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

enum mx_actions {                  // act_sort подумать
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
static const short word_first = 0;
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
        text[0] = (data != NULL) ? *((char*)data) : char_first;
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
        if (*((short*)left) != word_first)
            *((short*)left) = (word_last - (*((short*)left) - word_first) + 1);
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
    case mx_word:
        *((short*)left) += (*((short*)right) - word_first);
        if (*((short*)left) < word_first || *((short*)left) > word_last) {
            *((short*)left) = ((*((short*)left) - word_first) % (word_last - word_first + 1));
            *((short*)left) += (*((short*)left) >= 0) ? word_first : word_last;
        }
        break;
    default:
        printf("\ntype add warning: type is undefined;\n");
        return mx_error;
    }
    return mx_ok;
}

enum mx_flags type_rand(void* left, enum mx_flags type)
{ //  Генерация псевдослучайного значения с учётом типа данных и глобальныых ограничений
    if (left == NULL || is_types(type) != 1) {
        printf("\nWarning type rand: left (%p) or types (%s) incorrect arguments\n",
               left, flags_text(type, act_nop, 0));
        return mx_error;
    }
    switch (type & (mx_char | mx_word)) {
    case mx_char:
        *((char*)left) = char_first + rand() % (char_last - char_first + 1);
        break;
    case mx_word:
        *((short*)left) = word_first + rand() % (word_last - word_first + 1);
        break;
    default:
        printf("\nWarning type rand: type of data is undefined;\n");
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
    case mx_char:
        *((char*)left) = (*((char*)left) - char_first) * (*((char*)right) - char_first) + char_first;
        if (*((char*)left) < char_first || *((char*)left) > char_last) {
            *((char*)left) = ((*((char*)left) - char_first) % (char_last - char_first + 1));
            *((char*)left) += (*((char*)left) >= 0) ? char_first : char_last;
        }
        break;
    case mx_word:
        *((short*)left) = (*((short*)left) - word_first) * (*((short*)right) - word_first) + word_first;
        if (*((short*)left) < word_first || *((short*)left) > word_last) {
            *((short*)left) = ((*((short*)left) - word_first) % (word_last - word_first + 1));
            *((short*)left) += (*((short*)left) >= 0) ? word_first : word_last;
        }
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
                strncat_s(info, DATA_MAX - strlen(info), names[flag_idx], strlen(names[flag_idx]));
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
                type_rand(&init_char, type);
            else if (type & mx_input)
                init_char = init_text[0];
            ((char*)obj->matrix)[i] = init_char;
            break;
        case mx_word:
            if (type & mx_rand)
                type_rand(&init_word, type);
            else if (type & mx_input)
                init_word = atoi(init_text);
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
    char txt[DATA_MAX];
    void* found[MAX_COLUMNS];
    memset(txt, 0, DATA_MAX);
    memset(found, 0, MAX_COLUMNS);
    printf("\nMatrix find: action '%s', type '%s' from src [%p] to dst [%p], value = '%s'\n",
           flags_text(mx_nop, action, 1), flags_text(type, act_nop, 0), src, dst,
           type_text(txt, data, src->flags));
    if (((type & mx_row) && *row >= src->rows) || ((type & mx_column) && *col >= src->columns)) {
        printf("\nMatrix find error: start coordinates (%u,%u) out of bounds for matrix [%p] size %ux%u with flags '%s';\n",
               *row, *col, src, src->rows, src->columns, flags_text(type, act_nop, 0));
        return 0;
    }
    unsigned int start_row = (type & mx_row) ? *row : 0;
    unsigned int end_row = (type & mx_row) ? *row : src->rows - 1;
    unsigned int start_col = (type & mx_column) ? *col : 0;
    unsigned int end_col = (type & mx_column) ? *col : src->columns - 1;
    unsigned int i, j, m = 0, is_match = 0;
    int k = (type & mx_vert) ? -1 : 1, l = (type & mx_horiz) ? -1 : 1;
    if (type & mx_vert)
        type_xchg(&start_row, &end_row, mx_word);
    if (type & mx_horiz)
        type_xchg(&start_col, &end_col, mx_word);
    enum mx_flags search = action & (act_min | act_max);
    printf("\nrows and step: %u, %u, %d, columns and step: %u, %u, %d, %d;\n",
           start_row, end_row, k, start_col, end_col, l, search);
    for (i = start_row; (i != end_row + k) && ((type & mx_all) || (m == 0) || (search)); i += k) {
        if (((type & mx_even) && (i % 2 != 0)) || ((type & mx_odd) && (i % 2 == 0)))
            continue;
        for (j = start_col; (j != end_col + l) && ((type & mx_all) || (m == 0) || (search)); j += l) {
            if (((type & mx_even) && (j % 2 != 0)) || ((type & mx_odd) && (j % 2 == 0)))
                continue;
            void* current = linear(src, i, j);
            switch (action) {
            case act_data: {
                if (type_compare(current, data, src->flags) ==
                    (type & (mx_equal | mx_more | mx_less))) {
                    printf("Value found at (%u:%u) = '%s';\n", i, j,
                           type_text(txt, current, src->flags));
                    found[m++] = current;
                    is_match = 1;
                }
                break;
            }
            case act_min:
            case act_max: {
                if ((m == 0) ||
                    ((action == act_min) && (type_compare(current, found[0], src->flags) == mx_less)) ||
                    ((action == act_max) && (type_compare(current, found[0], src->flags) == mx_more))) {
                    printf("Value found at (%u:%u) = '%s';\n", i, j,
                           type_text(txt, current, src->flags));
                    found[0] = current; m = is_match = 1;
                }
                break;
            }
            case act_uniq: {
                struct Matrix uniq = {NULL, 0, 0, 0, mx_nop};
                unsigned int t_row = 0, t_col = 0;
                if (find(&uniq, src, current, &t_row, &t_col, act_data, mx_equal | mx_all) == 1) {
                    printf("Value uniq found at (%u:%u) = '%s', size of uniq vector %u;\n", i, j,
                           type_text(txt, current, src->flags), size(&uniq));
                    is_match = 1;
                    found[m++] = current;
                }
                destroy(&uniq);
                break;
            }
            default:
                printf("error find search: type of action undefined;\n");
                break;
            }
            if (m == MAX_COLUMNS) {
                printf("error find search: vector of elements is full, max %u;\n", MAX_COLUMNS);
                return 0;
            }
            if (is_match && m == 1) {
                *row = i;                                   // debug
                *col = j;
                is_match = 0;
            }
        }
    }
    printf("counter found = %u;\n", m);
    if ((action == act_min || action == act_max)) {
        if (type & mx_all) {
            printf("to find all max or min value, calling find again with 'data';\n");
            return find(dst, src, found[0], row, col, act_data, type | mx_equal);
        } else
            printf("Only one value '%s' max or min, just add it to destination;\n",
                   type_text(txt, found[0], src->flags));
    }
    if (create(dst, 1, m, NULL, src->flags) == mx_ok)
        for (i = 0; i < m; ++i)
            type_assign(linear(dst, 0, i), found[i], src->flags & (mx_char | mx_word));
    else
        printf("\nMatrix find error: failed to create destination matrix or empty;\n");
    return m;
}

enum mx_flags insert(struct Matrix* dst, struct Matrix* src,
                     unsigned int row, unsigned int col, enum mx_flags type)
{// Вставка в матрицу назначения исходной матрицы. Размерности должны совпадать с учётом флагов и координат.
    if (is_correct(dst) != mx_ok || is_correct(src) != mx_ok || size(dst) == 0 || size(src) == 0 ||
        !(type ^ (mx_row | mx_column)) || type_name(dst->flags) != type_name(src->flags) || // col и row проверить
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
            //char txt[DATA_MAX];
            //printf("Assign from %u:%u to %u:%u, value '%s';\n", *from_i, *from_j, i, j,
            //       type_text(txt, linear(from_ptr, *from_i, *from_j), from_ptr->flags));
            type_assign(linear(xchg_ptr, i, j), linear(from_ptr, *from_i, *from_j), xchg.flags);
        }
    }
    destroy(dst);
    move(&dst, &xchg_ptr);
    return mx_ok;
}

enum mx_flags cut(struct Matrix* dst, unsigned int first, unsigned int last, enum mx_flags type)
{// Удаление из матрица полных строк и/или стобцов, матрица назначения изменяет размеры.
    if (is_correct(dst) != mx_ok || size(dst) == 0 || first > last ||
        !(type ^ (mx_row | mx_column)) || ((type & mx_row) && last >= dst->rows) ||
        ((type & mx_column) && last >= dst->columns)) {
        printf("\nerror cut matrix: invalid arguments for matrix (%p), range [%u, %u], or flags '%s';\n",
               dst, first, last, flags_text(type, act_nop, 0));
        return mx_error;
    }
    unsigned int num_to_cut = last - first + 1;
    unsigned int new_rows = (type & mx_row) ? dst->rows - num_to_cut : dst->rows;
    unsigned int new_cols = (type & mx_column) ? dst->columns - num_to_cut : dst->columns;
    printf("\nCut matrix: from (%p), removing %u [%u to %u]. Old size %ux%u -> New size %ux%u\n",
           dst, num_to_cut, first, last, dst->rows, dst->columns, new_rows, new_cols);
    if (new_rows == 0 || new_cols == 0) {
        printf("Matrix is empty after cut, destroying.\n");
        return destroy(dst);
    }
    struct Matrix temp = { NULL, 0, 0, 0, mx_nop }, *ptr_temp = &temp;
    if (create(&temp, new_rows, new_cols, NULL, dst->flags) != mx_ok)
        return mx_error;
    unsigned int k = 0, l = 0, j = 0, i = 0;
    for (i = 0; i < dst->rows; ++i) {
        if (((type & mx_row) && (i >= first && i <= last)))
            continue;
        for (j = 0, l = 0; j < dst->columns; ++j)
            if (!((type & mx_column) && (j >= first && j <= last))) {
                //char data_txt[DATA_MAX];
                //printf("cut from (%u:%u) to (%u:%u), value '%s';\n", i, j, k, l,
                //       type_text(data_txt, linear(dst, i, j), dst->flags));
                type_assign(linear(&temp, k, l++), linear(dst, i, j), dst->flags);
            }
        k++;
    }
    destroy(dst);
    move(&dst, &ptr_temp);
    printf("Cut complete, new size %ux%u. Total free memory: %u\n", dst->rows, dst->columns, memory);
    return mx_ok;
}

// data - 1 строка и n столбцов вектор, если значения закончились то по кругу (по умолчанию)
enum mx_flags update(struct Matrix* dst, struct Matrix* src, void* data,
                     unsigned int row, unsigned int col,
                     enum mx_actions action, enum mx_flags type)
{//Обновление матрицы, элементов матрицы в соответствии с типом действия, флагами и вектором данных.
    // Из исходного вектора читаются данные для действия, а data - данные для работы с флагами. Типы данных матрицы и вектора должны совпадать.
    // Если размерности вектора не достаточно, то он зацикливается.
    // Функционал, действие всегда одно, а флаги отражают условия либо направления:
    // - замена значений элементов матрицы/строки/столбца на значение вектора или случайным значением(type_rand);
    // - арифметика(сложение умножение отрицание) со матрица/строками и столбцами;
    // - поменять элементы местами (act_xchg), матрица/строка/столбец и два флага вертикально/горизонтально или вместе;
    // - циклические сдвиги act_roll, флаги vert/horiz задают тип сдвига, mx_less или mx_more - направление
    // - арифметическая прогрессия задаётся в исходном векторе src (низ, верх, шаг)
    // - флаг mx_all, если установлен то все элементы иначе только первые элементы?
    if (is_correct(dst) != mx_ok || size(dst) == 0 ||
        ((type & mx_row) && row >= dst->rows) || ((type & mx_column) && col >= dst->columns) ||
        !(action & (act_assign | act_rand | act_xchg | act_add | act_mul | act_neg | act_roll | act_seq))) {
        printf("\nMatrix update error: invalid destination matrix [%p]\n", dst);
        return mx_error;
    }
    char data_txt[DATA_MAX];
    printf("\nMatrix update: action '%s', type '%s' on dst [%p], src vector [%p], rows %u, columns %u,"
           "data [%s]\n",
           flags_text(mx_nop, action, 1), flags_text(type, act_nop, 0), dst, src, row, col, type_text(data_txt, data, src->flags));
    if ((action & (act_assign | act_add | act_mul)) && (is_correct(src) != mx_ok || size(src) == 0 ||
                                                        type_name(dst->flags) != type_name(src->flags))) {
        printf("\nMatrix error update: type of action and source or type of matrix is incorrect;\n");
        return mx_error;
    }
    if ((type & (mx_equal | mx_less | mx_more)) && (data == NULL) && !(action & act_roll)) {
        printf("\nMatrix error update: extra check has no data;\n");
        return mx_error;
    }                           // Перепроверить условия
    if (action & (act_xchg) && (!(type & (mx_vert | mx_horiz)) || ((type & mx_horiz) && (type & mx_vert)) ||
                                ((type & mx_column) && (type & mx_horiz)) ||
                                ((type & mx_row) && (type & mx_vert)))) {
        printf("\nMatrix update error: cant xchg elements without flags or action and flags are incompatable;\n");
        return mx_error;
    }
    if (action & (act_roll) && (!(((type & mx_less) != 0) ^ ((type & mx_more) != 0)) ||
                                ((type & mx_horiz) && (type & mx_vert)))) {
        printf("\nMatrix update error: flags are incorrect, only one pair v/h and less/more at call;\n");
        return mx_error;
    }
    // if (action & (act_seq) && ()) {
    //     ;
    // }
    unsigned int start_r = (type & mx_row) ? row : 0;
    unsigned int end_r   = (type & mx_row) ? row : dst->rows - 1;
    unsigned int start_c = (type & mx_column) ? col : 0;
    unsigned int end_c   = (type & mx_column) ? col : dst->columns - 1;
    if (action & act_xchg) {
        if (type & mx_vert)
            end_r /= 2;
        if (type & mx_horiz)
            end_c /= 2;
    }
    unsigned int updates = 0, src_len = (src != NULL) ? size(src) : 0, src_idx = 0;
    int stop_processing = 0;
    // Для act_seq (арифметическая прогрессия)                                                 Использовать дополнительную матрицу.
    char seq_buff[DATA_MAX], txt[DATA_MAX];
    void* seq_curr = seq_buff;
    void* seq_end_val = NULL;
    void* seq_step_val = NULL;
    if (action == act_seq) {
        if (src_len < 3) {
            printf("Error update: act_seq requires src vector with [start, end, step].\n");
            return mx_error;
        }
        type_assign(seq_curr, linear(src, 0, 0), src->flags);
        seq_end_val = linear(src, 0, 1);
        seq_step_val = linear(src, 0, 2);
    }
    unsigned int i = 0, j = 0;
    for (i = start_r; i <= end_r; i++) {
        if (((type & mx_even) && (i % 2 != 0)) || ((type & mx_odd) && (i % 2 == 0)))
            continue;
        for (j = start_c; j <= end_c; j++) {
            if (((type & mx_even) && (j % 2 != 0)) || ((type & mx_odd) && (j % 2 == 0)))
                continue;
            void* dst_ptr = linear(dst, i, j);
            void* src_ptr = (src != NULL) ? linear(src, 0, src_idx % size(src)) : NULL;                   // Страшно
            printf("row %u, col %u, src %u, value at dst (%s); ", i, j, src_idx, type_text(txt, dst_ptr, src->flags));
            if (src != NULL)
                printf("source (%s); ", type_text(txt, src_ptr, src->flags));
            else
                printf("source has no data; ");
            // Фильтрация по data (если задан data и флаги сравнения)
            if (!(action & act_roll) && (type & (mx_equal | mx_less | mx_more))) {
                if (type_compare(dst_ptr, data, dst->flags) == (type & (mx_equal | mx_less | mx_more)))
                    printf("compare element (%s) is true, do action; ", data_txt);
                else {
                    printf("compare element (%s) is false, continue;\n", data_txt);
                    continue;
                }
            } else
                printf("No flags to compare elements, only action; ");
            switch (action) {                                               // add flags
            case act_assign:
                type_assign(dst_ptr, src_ptr, dst->flags);
                printf("Assign element from source and move to next cycle;\n");
                break;
            case act_rand:
                type_rand(dst_ptr, dst->flags);
                printf("Generate random element, usign matrix type;\n");
                break;
            case act_neg:
                type_neg(dst_ptr, dst->flags);
                printf("Neg element using type function;\n");
                break;
            case act_xchg: {
                // Зеркальный обмен относительно центра
                unsigned int t_r = (type & mx_vert) ? (dst->rows - 1 - i) : i;
                unsigned int t_c = (type & mx_horiz) ? (dst->columns - 1 - j) : j;
                type_xchg(dst_ptr, linear(dst, t_r, t_c), dst->flags);
                printf("Xchg elements within matrix, position %u-%u;\n", t_r, t_c);
                break;
            }
            case act_add:
                type_add(dst_ptr, src_ptr, dst->flags);
                printf("Add element usign source right value;\n");
                break;
            case act_mul:
                type_mul(dst_ptr, src_ptr, dst->flags);
                printf("Mul element usign source right value;\n");
                break;
            case act_seq:
                type_assign(dst_ptr, seq_curr, dst->flags);
                type_add(seq_curr, seq_step_val, dst->flags);
                if (type_compare(seq_curr, seq_end_val, dst->flags) == mx_more)
                    type_assign(seq_curr, linear(src, 0, 0), dst->flags);
                break;
            case act_roll: {
                // Корректировка границ для act_roll, чтобы не выйти за пределы массива при доступе к соседу
                if (((type & mx_vert) && (i == end_r)) || ((type & mx_horiz) && (j == end_c))) {
                    printf("\n");
                    continue;
                }
                unsigned int next_r = i, next_c = j;
                int offs_r = 0, offs_c = 0;
                if (type & mx_vert) {
                    if ((type & mx_less)) { // Влево: тянем j+1 в j
                        next_r = dst->rows - i - 1;
                        offs_r = -1;
                    } else { // Вправо: тянем j-1 в j
                        next_r = i;
                        offs_r = 1;
                    }
                }
                if (type & mx_horiz) {
                    if ((type & mx_less)) { // Влево: тянем j+1 в j
                        next_c = j;
                        offs_c = 1;
                    } else { // Вправо: тянем j-1 в j
                        next_c = dst->columns - j - 1;
                        offs_c = -1;
                    }
                }
                printf("Roll elements from %u:%u to %u:%u;\n", next_r, next_c, next_r + offs_r, next_c + offs_c);
                type_xchg(linear(dst, next_r, next_c), linear(dst, next_r + offs_r, next_c + offs_c), dst->flags);
                break;
            }
            default:
                printf("update error, type of action us undefined;\n");
                return mx_error;
            }
            updates++;
            src_idx++; // След. элемент данных
            // Если флаг mx_all не установлен, выполняем только один раз
            if (!(type & mx_all) && updates > 0)
                stop_processing = 1;
        }
    }
    printf("Matrix updated, %u elements modified.\n", updates);
    return (updates > 0) ? mx_ok : mx_nop;
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
        type_rand в тестовую таблицу
        обновить и протестировать create
        update

        черновик к пятнице вечеру
        к субботе - теорию (8-9)
    */
    // Инициализация и объявление переменных
    srand((unsigned int)time(NULL));
    printf("Chapter 12;\n");

    // Основные структуры и указатели
    struct Matrix matrix_a = {NULL, 0, 0, 0, mx_nop};
    struct Matrix matrix_b = {NULL, 0, 0, 0, mx_nop};
    struct Matrix matrix_c = {NULL, 0, 0, 0, mx_nop};
    struct Matrix* ptr_a = &matrix_a;
    struct Matrix* ptr_b = &matrix_b;
    struct Matrix* ptr_c = &matrix_c;

    // Вспомогательные переменные
    char data_text[DATA_MAX] = {'D', 'E', 'X'}, text[DATA_MAX];
    short data_short[DATA_MAX] = {1, 2, 3, 4, 5};
    short init_val = 10;
    unsigned int found_row = 0, found_col = 0, count = 0;
    enum mx_flags result;

    // Информация о структуре Matrix
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

    // Тестирование вспомогательных функций
    printf("Function:\tLeft:\tRight:\tFlags:\tResult:\t\tComment:\n");
    printf("----------------------------------------------------------------------------\n");
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
    printf("type_rand\t-\t-\t%s\t", flags_text(mx_char, 0, 0));
    type_rand(&data_text[0], mx_char);
    printf("%c\t\tRandom char\n", data_text[0]);
    printf("type_rand\t-\t-\t%s\t", flags_text(mx_word, 0, 0));
    type_rand(&data_short[0], mx_word);
    printf("%hd\t\tRandom word\n", data_short[0]);
    printf("----------------------------------------------------------------------------\n");
    printf("Character range: '%c' to '%c'\n", char_first, char_last);
    printf("Word range: %hd to %hd\n", word_first, word_last);

    // Тесты №1: Создание матриц и тестирования печати
    printf("\n\n--------------------------Tests #1: Creating Matrices and Printing Tests--------------------------\n\n");
    printf("Matrix A: %p (rows: %u, columns: %u)\n", ptr_a, ptr_a->rows, ptr_a->columns);
    printf("Matrix B: %p (rows: %u, columns: %u)\n", ptr_b, ptr_b->rows, ptr_b->columns);
    printf("Matrix C: %p (rows: %u, columns: %u)\n", ptr_c, ptr_c->rows, ptr_c->columns);
    printf("All matrices are initialized but not allocated yet.\n");
    printf("\nInvalid matrix creation\n");
    result = create(ptr_a, 0, 5, NULL, mx_char);
    printf("Create 0x5 matrix: %s\n", flags_text(result, 0, 0));
    printf("\n\nCorrect matrix creation\n");
    result = create(ptr_a, 3, 4, NULL, mx_char | mx_rand);
    printf("create return result: '%s' and matrix has %u elements;\n",
           flags_text(result, act_nop, 0), size(ptr_a));
    print(ptr_a, 0, 0, mx_all);
    // Создание матрицы B
    printf("\n\nSecond matrix creation\n");
    create(ptr_b, 2, 2, &init_val, mx_word);
    print(ptr_b, 0, 0, mx_all);
    // Проверка линейного доступа к памяти
    printf("\nLinear test for word matrix\n");
    void* addr = linear(ptr_b, 1, 1);
    printf("linear(1,1): %p -> value=%hd (expected: 10)\n", addr, *((short*)addr));
    printf("\nPrinting test\n");
    printf("Matrix A (3x4) full:\n");
    print(ptr_a, 0, 0, mx_all);
    printf("Row 1:\n");
    print(ptr_a, 1, 0, mx_row);
    printf("Column 2:\n");
    print(ptr_a, 0, 2, mx_column);
    printf("Element [2][3]:\n");
    print(ptr_a, 2, 3, mx_row | mx_column);
    // Печать несуществующих элементов
    printf("Invalid row (5):\n");
    print(ptr_a, 5, 0, mx_row);
    printf("Invalid column (5):\n");
    print(ptr_a, 0, 5, mx_column);
    // Тест ввода с клавиатуры
    /*
    printf("Test 9: Keyboard input\n");
    destroy(ptr_c);
    result = create(ptr_c, 2, 2, NULL, mx_char | mx_input);
    print(ptr_c, 0, 0, mx_all);
    */

    // Тесты №2: Копирование
    printf("\n\n--------------------------Test #2: Copy--------------------------\n\n");
    // Полное копирование
    printf("\nFull matrix copy\n");
    print(ptr_a, 0, 0, mx_all);
    mx_copy(ptr_c, ptr_a, 0, 0, 2, 3);
    print(ptr_c, 0, 0, mx_all);
    // Копирование отдельного элемента
    printf("\nSingle element copy\n");
    destroy(ptr_c);
    print(ptr_a, 0, 0, mx_all);
    result = mx_copy(ptr_c, ptr_a, 1, 1, 1, 2);
    ((char*)ptr_c->matrix)[0] = 'A';
    ((char*)ptr_c->matrix)[1] = 'C';
    print(ptr_c, 0, 0, mx_all);
    info(ptr_c, 1, 2, mx_char);
    print(ptr_b, 0, 0, mx_all);
    info(ptr_b, 0, 0, mx_word | mx_row | mx_even);
    // Копирования части матрицы
    printf("Source Matrix A (before copy):\n");
    print(ptr_a, 0, 0, mx_all);
    destroy(ptr_c);
    printf("\nCopying 2x2 sub-matrix from A[1,1] to A[2,2] into C...\n");
    result = mx_copy(ptr_c, ptr_a, 1, 1, 2, 2);
    printf("Resulting Matrix C (after copy):\n");
    print(ptr_c, 0, 0, mx_all);

    // Тесты №3: Перемещение
    printf("\n\n--------------------------Test #3: Move--------------------------\n\n");
    printf("Move to occupied matrix\n");
    // Очищаем B перед перемещением в неё данных
    destroy(ptr_b);
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

    // Тесты №4 Вывод общий информации о матрице
    printf("\n\n--------------------------Tests #4: General information about the matrix--------------------------\n\n");
    info(ptr_a, 0, 0, mx_all | mx_char);
    printf("\nInfo for row 1 of Matrix A:\n");
    info(ptr_a, 1, 0, mx_row | mx_char);
    printf("\nInfo for column 2 of Matrix A:\n");
    info(ptr_a, 0, 2, mx_column | mx_char);
    printf("\nInfo for odd-indexed columns in row 1 of Matrix A:\n");
    info(ptr_a, 1, 0, mx_row | mx_odd | mx_column | mx_char);

    // Тесты №5: Уплотнение
    printf("\n\n--------------------------Tests #5: Compact--------------------------\n\n");
    *((char*)linear(ptr_a, 0, 0)) = 'X';
    *((char*)linear(ptr_a, 0, 1)) = 'X';
    *((char*)linear(ptr_a, 0, 2)) = 'X';
    *((char*)linear(ptr_a, 0, 3)) = 'X';
    printf("Matrix A (3x4) before compact:\n");
    print(ptr_a, 0, 0, mx_all);
    result = compact(ptr_a, &data_text[2]);
    printf("Compaction result: %s\n", flags_text(result, 0, 0));
    print(ptr_a, 0, 0, mx_all);

    // Тесты №6: Вставка и обрезка
    printf("\n\n--------------------------Tests #6: Insert and Cut--------------------------\n\n");
    destroy(ptr_b);
    destroy(ptr_c);
    create(ptr_b, 1, 1, NULL, mx_rand | mx_word);
    create(ptr_c, 1, 1, NULL, mx_rand | mx_word);
    print(ptr_b, 0, 0, mx_all);
    print(ptr_c, 0, 0, mx_all);
    // Вставка строки
    insert(ptr_b, ptr_c, 1, 0, mx_row);
    print(ptr_b, 0, 0, mx_all);
    // Вставка столбца
    insert(ptr_b, ptr_b, 0, 1, mx_column);
    print(ptr_b, 0, 0, mx_all);
    // Изменение значений и повторная вставка
    *((short*)linear(ptr_b, 0, 1)) = 1;
    *((short*)linear(ptr_b, 1, 1)) = 3;
    print(ptr_b, 0, 0, mx_all);
    insert(ptr_b, ptr_b, 1, 0, mx_row);
    print(ptr_b, 0, 0, mx_all);
    // Тестирование обрезки на новой матрице
    destroy(ptr_a);
    create(ptr_a, 3, 4, NULL, mx_char | mx_rand);
    print(ptr_a, 0, 0, mx_all);
    cut(ptr_a, 0, 1, mx_row);
    print(ptr_a, 0, 0, mx_all);
    cut(ptr_a, 0, 2, mx_column);
    print(ptr_a, 0, 0, mx_all);

    // Тесты №7: Поиск
    printf("\n\n--------------------------Tests #7: Find--------------------------\n\n");
    print(ptr_a, 0, 0, mx_all);
    print(ptr_b, 0, 0, mx_all);
    print(ptr_c, 0, 0, mx_all);
    destroy(ptr_a);
    destroy(ptr_b);
    printf("\nFind first 'X' in matrix A\n");
    create(ptr_a, 3, 4, NULL, mx_word | mx_rand);
    print(ptr_a, 0, 0, mx_all);
    found_row = 0;
    found_col = 0;
    data_short[0] = *(short*)linear(ptr_a, found_row, found_col);
    count = find(ptr_b, ptr_a, data_short, &found_row, &found_col, act_data,
                 mx_equal | mx_row | mx_column | mx_horiz | mx_vert);
    printf("Find count: %u\n", count);
    destroy(ptr_b);
    count = find(ptr_b, ptr_a, data_short, &found_row, &found_col, act_min, mx_all);
    printf("Find min count: %u\n", count);
    destroy(ptr_b);
    count = find(ptr_b, ptr_a, data_short, &found_row, &found_col, act_uniq, mx_nop);
    printf("Result: Found %u element(s). First occurrence at [%u, %u].\n",
           count, found_row, found_col);
    printf("Data found:\n");
    print(ptr_b, 0, 0, mx_all);

    // Тест №8: Закомментированные тесты update
    printf("\n\n--------------------------Tests #8: Update--------------------------\n\n");
    //Тест act_assign: Заполнение областей
    printf("1. Assign 'X' to Row 0 and Column 2:\n");
    destroy(ptr_a);
    destroy(ptr_b);
    create(ptr_a, 3, 5, NULL, mx_char | mx_rand);
    char val_x = 'X';
    create(ptr_b, 1, 1, &val_x, mx_char);
    print(ptr_a, 0, 0, mx_all);
    update(ptr_a, ptr_b, NULL, 0, 0, act_roll, mx_all | mx_vert | mx_more);
    print(ptr_a, 0, 0, mx_all);
    return;
    update(ptr_a, ptr_b, NULL, 0, 2, act_assign, mx_column | mx_all);
    print(ptr_a, 0, 0, mx_all);
    //Тест act_seq: Арифметическая прогрессия (1..9)
    printf("\n2. Arithmetic Sequence (Start:1, End:9, Step:1):\n");
    destroy(ptr_a);
    destroy(ptr_b);
    create(ptr_a, 3, 5, NULL, mx_word);
    create(ptr_b, 1, 3, NULL, mx_word);
    ((short*)ptr_b->matrix)[0] = 1;  // Start
    ((short*)ptr_b->matrix)[1] = 9;  // End (max for mx_word)
    ((short*)ptr_b->matrix)[2] = 1;  // Step
    update(ptr_a, ptr_b, NULL, 0, 0, act_seq, mx_all);
    print(ptr_a, 0, 0, mx_all);
    //Тест act_roll: Сдвиг
    printf("\n3. Roll Row 1 Left and Column 4 Down:\n");
    // Сдвиг 1-й строки влево
    update(ptr_a, NULL, NULL, 1, 0, act_roll, mx_row | mx_horiz | mx_less | mx_all);
    // Сдвиг 4-го столбца вниз
    update(ptr_a, NULL, NULL, 0, 4, act_roll, mx_column | mx_vert | mx_more | mx_all);
    print(ptr_a, 0, 0, mx_all);
    //Тест act_add с условием: Добавить 2 ко всем числам < 5
    printf("\n4. Conditional Add: Add 2 to values < 5:\n");
    destroy(ptr_b);
    short val_add = 2;
    short val_thresh = 5;
    create(ptr_b, 1, 1, &val_add, mx_word);
    update(ptr_a, ptr_b, &val_thresh, 0, 0, act_add, mx_all | mx_less);
    print(ptr_a, 0, 0, mx_all);

    // Уничтожение матриц
    printf("Cleanup\n");
    destroy(ptr_a);
    destroy(ptr_b);
    destroy(ptr_c);
    printf("Final memory check: %u bytes used, %u bytes free (total: %u bytes)\n",
           MEM_MAX - memory, memory, MEM_MAX);
    return;
}
