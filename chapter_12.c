#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATA_MAX 256
#define MEM_MAX 1500
#define MAX_ROWS 12
#define MAX_COLUMNS 12
/*
 *  Глава 12. матрицы произвольных размерностей и базовые алгоритмы интерпритации данных.
 */

enum mx_flags { mx_nop = 0x00, mx_ok = 0x00, mx_error = 0x01, mx_char = 0x02, mx_word = 0x04, mx_column = 0x08, mx_row = 0x10,
                mx_horiz = 0x20, mx_vert = 0x40, mx_all = 0x80, mx_rand = 0x100, mx_input = 0x200, mx_equal = 0x400,
                mx_less = 0x800, mx_more = 0x1000, mx_even = 0x2000, mx_odd = 0x4000
};

enum mx_actions {
    act_nop = 0x00, act_create = 0x01, act_copy = 0x02, act_move = 0x04, act_destroy = 0x08, act_assign = 0x10, act_neg = 0x20,
    act_add = 0x40, act_mul = 0x80, act_xchg = 0x100, act_pow = 0x200, act_value = 0x400, act_rand = 0x800, act_roll = 0x1000,
    act_min = 0x2000, act_max = 0x4000, act_uniq = 0x8000, act_create_ariphmetic = 0x10000, act_create_geometric = 0x20000,
    act_end = 0x40000
};

struct Matrix {
    void* matrix;
    unsigned int rows, columns, data_size;
    enum mx_flags flags;
};

//Статичные переменные для всей главы.
static unsigned int random_word = 10; // Максимальное значение для случайных чисел
static unsigned int random_char = 'Z'- 'A';
static int arithmetic_step = 1;       // Шаг арифметической прогрессии
static double geometric_ratio = 2.0;  // Знаменатель геометрической прогрессии
static unsigned int memory = MEM_MAX;
static char flags_info[DATA_MAX], actions_info[DATA_MAX];
static char* matrix_flags_name[] = { "nope_ok", "error", "char", "word",
    "column", "row", "horizontal", "vertical", "all", "random", "input",
    "equal", "less", "more"
};

/*
    "initialization zeros", "initialization input", "initialization from source data",
    "initialization only columns from source", "initialization only rows from source",
    "create value", "create random", "create ariphmetic", "create geometric",
    "roll left", "roll right", "roll up", "roll down"
 */

static const unsigned int types_sizes[] = {sizeof(char), sizeof(short)};

static char* matrix_actions_name[] = {
    "nop", "init zeros", "init input",
    "init from source", "init columns", "init rows",
    "create value", "create random", "create ariphmetic",
    "create geometric"
};

static char* types_names[] = {
    "char", "word"
};

unsigned int is_types(enum mx_flags types)
{// Вспомогательная функция для проверки количества типов данных.
    return ((types & mx_char) != 0) + ((types & mx_word) != 0);
}

char* type_name(enum mx_flags type)
{// Для удобства. Возврат названия типа данных,                 функцию переделать
    return types_names[((type & (mx_char | mx_word)) >> 0x02)];
}

unsigned int type_size(enum mx_flags type)
{// Для удобства. Возврат размера типа данных.
    return types_sizes[((type & (mx_char | mx_word)) >> 0x02)];
}

char* type_text(char* text, void* data, enum mx_flags type)
{//Вспомогательная функция текстового представления типа, тескт как есть или цифры со знаком.
    if (text == NULL || is_types(type) != 1) {
        printf("\nWarning type to text, some arguments maybe incorrect;\n");
        return text;
    }
    memset(text, 0, DATA_MAX);
    switch (type & (mx_char | mx_word)) {
    case (mx_char):
        text[0] = (data != NULL) ? *((char*)data) : ' ';
        break;
    case (mx_word):
        sprintf_s(text, DATA_MAX, "%+hd", (data != NULL) ? *(short*)data : 0);
        break;
    default:
        printf("\nWarning type to text, some arguments maybe incorrect;\n");
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
    case mx_char: {
        if (*((char*)left) > *((char*)right))
            return mx_more;
        else if (*((char*)left) < *((char*)right))
            return mx_less;
        else
            return mx_equal;
    }
    case mx_word: {
        if (*((short*)left) > *((short*)right))
            return mx_more;
        else if (*((short*)left) < *((short*)right))
            return mx_less;
        else
            return mx_equal;
    }
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

enum mx_flags type_add(void* left, void* right, enum mx_flags type)
{// Сложение элементов с учётом типа.
    if (left == NULL || right == NULL || is_types(type) != 1)
        return mx_error;
    switch (type & (mx_char | mx_word)) {
    case mx_char:
        *((char*)left) += *((char*)right);
        break;
    case mx_word:
        *((short*)left) += *((short*)right);
        break;
    default:
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

unsigned int size(struct Matrix* obj)
{//Вычисляем количество элементов в матрице (rows * columns)
    if (is_correct(obj) != mx_ok)
        return 0;
    return (unsigned int)(obj->rows * obj->columns);
}

char* info_text(enum mx_flags state, enum mx_actions action, unsigned int type)
{//Возвращает в виде текстовой строки все флаги, без доп символов, в статичную переменную.  type, 0 - флаги, иначе actions
    char* info = (type == 0) ? flags_info : actions_info;
    info[0] = '\0';
    // Определяем параметры в зависимости от типа
    unsigned int* value = (type == 0) ? (unsigned int*)&state: (unsigned int*)&action;
    char** names = (type == 0) ? matrix_flags_name : matrix_actions_name;
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

void info(struct Matrix* obj, unsigned short row, unsigned short col, enum mx_flags type)
{//Общая информация о матрице, в статичную строку без доп символов.
    if (obj == NULL) {                                                          // проверка correct и размерности
        printf("Matrix: NULL object");
        return;
    }
    printf("Matrix %dx%d", obj->rows, obj->columns);
    if (obj->flags & mx_char)                                                   // Использовать вспомогательные функции
        printf(" char");
    else if (obj->flags & mx_word)
        printf(" short");
    else
        printf(" unknown_type");
    if (obj->matrix == NULL)
        printf(" unallocated");
    else
        printf(" allocated");
    //Обработка всех флагов, только строка или только столбец, вся матрица, чётные и не чётные, операторы для типов оставить тут
    //В один цикл
    //Убрать работу с дробями
    if (obj->matrix != NULL && obj->rows > 0 && obj->columns > 0) {
        double sum = 0.0, product = 1.0;
        int count = obj->rows * obj->columns;
        int has_negative = 0;
        if (obj->flags & mx_char) {
            char* data = (char*)obj->matrix;
            for (int i = 0; i < count; i++) {
                sum += data[i];
                product *= data[i];
                if (data[i] < 0)
                    has_negative = 1;
            }
        } else if (obj->flags & mx_word) {
            short* data = (short*)obj->matrix;
            for (int i = 0; i < count; i++) {
                sum += data[i];
                product *= data[i];
                if (data[i] < 0)
                    has_negative = 1;
            }
        }
        double arithmetic_mean = sum / count;
        double geometric_mean = 0.0;
        if (!has_negative && count > 0)
            geometric_mean = pow(product, 1.0 / count);
        printf("\nsum:%.2f\nproduct:%.2f\narithmetic:%.2f", sum, product, arithmetic_mean);
        if (!has_negative)
            printf("\ngeometric:%.2f", geometric_mean);
    }
    printf(" [");
    printf("%s", info_text(obj->flags, 0, 0));
    printf("]");
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
               obj, info_text(obj->flags, act_nop, 0), rows, columns);
        return mx_error;
    }
    unsigned int req_mem = rows * columns * type_size(type);
    char init_char = (data != NULL) ? *(char*)data : ' ', init_text[DATA_MAX], data_text[DATA_MAX];
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
           obj, rows, columns, init_text, info_text(type, act_nop, 0));
    obj->rows = rows; obj->columns = columns; obj->data_size = req_mem;
    obj->flags = type & (mx_char | mx_word);
    for (unsigned int i = 0; i < rows * columns; ++i) {
        if (type & mx_input) {
            printf("Input (%u,%u) element: ", i / columns, i % columns);
            scanf("%s", init_text);
        }
        switch (type & (mx_char | mx_word)) {
        case mx_char:
            if (type & mx_rand)
                init_char = 'A' + rand() % random_char;
            else if (type & mx_input)
                init_char = init_text[0];
            ((char*)obj->matrix)[i] = init_char;
            break;
        case mx_word:
            if (type & mx_rand)
                init_word = rand() % random_word;
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
           info_text(src->flags, act_nop, 0));
    enum mx_flags type = src->flags & (mx_char | mx_word);
    if ((create(dst, rows_new, cols_new, NULL, type)) != mx_ok) {
        printf("error copy: failed to create destination matrix\n");
        return mx_error;
    }
    for (unsigned int i = 0; i < rows_new; i++)
        for (unsigned int j = 0; j < cols_new; j++)                                    // Доп. использовать assign
            if (type & mx_char) {
                char (*src_arr)[src->rows][src->columns] = src->matrix;
                char (*dst_arr)[rows_new][cols_new] = dst->matrix;
                (*dst_arr)[i][j] = (*src_arr)[row_first + i][col_first + j];
            } else {
                short (*src_arr)[src->rows][src->columns] = src->matrix;
                short (*dst_arr)[rows_new][cols_new] = dst->matrix;
                (*dst_arr)[i][j] = (*src_arr)[row_first + i][col_first + j];
            }
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
    printf("\nDestroy matrix: [%p], free %u elements and %u bytes, available memory %u;\n", obj, size(obj), obj->data_size, memory);
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
    printf("Printing matrix %dx%d with style [%s]\n", obj->rows, obj->columns, info_text(style, 0, 0));
    unsigned int start_row = 0, end_row = obj->rows;
    unsigned int start_col = 0, end_col = obj->columns;
    start_row = (style & mx_row) ? row : start_row;
    end_row = (style & mx_row) ? row + 1 : end_row;
    start_col = (style & mx_column) ? column : start_col;
    end_col = (style & mx_column) ? column + 1 : end_col;
    for (unsigned int i = start_row; i < end_row; i++) {
        for (unsigned int j = start_col; j < end_col; j++) {
            if (obj->flags & mx_char)
                printf("%c ", ((char*)obj->matrix)[i * obj->columns + j]);
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

enum mx_flags compact(struct Matrix* obj)
{// Сжатие или уплотнение матрицы. Удаляются полнстью нулевые стоки или столбцы.
    printf("\nMatrix compact (final version)\n");
    if (is_correct(obj) != mx_ok || size(obj) == 0) {
        printf("error: invalid or empty matrix for compaction\n");
        return is_correct(obj) | mx_error;
    }
    int rows_to_keep[MAX_ROWS];
    int cols_to_keep[MAX_COLUMNS];
    for (int i = 0; i < MAX_ROWS; ++i)
        rows_to_keep[i] = 0;
    for (int i = 0; i < MAX_COLUMNS; ++i)
        cols_to_keep[i] = 0;
    for (unsigned int i = 0; i < obj->rows; i++) {
        for (unsigned int j = 0; j < obj->columns; j++) {
            unsigned int index = i * obj->columns + j;
            int is_zero;
            if (obj->flags & mx_char)
                is_zero = ((char*)obj->matrix)[index] == ' ';
            else if (obj->flags & mx_word)
                is_zero = ((short*)obj->matrix)[index] == 0;
            else
                is_zero = 1;
            if (!is_zero) {
                rows_to_keep[i] = 1;
                cols_to_keep[j] = 1;
            }
        }
    }
    unsigned int new_rows = 0, new_cols = 0;
    for (unsigned int i = 0; i < obj->rows; i++)
        if (rows_to_keep[i]) new_rows++;
    for (unsigned int j = 0; j < obj->columns; j++)
        if (cols_to_keep[j]) new_cols++;
    if (new_rows == 0 || new_cols == 0) {
        printf("Matrix is effectively empty, destroying.\n");
        return destroy(obj);
    }
    if (new_rows == obj->rows && new_cols == obj->columns) {
        printf("No empty rows or columns found. Compaction not needed.\n");
        return mx_ok;
    }
    printf("Compacting matrix from %dx%d to %dx%d\n", obj->rows, obj->columns, new_rows, new_cols);
    struct Matrix temp = { NULL, 0, 0, 0, mx_nop };
    enum mx_flags type_flag = (obj->flags & mx_char) ? mx_char : mx_word;
    enum mx_flags result = create(&temp, new_rows, new_cols, NULL, type_flag);
    if (result != mx_ok) {
        printf("error: failed to create temporary matrix for compaction\n");
        return result;
    }
    unsigned int element_size = (type_flag == mx_char) ? sizeof(char) : sizeof(short);
    unsigned int current_idx = 0;
    for (unsigned int i = 0; i < obj->rows; i++) {
        if (!rows_to_keep[i]) continue;
        for (unsigned int j = 0; j < obj->columns; j++) {                           // Доп. использовать assign
            if (!cols_to_keep[j]) continue;
            unsigned int src_index = i * obj->columns + j;
            void* src_ptr = (char*)obj->matrix + src_index * element_size;
            void* dst_ptr = (char*)temp.matrix + current_idx * element_size;
            memcpy(dst_ptr, src_ptr, element_size);
            current_idx++;
        }
    }
    unsigned int old_rows = obj->rows, old_cols = obj->columns;
    struct Matrix* ptr_temp = &temp;
    destroy(obj);
    move(&obj, &ptr_temp);
    printf("Compaction from %dx%d to %dx%d successful. Total free memory: %u\n",
           old_rows, old_cols, obj->rows, obj->columns, memory);
    return mx_ok;
}

enum mx_flags operator(struct Matrix* dst, struct Matrix* src, enum mx_actions action)
{// Исходная матрица должна сохраниться
    printf("\nMatrix operator: %s\n", info_text(0, action, 1));
    if (is_correct(dst) != mx_ok) {
        printf("error: Invalid destination matrix\n");
        return is_correct(dst);
    }
if (action != act_neg && is_correct(src) != mx_ok) {
    printf("error: Invalid source matrix\n");
    return is_correct(src);
}
if ((action == act_add || action == act_mul || action == act_pow || action == act_xchg) &&
    (dst->rows != src->rows || dst->columns != src->columns)) {
    printf("error: Matrix sizes must match for this operation\n");
    printf("Destination: %dx%d, Source: %dx%d\n",
           dst->rows, dst->columns, src->rows, src->columns);
    return mx_error;
}
if ((action == act_add || action == act_mul || action == act_pow || action == act_xchg) &&
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
case act_pow: { // Возведение в степень dst ^ src
    printf("Performing element-wise power operation\n");
    unsigned int count = dst->rows * dst->columns;
    if (dst->flags & mx_char) {
        char* dst_data = (char*)dst->matrix;
        char* src_data = (char*)src->matrix;
        for (unsigned int i = 0; i < count; i++) {
            char base = dst_data[i];
            char exponent = src_data[i];
            char result = 1;
            for (char j = 0; j < exponent; j++) {
                result *= base;
            }
            dst_data[i] = result;
        }
    } else if (dst->flags & mx_word) {
        short* dst_data = (short*)dst->matrix;
        short* src_data = (short*)src->matrix;
        for (unsigned int i = 0; i < count; i++) {
            short base = dst_data[i];
            short exponent = src_data[i];
            short result = 1;
            for (short j = 0; j < exponent; j++) {
                result *= base;
            }
            dst_data[i] = result;
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

unsigned int find(struct Matrix* dst, struct Matrix* src, void* data,
                  unsigned int* row, unsigned int* col, enum mx_actions action, enum mx_flags type)
{// Поиск заданного элемента/элементов в исходной матрице
    // и сохранение в матрицу назначения с учётом параметров и флагов.

}

unsigned int update(struct Matrix* dst, void* data, unsigned int row, unsigned int col, enum mx_actions action, enum mx_flags type)
{//Обновление матрицы, вовращает количество заменённых объектов.

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
    printf("\nMatrix order check: %s\n", info_text(type, 0, 0));
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
            printf("Rows are ordered: %s\n", info_text(result, 0, 0));
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
            printf("Columns are ordered: %s\n", info_text(result, 0, 0));
            return result;
        }
    }
    if (!(type & mx_row) && !(type & mx_column)) {
        printf("Checking entire matrix as linear array\n");
        result = check_array_order(obj->matrix, obj->rows * obj->columns, data_type);
        if (result != mx_nop) {
            printf("Matrix is ordered: %s\n", info_text(result, 0, 0));
            return result;
        }
    }
    printf("Matrix is not ordered\n");
    return mx_nop;
}

void chapter_12()
{
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
    //printf("(%s)", info_text(mx_row | mx_err_mem | mx_ok, act_nop, 0));
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

    // 1. Тест создания матрицы с неверными размерами
    printf("\n=== Test 1: Invalid matrix creation ===\n");
    enum mx_flags result = create(ptr_a, 0, 5, NULL, mx_char);  // Нулевые строки
    printf("Create 0x5 matrix: %s\n", info_text(result, 0, 0));

    // 2. Создание матрицы A (3x4, тип char, случайные значения)
    printf("\n\n=== Test 2: Valid matrix creation ===\n");
    result = create(ptr_a, 3, 4, NULL, mx_char | mx_rand);
    if (result != mx_ok) {
        printf("Failed to create Matrix A\n");
        return;
    } else
        printf("create return result: '%s' and matrix has %u elements;\n", info_text(result, act_nop, 0), size(ptr_a));
    print(ptr_a, 0, 0, mx_all);
    //print(ptr_a, 0, 0, mx_row);
    //print(ptr_a, 0, 0, mx_column);                                  // Проверить
    // 3. Создание матрицы B (2x2, тип short, нули)
    printf("\n\n=== Test 3: Second matrix creation ===\n");
    short data = 10;
    create(ptr_b, 2, 2, &data, mx_word);
    print(ptr_b, 0, 0, mx_all);
    // 4. Копирование всей матрицы A в C
    printf("\n\n=== Test 4: Full matrix copy ===\n");
    print(ptr_a, 0, 0, mx_all);
    mx_copy(ptr_c, ptr_a, 0, 0, 2, 3);  // Всю матрицу 3x4
    print(ptr_c, 0, 0, mx_all);
    // 5. Копирование отдельного элемента
    printf("\n\n=== Test 5: Single element copy ===\n");
    destroy(ptr_c);  // Очищаем для нового теста
    result = mx_copy(ptr_c, ptr_a, 1, 1, 1, 1);  // Один элемент
    print(ptr_c, 0, 0, mx_all);
    // 6. Перемещение матрицы в занятую матрицу
    printf("=== Test 6: Move to occupied matrix ===\n");
    printf("Before move - Matrix B:\n");
    print(ptr_b, 0, 0, mx_all);
    printf("Before move - Matrix C:\n");
    print(ptr_c, 0, 0, mx_all);
    move(&ptr_b, &ptr_c);
    destroy(ptr_c);
    move(&ptr_c, &ptr_b);
    printf("Move B to C: %s\n", info_text(result, 0, 0));
    printf("Matrix B:\n");
    print(ptr_b, 0, 0, mx_all);
    printf("Matrix C:\n");
    print(ptr_c, 0, 0, mx_all);
    return;
    // 7. Повторное создание и перемещение
    printf("=== Test 7: Recreate and move again ===\n");
    result = create(ptr_c, 2, 2, NULL, mx_char | mx_rand);
    if (result == mx_ok) {
        printf("Recreated Matrix C:\n");
        print(ptr_c, 0, 0, mx_all);

        result = move(&ptr_b, &ptr_c);
        printf("Second move C to B: %s\n", info_text(result, 0, 0));
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
    // 13. Тест сжатия матрицы типа char с пустыми строками и столбцами
    printf("\n=== Test 13: Char matrix compaction ===\n");
    struct Matrix matrix_d = {NULL, 0, 0, 0, mx_nop};
    struct Matrix* ptr_d = &matrix_d;
    result = create(ptr_d, 4, 4, NULL, mx_char);
    if (result == mx_ok) {
        char* data = (char*)ptr_d->matrix;
        data[5] = 'A';  // [1][1]
        data[6] = 'B';  // [1][2]
        data[9] = 'C';  // [2][1]
        data[10] = 'D'; // [2][2]
        printf("Before compaction:\n");
        print(ptr_d, 0, 0, mx_all);
        result = compact(ptr_d);
        printf("Compaction result: %s\n", info_text(result, 0, 0));
        printf("After compaction:\n");
        print(ptr_d, 0, 0, mx_all);
        destroy(ptr_d);
    }
    return;
}
