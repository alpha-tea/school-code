#include "global.h"
#include "library.h"

static const int matrix_act_mask = 0x1F;            // Константная маска до модификатора. Изменить, если поменяется назначение бит.
static const int matrix_check_mask = 0xFF000;       // Маска для модификатора проверки массива или элемента.

enum matrix_type { mx_nop, mx_init_par, mx_init_input, mx_init_all, mx_init_column, mx_init_row,
                   mx_cr_val, mx_cr_rnd, mx_cr_ariphmetic, mx_cr_geometry,
                   mx_roll_left, mx_roll_right, mx_roll_up, mx_roll_down,
                   mx_info_status, mx_info_sum, mx_info_multiply, mx_info_avr, mx_info_min, mx_info_max, mx_info_pairs, mx_info_idxs,
                   mx_prn_default = 0x20,  mx_prn_row = 0x40, mx_prn_column = 0x80, mx_prn_flipv = 0x100, mx_prn_fliph = 0x200, mx_prn_field = 0x400,
                   mx_chk_idxs = 0x800, mx_chk_equal = 0x1000, mx_chk_more = 0x2000, mx_chk_less = 0x4000,
                   mx_chk_not_div = 0x8000, mx_chk_div = 0x10000, mx_chk_pairs = 0x20000, mx_chk_dsc = 0x40000, mx_chk_asc = 0x80000,
                   mx_mod_col = 0x100000, mx_mod_row = 0x200000, mx_mod_sq = 0x400000, mx_mod_last = 0x800000,
                   mx_end = 0x1000000
                 };

static char* matrix_type_name[] = { "matrix nope",
                                    "initialization zeros", "initialization input", "initialization from source data",
                                    "initialization only columns from source", "initialization only rows from source",
                                    "create value", "create random", "create ariphmetic", "create geometric",
                                    "roll left", "roll right", "roll up", "roll down"
                                  };

int matrix_init(int data[OBJECTS_MAX][OBJECTS_MAX], int init[OBJECTS_MAX][OBJECTS_MAX],
                int columns, int rows, int par, enum matrix_type type)
{
    if (type < mx_init_par || type > mx_init_row || columns >= OBJECTS_MAX || rows >= OBJECTS_MAX ||
            columns < 1 || rows < 1) {
        printf("error in array size, rows = %d, columns = %d or initialization type = %d incorrect;\n",
               rows, columns, type);
        return -1;
    }
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            switch (type) {
            case mx_init_par:
                data[i][j] = par;
                break;
            case mx_init_input:
                printf("%d:%d: ",i,j);
                scanf("%d", &data[i][j]);
                break;
            case mx_init_all:
                data[i][j] = init[i][j]; //if & - data[i][j] = *init++;
                break;
            case mx_init_column:
                data[i][j] = init[0][j];
                break;
            case mx_init_row:
                data[i][j] = init[0][i];
                break;
            default:
                printf("type of array initialization is incorrect, %d;\n",type);
                return -1;
            }
    return 0;
}

int matrix_print(int data[OBJECTS_MAX][OBJECTS_MAX], int columns, int rows, int parameter, enum matrix_type type)
{
    if (type < mx_prn_default || columns > OBJECTS_MAX || rows > OBJECTS_MAX) {
        printf("error in print matrix type;\n");
        return -1;
    }
    int field = 0;
    if (type & mx_prn_field) {
        field = parameter;
        type ^= mx_prn_field;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (field > 0) {
                int element = data[i][j], data_size = 0;
                if (element < 0)
                    data_size++;
                data_size += length_number(element);
                //printf("data_size = %d;\n", data_size);
                for (int k = data_size; k < field; ++k)
                    printf(" ");
            }
            for (int mask = mx_prn_default; mask != mx_chk_idxs; mask <<= 1) {
                switch (type & mask) {
                case mx_prn_default:
                    printf("%2d ", data[i][j]);
                    break;
                case mx_prn_column:
                    if (j == parameter)
                        printf("%d ", data[i][j]);
                    break;
                case mx_prn_row:
                    if (i == parameter)
                        printf("%d ", data[i][j]);
                    break;
                case mx_prn_fliph:
                    printf("%d ", data[i][columns - j - 1]);
                    break;
                case mx_prn_flipv:
                    printf("%d ", data[rows - i - 1][j]);
                    break;
                }
            }
        }
        printf("\n");
    }
    return 0;
}

int matrix_create_sequence(int data[OBJECTS_MAX][OBJECTS_MAX], int columns, int rows, int parameter, enum matrix_type type)
{
    if (type < mx_cr_val || type > mx_cr_geometry || columns >= OBJECTS_MAX || rows >= OBJECTS_MAX ||
            columns < 1 || rows < 1 || (type == mx_cr_rnd && parameter == 0)) {
        printf("error in array size, rows = %d, columns = %d, par = %d or sequence type = %d incorrect;\n",
               rows, columns, parameter, type);
        return -1;
    }
    int ariphmetic = 0, geometric = 1;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            switch (type) {
            case mx_cr_val:
                data[i][j] = parameter;
                break;
            case mx_cr_rnd:
                data[i][j] = rand() % abs(parameter);
                if (parameter < 0 && rand() % 2 == 0)   //если отрицательное значение параметра то значение в масиве со знаком минус
                    data[i][j] *= -1;
                break;
            case mx_cr_ariphmetic:
                data[i][j] = ariphmetic;
                ariphmetic += parameter;
                break;
            case mx_cr_geometry:
                data[i][j] = geometric;
                geometric *= parameter;
                break;
            default:
                printf("error in type of sequence, %d;\n", type);
                return -1;
            }
    return 0;
}

int matrix_roll(int data[OBJECTS_MAX][OBJECTS_MAX], int columns, int rows, int counter, enum matrix_type type)
{
    if (type < mx_roll_left || type > mx_roll_down || columns >= OBJECTS_MAX || rows >= OBJECTS_MAX ||
            columns < 1 || rows < 1) {
        printf("error in array size, rows = %d, columns = %d or rolling type = %d incorrect;\n",
               rows, columns, type);
        return -1;
    }
    for (int k = 0; k < counter; ++k)
        switch (type) {
        case mx_roll_left:
            for (int i = 0; i < rows; ++i) {
                int element = data[i][0];
                for (int j = 0; j < columns - 1; ++j)
                    data[i][j] = data[i][j + 1];
                data[i][columns - 1] = element;
            }
            break;
        case mx_roll_right:
            for (int i = 0; i < rows; ++i) {
                int element = data[i][columns - 1];
                for (int j = columns - 1; j > 0; --j)
                    data[i][j] = data[i][j - 1];
                data[i][0] = element;
            }
            break;
        case mx_roll_up:
            for (int j = 0; j < columns; ++j) {
                int element = data[0][j];
                for (int i = 0; i < rows - 1; ++i)
                    data[i][j] = data[i + 1][j];
                data[rows - 1][j] = element;
            }
            break;
        case mx_roll_down:
            for (int j = 0; j < columns; ++j) {
                int element = data[rows - 1][j];
                for (int i = rows - 1; i > 0; --i)
                    data[i][j] = data[i - 1][j];
                data[0][j] = element;
            }
            break;
        default:
            printf("error in roll type %d",type);
            return -1;
        }
    return 0;
}


int matrix_info(int data[OBJECTS_MAX][OBJECTS_MAX], int* columns, int* rows, enum matrix_type type)
{
    if (*columns < 0 || *rows < 0 || *columns > OBJECTS_MAX || *rows > OBJECTS_MAX ||
            type < mx_info_status || type >= mx_end) {
        printf("error: columns = %d, rows = %d, type = %d;\n", *columns, *rows, type);
        return -1;
    }
    int result = 0, counter = 0, square = 0, start_row = 0, start_column = 0, element = 0,
            first_last = 0, idx_col = 0, idx_row = 0, max = 0, min = 0, len_col = *columns,
            len_row = *rows, pair_mod = 0, pairs = 0;
    result = ((type & matrix_act_mask) == mx_info_multiply) ? 1 : 0;
    square = (type & mx_mod_sq) ? 1 : 0;
    start_column = (type & mx_mod_col) ? len_col++ : 0;
    start_row = (type & mx_mod_row) ? len_row++ : 0;
    first_last = (type & mx_mod_last) ? 1 : 0;
    pair_mod = (type & (mx_mod_col | mx_mod_row));
    max = min = data[start_row][start_column];
    idx_col = start_column; idx_row = start_row;
    //printf("square = %d, start column = %d, start row = %d, row = %d;\n", square, start_column, start_row, *rows);
    for (int i = start_row; i < len_row; ++i)
        for (int j = start_column; j < len_col; ++j) {
            if (!square)
                element = data[i][j];
            else
                element = data[i][j] * data[i][j];
            switch (type & matrix_act_mask) {
            case mx_info_sum:
                result += element;
                break;
            case mx_info_multiply:
                result *= element;
                break;
            case mx_info_avr:
                result += element;
                counter++;
                break;
            case mx_info_idxs:
                result += i + j;
                break;
            case mx_info_max:
                if ((first_last && data[i][j] >= max) || (!first_last && data[i][j] > max)) {
                    max = data[i][j];
                    idx_row = i;
                    idx_col = j;
                }
                break;
            case mx_info_min:
                if ((first_last && data[i][j] <= min) || (!first_last && data[i][j] < min)) {
                    min = data[i][j];
                    idx_row = i;
                    idx_col = j;
                }
                break;
            case mx_info_pairs: //В парах учитывае оба модификатора.
                if ((i > 0 && (pair_mod & mx_mod_row) != 0) && (element == data[i - 1][j]))
                    ++pairs;
                if ((j > 0 && (pair_mod & mx_mod_col) != 0) && (element == data[i][j - 1]))
                    ++pairs;
                break;
            default:
                printf("incorrect type of action %d;\n", type & matrix_act_mask);
                return -1;
            }
        }
    if (counter)
        result /= counter;
    if ((type & matrix_act_mask) == mx_info_max || (type & matrix_act_mask) == mx_info_min) {
        *columns = idx_col;
        *rows = idx_row;
        if ((type & matrix_act_mask) == mx_info_max)
            result = max;
        else
            result = min;
    }
    if ((type & matrix_act_mask) == mx_info_pairs)
        result = pairs;
    return result;
}

int matrix_check_element(int data[OBJECTS_MAX][OBJECTS_MAX], int column, int row, int parameter ,enum matrix_type check)
{
    if (column < 0 || row < 0 || column >= OBJECTS_MAX || row >= OBJECTS_MAX) {
        printf("error check element: columns = %d, rows = %d, type = %d;\n", column, row, check);
        return -1;
    }
    switch (check) {
    case mx_chk_equal:
        return (data[row][column] == parameter);
    case mx_chk_more:
        return (data[row][column] > parameter);
    case mx_chk_less:
        return (data[row][column] < parameter);
    case mx_chk_div:
        return (data[row][column] % parameter == 0);
    case mx_chk_not_div:
        return (data[row][column] % parameter != 0);
    case mx_chk_idxs:
        return ((row + column) % parameter == 0);
        /*                  немного обновить
    case mx_chk_pairs:
        if (parameter == 0 && row != 0)
            return (data[row][column] == data[row - 1][column]);
        if (parameter == 1 && column != 0)
            return (data[row][column] == data[row][column - 1]);
        if (parameter == 2 && row < OBJECTS_MAX - 1)
            return (data[row][column] == data[row + 1][column]);
        if (parameter == 3 && column < OBJECTS_MAX - 1) {
            return (data[row][column] == data[row][column + 1]);
        }
        return 0;
        */
    default:
        printf("error check element: columns = %d, rows = %d, type = %d;\n", column, row, check);
    }
    return -1;
}

int matrix_check_info(int data[OBJECTS_MAX][OBJECTS_MAX], int columns, int rows, int* par_cnt, enum matrix_type check)
{   // параметр сначала используется как параметр, а потом как счётчик, вернуть.
    if (columns < 0 || rows < 0 || columns > OBJECTS_MAX || rows > OBJECTS_MAX ||
            check < mx_info_status || check >= mx_end) {
        printf("error: columns = %d, rows = %d, type = %d;\n", columns, rows, check);
        return -1;
    }
    int result = 0, square = 0, start_row = 0, start_column = 0,
            element = 0, check_type = 0, par = *par_cnt; *par_cnt = 0;
    result = ((check & matrix_act_mask) == mx_info_multiply) ? 1 : 0;
    square = (check & mx_mod_sq) ? 1 : 0;
    start_column = (check & mx_mod_col) ? columns++ : 0;
    start_row = (check & mx_mod_row) ? rows++ : 0;
    for (int i = mx_chk_idxs; i <= mx_chk_pairs; i <<= 1)
        check_type = (check & i) ? i: check_type;
    //printf("square = %d, start column = %d, start row = %d;\n", square, start_column, start_row);
    for (int i = start_row; i < rows; ++i)
        for (int j = start_column; j < columns; ++j) {
            if (matrix_check_element(data,j,i,par,check_type)) {
                if (!square)
                    element = data[i][j];
                else
                    element = data[i][j] * data[i][j];
                switch (check & matrix_act_mask) {
                case mx_info_sum:
                    result += element;
                    break;
                case mx_info_multiply:
                    result *= element;
                    break;
                case mx_info_avr:
                    result += element;
                    break;
                case mx_info_idxs:
                    result += i + j;
                    break;
                default:
                    //printf("incorrect type of action %d;\n", check & matrix_act_mask);
                    return -1;
                }
                ++*par_cnt;
            }
        }
    if (*par_cnt && (check & matrix_act_mask) == mx_info_avr)
        result /= *par_cnt;
    return result;
}

int matrix_elements_copies(int data[OBJECTS_MAX][OBJECTS_MAX], int columns,  int rows, int counter)
{   // функция определения наличия n копий хотя бы одного элемента в массиве
    //возвращает кол-во элементов, счётчик копий которых задан в параметре.
    if (columns < 0 || rows < 0 || rows >= OBJECTS_MAX || columns >= OBJECTS_MAX || counter < 1)
        return -1;
    int quantity = 0, result = 0, j = 0, copies = 0;
    int uniq_elements[columns * rows];
    for (int i = 0; i < rows; ++i)
        for (int g = 0; g < columns; ++g) {
            int element = data[i][g];
            for (j = 0; j < quantity && element != uniq_elements[j]; ++j)
                ;
            if (j == quantity) {
                copies = 0;
                uniq_elements[quantity++] = element;
                for (int k = i * g; k < rows * columns; ++k)
                    if (element == data[k / columns][k % columns])
                        ++copies;
                if (copies == counter)
                    result++;
            }
        }
    return result;
}
int matrix_find_element(int data[OBJECTS_MAX][OBJECTS_MAX], int* columns, int* rows,
                        int par, enum matrix_type chk)
{
    if (*columns < 0 || *rows < 0 || *rows >= OBJECTS_MAX || *columns >= OBJECTS_MAX)
        return -1;
    int last_col = *columns, last_row = *rows, check_type = 0, result = 0, start_column = 0, start_row = 0;
    start_column = (chk & mx_mod_col) ? last_col++ : 0;
    start_row = (chk & mx_mod_row) ? last_row++ : 0;
    int first_last = (chk & mx_mod_last) ? 1 : 0;
    for (int i = mx_chk_idxs; i <= mx_chk_pairs; i <<= 1)
        check_type = (chk & i) ? i: check_type;
    for (int i = start_row; i < last_row && (!result || first_last); ++i)
        for (int j = start_column; j < last_col && (!result || first_last); ++j)
            if (matrix_check_element(data, j, i, par, check_type)) {
                *rows = i;
                *columns = j;
                result = 1;
            }
    return result;
}

int matrix_is_sequence(int data[OBJECTS_MAX][OBJECTS_MAX], int columns, int rows,
                       int parameter, enum matrix_type check)
{   //Функция определяет является ли матрица или её часть элементом последовательности
    //с условием по параметру.
    // Все элементы матрицы, строки или столбца должны удовлетворять условию проверки
    //на убывание или возрастание.
    if (columns < 0 || rows < 0 || rows >= OBJECTS_MAX || columns >= OBJECTS_MAX)
        return -1;
    int prev = 0, last_col = columns, last_row = rows, check_type = 0, start_column = 0, start_row = 0;
    start_column = (check & mx_mod_col) ? last_col++ : 0;
    start_row = (check & mx_mod_row) ? last_row++ : 0;
    for (int i = mx_chk_idxs; i <= mx_chk_asc; i <<= 1)
        check_type = (check & i) ? i: check_type;
    for (int i = start_row; i < last_row; ++i)
        for (int j = start_column; j < last_col; ++j) {
            if (i != start_row || j != start_column) {
                if (check_type == mx_chk_asc || check_type == mx_chk_dsc) {
                    if ((check_type == mx_chk_asc && data[i][j] <= prev) ||
                            (check_type == mx_chk_dsc && data[i][j] >= prev))
                        return 0;
                } else if (!matrix_check_element(data, i, j, parameter, check_type))
                    return 0;
            }
            prev = data[i][j];
        }
    return 1;
}

void chapter_12()
{
    printf("12.1 - 12.21:\n");
    srand(time(NULL));
    int array[OBJECTS_MAX][OBJECTS_MAX];
    matrix_init(array,array,OBJECTS_MAX,OBJECTS_MAX, 1,mx_init_par);
    int x1 = rand() % 5, y1 = rand() % 5, x2 = rand() % 5,
            y2 = rand() % 5, value1 = 2 + rand() % 8, value2 = 2 + rand() % 8,
            length_x = 5, length_y = 5, tmp = 0;
    array[x1][y1] = value1;
    array[x2][y2] = value2;
    printf("source:\n");
    matrix_print(array,length_x,length_y,0,mx_prn_default);
    printf("replace elements from %d:%d to %d:%d position;\n",x1,y1,x2,y2);
    tmp = array[x1][y1];
    array[x1][y1] = array[x2][y2];
    array[x2][y2] = tmp;
    matrix_print(array,length_x,length_y,0,mx_prn_default);
    x1 = rand() % 5;
    printf("sum of elements and geometric mean, row = %d\n",x1);
    int sum = 0, mean_geom = 1, i = 0, j = 0, k = 0;
    for (i = 0; i < length_x; ++i) {
        sum += array[x1][i];
        mean_geom *= array[x1][i];
    }
    mean_geom = sqrt(mean_geom);
    printf("sum = %d, geom mean = %d;\n", sum, mean_geom);
    printf("which element is greater than 5 and even: ");
    if (array[x1][y1] > 5 && array[x1][y1] % 2 == 0) {
        printf("Elements #1 on %d:%d, ",x1,y1);
        ++k;
    }
    if (array[x2][y2] > 5 && array[x2][y2] % 2 == 0) {
        printf("Elements #2 on %d:%d;",x2,y2);
        ++k;
    }
    printf(" %d elements total;\n\n",k);
    printf("12.23 - 12.25;\n");
    int rows = 2, columns = 3;
    /*
    for (enum matrix_type init = mx_nop; init <= mx_init_row; ++init) {
        printf("%s\n",matrix_type_name[init]);
        matrix_init(array,array_init,rows,columns,0,init);
        matrix_print(array,rows,columns,0,mx_prn_default);
    }
    */
    /*
    for (enum matrix_type seq = mx_cr_val, roll = mx_roll_left; seq <= mx_cr_geometry; ++seq, ++roll) {
        printf("%s\n",matrix_type_name[seq]);
        matrix_create_sequence(array,rows,columns,rand_max,seq);
        matrix_print(array,rows,columns,0,mx_prn_default);
        printf("%s\n",matrix_type_name[roll]);
        matrix_roll(array,rows,columns,1,roll);
        matrix_print(array,rows,columns,0,mx_prn_default);
    }
    */
    matrix_create_sequence(array,length_x,length_y,1,mx_cr_ariphmetic);
    printf("source:\n");
    matrix_print(array,length_x,length_y,0,mx_prn_default);
    printf("total:\n");
    length_x = length_y = 5;
    for (i = 0; i < 5; ++i)
        matrix_roll(array,length_x,i,i,mx_roll_down);
    matrix_print(array,length_x,length_y,0,mx_prn_default);
    printf("12.26 - 12.27;\n");
    for (i = 0; i < length_x; ++i)
        for (j = 0; j < length_y; ++j)
            if (j % 2 == 0)
                array[i][j] = 1;
            else
                array[i][j] = 0;
    printf("source:\n");
    matrix_print(array,length_x,length_y,0,mx_prn_default);
    for (i = 0; i < length_x; ++i)
        if (i % 2 != 0)
            for (j = 0; j < length_y; ++j)
                array[i][j] = !array[i][j];
    printf("total:\n");
    matrix_print(array,length_x,length_y,0,mx_prn_default);
    printf("\n12.28 - 12.30;\n");
    char* dir_name[] = { "north", "east", "south", "west" };
    const int directions = 4;
    int data_dir[4][2] = { {0, -1}, {+1, 0}, {0, +1}, {-1, 0} };
    columns = 1, rows = 7, j = 0, k = 0;
    int number = 1, next_row = 0, next_column = 0, move_dir = 1, trail_size = 0, move_size = 0;
    int data_trail[OBJECTS_MAX][2];
    matrix_init(array,array,columns,rows,0,mx_init_par);
    while (array[next_row][next_column] == 0 && next_column >= 0 && next_row >= 0 &&
           next_column < columns && next_row < rows) {
        printf("next column = %d, next row = %d and directions = %d:%d;\n",
               next_column, next_row, data_dir[move_dir][0], data_dir[move_dir][1]);
        array[next_row][next_column] = number++;
        move_size++;
        if ((next_column + data_dir[move_dir][0] == columns) ||
                (next_column + data_dir[move_dir][0] == -1) ||
                (next_row + data_dir[move_dir][1] == rows) ||
                (next_row + data_dir[move_dir][1] == -1) ||
                array[next_row + data_dir[move_dir][1]][next_column + data_dir[move_dir][0]] != 0) {
            data_trail[trail_size][0] = move_dir;
            data_trail[trail_size][1] = move_size;
            trail_size++;
            move_size = 0;
            move_dir = (move_dir + 1) % directions;
        }
        next_row += data_dir[move_dir][1];
        next_column += data_dir[move_dir][0];
        matrix_print(array,columns,rows,0,mx_prn_default);
    }
    /*
    while (columns >= 0 && rows >= 0) {
        if (k % 2 == 0) {
            for (int i = 0; i < columns; ++i) {
                array[x][y] = number++;
                if (i != columns - 1)
                    y += data_dir[k][1];
            }
            x += data_dir[k][0];
            data_trail[j][0] = k;
            data_trail[j++][1] = columns;
            --columns;
        } else {
            for (int i = 0; i < rows; ++i) {
                array[x][y] = number++;
                if (i != rows - 1)
                    x += data_dir[k][0];
                printf("%d:%d\n", x, y);
                matrix_print(array,length_x,length_y,0,mx_prn_default);
            }
            y += data_dir[k][1];
            data_trail[j][0] = k;
            data_trail[j++][1] = rows;
            --rows;
        }
        k = (k + 1) % directions;
    }
    */
    //matrix_print(array,length_x,length_y,0,mx_prn_default);
    printf("next column was %d, next row was %d, move direct = %s, to opposite direct;\n",
           next_column,next_row,dir_name[move_dir]);
    next_row -= data_dir[move_dir][1];
    next_column -= data_dir[move_dir][0];
    printf("reading all elements to sequence, from %d column, %d rows;\n",next_column,next_row);
    printf("trail length(elements):\n");
    for (i = trail_size; i >= 0; --i) {
        move_dir = data_trail[i][0];
        printf("%s:%d (",dir_name[data_trail[i][0]], data_trail[i][1]);
        for (j = 0; j < data_trail[i][1]; ++j) {
            printf("%d ",array[next_row][next_column]);
            next_row -= data_dir[move_dir][1];
            next_column -= data_dir[move_dir][0];
        }
        printf(")\n");
    }
    printf("\n12.31;\n");
    number = 0;
    length_x = 3, length_y = 3;
    int array_add[length_x];
    uniq_gen_fast_alt(array_add,length_x,length_x);
    for (i = 0; i < length_x; ++i, number += length_y)
        uniq_gen_fast_alt_1(array[array_add[i]],number,length_y);
    matrix_print(array,length_x,length_y,0,mx_prn_default);
    printf("12.32 - 12.34, printf matrix;\n");
    matrix_print(array,length_x,length_y,0,mx_prn_default); //Вывод зависит от типа enum-a
    printf("\nflip matrix horizontal:\n");
    matrix_print(array,length_x,length_y,0,mx_prn_fliph);
    printf("\nflip matrix vertical:\n");
    matrix_print(array,length_x,length_y,0,mx_prn_flipv);
    printf("\n12.35 - 12.46;\nsource matrix for all tasks, indexes from 0:\n");
    rows = 4; columns = 6;
    matrix_create_sequence(array,columns,rows,1,mx_cr_ariphmetic);
    matrix_print(array,columns,rows,0,mx_prn_default);
    int a1 = 2, a2 = 2;
    printf("\n12.35, sum of elements %d row and sum of %d colmn;\n", a1, a2);
    int result = matrix_info(array,&columns, &a1, mx_info_sum | mx_mod_row);
    printf("a) sum = %d;\n",result);
    result = matrix_info(array, &a2, &rows, mx_info_sum | mx_mod_col);
    printf("b) sum = %d;\n",result);
    printf("\n12.38, 12.41, source matrix:\n");
    number = 3; columns = 5; rows = 5;
    int rand_max = 10;
    matrix_create_sequence(array,columns,rows,rand_max,mx_cr_rnd);
    matrix_print(array,columns,rows,0,mx_prn_default);
    result = matrix_info(array, &number, &rows, mx_info_sum | mx_mod_col);
    printf("sum of scores spotrsmans = %d, column = %d;\n",result, number);
    result = matrix_info(array, &columns, &number, mx_info_sum | mx_mod_row);
    printf("sum of salary = %d, row = %d;\n", result, number);
    printf("\n12.44;\n");
    number = 3; columns = 5; rows = 5;
    matrix_print(array,columns,rows,0,mx_prn_default);
    result = matrix_info(array, &number, &rows, mx_info_sum | mx_mod_col);
    printf("students counter = %d, column = %d;\n",result, number);
    printf("\n12.47, multiply of %d row;\n", a1);
    result = matrix_info(array, &columns, &a1, mx_info_multiply | mx_mod_row);
    printf("multiply = %d;\n",result);
    printf("\n12.48;\n");
    matrix_print(array,columns,rows,0,mx_prn_default);
    a1 = 2; a2 = 3;
    result = matrix_info(array, &columns, &a1, mx_info_sum | mx_mod_sq | mx_mod_row);
    printf("a) sum of square(row = %d) = %d;\n",a1,result);
    result = matrix_info(array, &a2, &rows, mx_info_sum | mx_mod_sq | mx_mod_col);
    printf("b) sum of square(column = %d) = %d;\n\n",a2,result);
    printf("12.50, 12.55;\n");
    matrix_print(array,columns,rows,0,mx_prn_default);
    a1 = 2; a2 = 3;
    result = matrix_info(array, &columns, &a1, mx_info_avr | mx_mod_row);
    printf("a) average(row = %d) = %d;\n",a1,result);
    result = matrix_info(array, &a2, &rows, mx_info_avr | mx_mod_col);
    printf("b) average(column = %d) = %d;\n\n",a2,result);
    printf("12.56;\n");
    matrix_print(array,columns,rows,0,mx_prn_default);
    result = matrix_info(array, &columns, &rows, mx_info_sum);
    printf("a) sum of all elements = %d;\n",result);
    result = matrix_info(array, &columns, &rows, mx_info_sum | mx_mod_sq);
    printf("b) sum of square all elements = %d;\n",result);
    result = matrix_info(array, &columns, &rows, mx_info_avr);
    printf("c) average of all elements = %d;\n\n",result);
    printf("12.59;\n");
    a1 = 0;
    matrix_print(array, columns, rows, 0, mx_prn_default);
    result = matrix_check_info(array, columns, rows, &a1 ,mx_chk_equal | mx_info_sum);
    printf("equal 0 = %d;\n\n",a1);
    printf("12.61;\n");
    matrix_print(array, columns, rows, 0, mx_prn_default);
    double average_rating = 0;
    result = matrix_info(array, &columns, &rows, mx_info_sum);
    average_rating = (double)result / (double)(columns * rows);
    printf("scores of students = %.2f;\n\n",average_rating);
    printf("12.65, scores of students;\n");
    columns = 3, rows = 3;
    double max_d = 0;
    int idx = 0;
    for (k = 0; k < 3; ++k) {
        printf("group #%d:\n", k);
        matrix_create_sequence(array,columns,rows,10,mx_cr_rnd);
        matrix_print(array, columns, rows, 0, mx_prn_default);
        result = matrix_info(array, &columns, &rows, mx_info_sum);
        average_rating = (double)result / (double)(columns * rows);
        printf("average = %.2f;\n\n", average_rating);
        if (average_rating > max_d) {
            max_d = average_rating;
            idx = k;
        }
    }
    printf("max ratinf of groups #%d = %.2f;\n", idx, max_d);
    printf("12.67, 12.69, 12.72;\nsource matrix:\n");
    columns = 5; rows = 5;
    matrix_create_sequence(array,columns,rows,-rand_max,mx_cr_rnd);
    matrix_print(array, columns, rows, 0, mx_prn_default);
    char* tasks[] = {"\n12.67\na) sum negative elements of 4-th row:",
                     "b) sum elements less than 5 of 3-rd column:",
                     "c) counter of elements of 3-rd row less than -3:",
                     "d) counter of elements of 1-st column more than -5:",
                     "\n12.69\na) average of odd elements of 2-nd row:",
                     "b) average of 3-th column, divided by 4:",
                     "\n12.72\na) sum of even elements: ",
                     "b) counter of elements less than 0: ",
                     "c) average of odd elements: ",
                     "d) sum of elements, indexes divided by 3: "
                    };
    enum matrix_type tasks_type[] = {mx_info_sum | mx_chk_less | mx_mod_row,    //12.67 a
                                     mx_info_sum | mx_chk_less | mx_mod_col,
                                     mx_chk_less | mx_mod_row | mx_info_sum,
                                     mx_chk_more | mx_mod_col | mx_info_sum,
                                     mx_info_avr | mx_mod_row | mx_chk_not_div,
                                     mx_info_avr | mx_mod_col | mx_chk_div,
                                     mx_info_sum | mx_chk_div,
                                     mx_info_sum |mx_chk_less,
                                     mx_info_avr | mx_chk_not_div,
                                     mx_info_sum | mx_chk_idxs
                                    };
    int tasks_par[] = {columns, 4, 0, //12.67 a;  параметры задачи: столбц(ы), строк(и), параметр проверки
                       3, rows, 5,
                       columns, 3, -3,
                       1, rows, -5,
                       columns, 2, 2,
                       3, rows, 4,
                       columns, rows, 2,
                       columns, rows, 0,
                       columns, rows, 2,
                       columns, rows, 3};
    for (i = 0; i < 10; ++i) {
        result = matrix_check_info(array, tasks_par[i * 3], tasks_par[i * 3 + 1], &tasks_par[i * 3 + 2],
                tasks_type[i]);
        if (i != 2 && i != 3 && i != 7)
            printf("%s %d;\n", tasks[i], result);
        else
            printf("%s %d;\n", tasks[i], tasks_par[i * 3 + 2]);
    }
    printf("\n12.73, search max and min:\n");
    int max = array[0][0], min = array[0][0];
    a1 = 1; a2 = 1;
    for (i = 0; i < rows; ++i)
        for (j = 0; j < columns; ++j) {
            if (array[i][j] > max) {
                a1 = 1;
                max = array[i][j];
            }
            if (array[i][j] == max)
                a1++;
            if (array[i][j] < min) {
                a2 = 1;
                min = array[i][j];
            }
            if (array[i][j] == min)
                a2++;
        }
    printf("a) max = %d, counter = %d;\n", max, a1);
    printf("b) min = %d, counter = %d;\n", min, a2);
    printf("\n12.74 - 12.75, pairs counter and signs;\n");
    matrix_create_sequence(array,columns,rows,-rand_max,mx_cr_rnd);
    matrix_print(array, columns, rows, 2, mx_prn_default | mx_prn_field);
    a1 = 0; a2 = 0;
    const int pairs_types = 3;
    int pairs[] = {0, 0, 0}, sign = (array[0][0] >= 0) ? 1 : -1;
    int counter = 0;
    char* pairs_names[] = {"pairs in row", "pairs in column", "pairs in row and column"};
    printf("All elements pairs in matrix with indexes;\n");
    for (i = 0; i < rows; ++i)
        for (j = 0; j < columns; ++j) {
            int p[3];
            if ((sign == 1 && array[i][j] < 0) || (sign == -1 && array[i][j] >= 0)) {
                sign *= -1;
                counter++;
            }
            p[0] = (i < rows - 1 && array[i][j] == array[i + 1][j]);
            p[1] = (j < columns - 1 && array[i][j] == array[i][j + 1]);
            p[2] = (p[0] && p[1]);
            for (k = 0; k < pairs_types; ++k) {
                if (p[k]) {
                    printf("%s = %d[%d:%d]\n",pairs_names[k], array[i][j], i, j);
                    ++pairs[k];
                }
            }
        }
    printf("pairs counter:\n");
    for (i = 0; i < pairs_types; ++i)
        printf("%d ", pairs[i]);
    printf("\nSign chg = %d;\n",counter);
    printf("\n12.77, parameters for each column;\nsource matrix:\n");
    matrix_print(array, columns, rows, 2, mx_prn_default | mx_prn_field);
    printf("a, sum of odd elements:\n");
    for (i = 0; i < columns; ++i) {
        a1 = 2;
        result = matrix_check_info(array, i, rows, &a1, mx_info_sum | mx_chk_not_div | mx_mod_col);
        printf("column #%d = %d;\n", i, result);
    }
    printf("\nb, counter of all positive elements:\n");
    for (i = 0; i < columns; ++i) {
        a1 = -1;
        result = matrix_check_info(array, i, rows, &a1, mx_info_sum | mx_chk_more | mx_mod_col);
        printf("column #%d = %d;\n", i, a1);
    }
    printf("\nc, counter elements divided 2 or 3:\n");
    for (i = 0; i < columns; ++i) {
        for (j = 0, counter = 0; j < rows; ++j)
            if (array[j][i] % 2 == 0 || array[j][i] % 3 == 0)
                ++counter;
        printf("column #%d = %d;\n", i, counter);
    }
    printf("\n12.78 - 12.79, pairs in matrix;\nsource matrix:\n");
    rand_max = 5;
    matrix_create_sequence(array,columns,rows,rand_max,mx_cr_rnd);
    matrix_print(array, columns, rows, 0, mx_prn_default);
    printf("a, pairs and sum of each row;\n");
    for (i = 0, result = 0, sum = 0; i < rows; ++i) {
        result += matrix_info(array, &columns, &i, mx_info_pairs | mx_mod_row);
        sum = matrix_info(array, &columns, &i, mx_info_sum | mx_mod_row);
        printf("%d: pairs = %d, rows = %d;\n", i, result, sum);
    }
    printf("b, pairs and sum of each column;\n");
    for (j = 0, result = 0, sum = 0; j < columns; ++j) {
        result += matrix_info(array, &j, &rows, mx_info_pairs | mx_mod_col);
        sum = matrix_info(array, &j, &rows, mx_info_sum | mx_mod_col);
        printf("%d: pairs = %d, column = %d;\n", j, result, sum);
    }
    printf("\n12.80, find uniq elements in matrix;\n");
    rand_max = 10;
    i = 0; j = 0; counter = 0; rows = 5; columns = 5;
    matrix_create_sequence(array,columns,rows,rand_max,mx_cr_rnd);
    matrix_print(array, columns, rows, 0, mx_prn_default);
    printf("First variant(linean search):\n");
    for (i = 0; i < rows * columns; ++i)
        for (j = 0; j < rows * columns; ++j, ++counter) {
            if ((array[i / columns][i % columns] == array[j / columns][j % columns]) && i != j)
                break;
            if (j == (rows * columns - 1))
                printf("%d[%d] ", array[i / columns][i % columns], counter);
        }
    printf("counter = %d\n", counter);
    printf("Second variant(rewrite array):\n");
    for (i = 0, counter = 0; i < rows * columns; ++i) {
        int is_find = 0;
        for (j = i + 1; j < rows * columns && array[i / columns][i % columns] != -1; ++j, ++counter) {
            if (array[i / columns][i % columns] == array[j / columns][j % columns]) {
                array[j / columns][j % columns] = -1;
                is_find = 1;
            }
        }
        if (!is_find && array[i / columns][i % columns] != -1)
            printf("%d[%d] ", array[i / columns][i % columns], counter);
    }
    printf("counter = %d", counter);
    printf("\nThird variant(Using big extra array):\n");
    int copies_array[OBJECTS_MAX], copies = 0, element = 0; //Если много, то отвал
    matrix_create_sequence(array,columns,rows,rand_max,mx_cr_rnd);
    //matrix_print(array, columns, rows, 0, mx_prn_default);
    for (i = 0, counter = 0; i < rows * columns; ++i) {
        element = array[i / columns][i % columns];
        for (j = 0; j < copies && element != copies_array[j]; ++j, ++counter)
            ;
        if (j == copies) {
            //printf("\ncache missed, ");
            for (j = 0; j < rows * columns; ++j, ++counter)
                if ((element == array[j / columns][j % columns]) && i != j)
                    break;
            if (j == rows * columns) {
                printf("uniq %d[%d]\n", element, counter);
            } else {
                //printf("add to cache %d[%d] ", element, counter);
                copies_array[copies++] = element;
            }
        } else
            printf(";");//printf("cache hit, element = %d\n", element);
    }
    printf("counter = %d", counter);
    printf("\n\n12.84, search max and min;\nsource matrix:\n");
    matrix_print(array, columns, rows, 0, mx_prn_default);
    length_x = columns; length_y = 1;
    result = matrix_info(array, &length_x, &length_y, mx_info_max | mx_mod_row);
    printf("max = %d (%d:%d);\n",result, length_y, length_x);
    length_x = 1; length_y = rows;
    result = matrix_info(array, &length_x, &length_y, mx_info_min | mx_mod_col);
    printf("min = %d (%d:%d);\n",result, length_y, length_x);
    printf("\n12.88, search in full matrix;\n");
    length_x = columns; length_y = rows;
    result = matrix_info(array, &length_x, &length_y, mx_info_max | mx_mod_last);
    printf("last max = %d (%d:%d);\n",result, length_y, length_x);
    length_x = columns; length_y = rows;
    result = matrix_info(array, &length_x, &length_y, mx_info_min | mx_mod_last);
    printf("last min = %d (%d:%d);\n",result, length_y, length_x);
    printf("\n12.89, search max from left:up, min from right:down;\n");
    length_x = columns; length_y = rows;
    result = matrix_info(array, &length_x, &length_y, mx_info_max);
    printf("first max = %d (%d:%d);\n",result, length_y, length_x);
    length_x = columns; length_y = rows;
    result = matrix_info(array, &length_x, &length_y, mx_info_min | mx_mod_last);
    printf("last min = %d (%d:%d);\n",result, length_y, length_x);
    printf("\n12.93, search sum of max elements in every row, sum of min elements in every column;\n");
    max = min = array[0][0];
    int max_idx = 0;
    for (i = 0; i < rows; ++i) {
        result = matrix_info(array, &columns, &i, mx_info_sum | mx_mod_row);
        if (max < result) {
            max = result;
            max_idx = i;
        }
    }
    printf("max = %d, row = %d\n", max, max_idx);
    for (i = 0; i < columns; ++i) {
        result = matrix_info(array, &i, &rows, mx_info_sum | mx_mod_col);
        if (max < result) {
            max = result;
            max_idx = i;
        }
    }
    printf("max = %d, col = %d\n\n", max, max_idx);
    printf("12.94, students in classes;\n");
    rows = 3; columns = 5;
    matrix_print(array, columns, rows, 0, mx_prn_default);
    for (i = 0, max_idx = 0, max = -1; i < rows; ++i) {
        result = matrix_info(array, &columns, &i, mx_info_sum | mx_mod_row);
        if (result > max || max == -1) {
            max = result;
            max_idx = i;
        }
    }
    printf("max = %d, row = %d;\n", max, max_idx);
    for (i = 0, max_idx = 0, min = -1; i < rows; ++i) {
        result = matrix_info(array, &columns, &i, mx_info_sum | mx_mod_row);
        if (result < min || min == -1) {
            min = result;
            max_idx = i;
        }
    }
    printf("min = %d, row = %d;\n",min , max_idx);
    printf("\n12.97, search first max row and last min column;\n");
    matrix_print(array, columns, rows, 0, mx_prn_default);
    for (i = 0, max_idx = 0, max = -1; i < rows; ++i) {
        result = matrix_info(array, &columns, &i, mx_info_sum | mx_mod_row);
        if (result > max || max == -1) {
            max = result;
            max_idx = i;
        }
    }
    printf("max = %d, row = %d;\n", max, max_idx);
    for (i = 0, max_idx = 0, min = -1; i < columns; ++i) {
        result = matrix_info(array, &i, &rows, mx_info_sum | mx_mod_col);
        if (result <= min || min == -1) {
            min = result;
            max_idx = i;
        }
    }
    printf("min = %d, column = %d;\n\n",min , max_idx);
    rows = 5; columns = 5;
    printf("12.100 - 12.101;\n");
    printf("Teams in games:\n");
    int score[] = {0, 1, 3};
    for (i = 0; i < rows; ++i)
        for (j = 0; j < i; ++j) {
            a1 = rand() % 3;
            array[i][j] = score[a1];
            array[j][i] = score[2 - a1];
        }
    printf("   ");
    for (i = 0; i < columns; ++i)
        printf("%d  ", i + 1);
    printf("\n");
    for (i = 0; i < rows; ++i) {
        printf("%d: ", i + 1);
        for (j = 0; j < columns; ++j)
            if (i != j)
                printf("%d  ",array[i][j]);
            else
                printf("-  ");
        printf("\n");
    }
    max = 0, min = 3 * rows, a1 = 0, a2 = 0;
    for (i = 0; i < rows; ++i) {
        sum = 0;
        for (j = 0; j < columns; ++j) {
            if (i != j)
                sum += array[i][j];
        }
        if (sum > max) {
            max = sum;
            a1 = i;
        }
        if (sum < min) {
            min = sum;
            a2 = i;
        }
    }
    printf("Winner: score = %d, number = %d;\n", max, a1 + 1);
    printf("Loser: score = %d, number = %d;\n\n", min, a2 + 1);
    printf("12.104, 12.108, max in pairs of rows;\n");
    max = 0, a1 = 0;
    matrix_create_sequence(array, columns, rows, rand_max, mx_cr_rnd);
    matrix_print(array, columns, rows, 0, mx_prn_default);
    int sum_1 = 0, sum_2 = 0;
    for (i = 0, max_idx = 0; i < rows - 1; ++i) {
        length_x = i;
        sum_1 = matrix_info(array, &columns, &length_x, mx_info_sum | mx_mod_row);
        length_x++;
        sum_2 = matrix_info(array, &columns, &length_x, mx_info_sum | mx_mod_row);
        printf("sum_1 = %d, sum_2 = %d;\n", sum_1, sum_2);
        if (sum_1 + sum_2 > max) {
            max = sum_1 + sum_2;
            max_idx = i;
        }
    }
    printf("max sum = %d, rows = %d and %d;\n", max, max_idx, max_idx + 1);
    printf("\n12.103, 12.107, min in pairs of columns;\n");
    sum_1 = 0, sum_2 = 0; min = columns * rand_max;
    for (i = 0, max_idx = 0; i < columns - 1; ++i) {
        length_y = i;
        sum_1 = matrix_info(array, &length_y, &rows, mx_info_sum | mx_mod_col);
        length_y++;
        sum_2 = matrix_info(array, &length_y, &rows, mx_info_sum | mx_mod_col);
        printf("sum_1 = %d, sum_2 = %d;\n", sum_1, sum_2);
        if (sum_1 + sum_2 < min) {
            min = sum_1 + sum_2;
            max_idx = i;
        }
    }
    printf("min sum = %d, columns = %d and %d;\n", min, max_idx, max_idx + 1);
    max = rand() % rand_max * 4;
    printf("\n12.113, sum of salaries more than %d?;\n", max);
    matrix_print(array, columns, rows, 0, mx_prn_default);
    length_y = 1;
    result = matrix_info(array, &columns, &length_y, mx_mod_row | mx_info_sum);
    printf("Sum = %d;\n", result);
    if (result > max)
        printf("Yes;\n\n");
    else if (result < max)
        printf("No;\n\n");
    else
        printf("Equal;\n\n");
    printf("12.115;\nPlaces:\n");
    unsigned char places[] = {0, 0, 0, 0, 0}, taken = 0;
    for (i = 0; i < 5; ++i) {
        places[i] = rand() % (UCHAR_MAX + 1);
        printf("%d:\t", i);
        print_binary_byte(places[i]);
        for (unsigned char mask = 1; mask; mask <<= 1)
            if (places[i] & mask)
                ++taken;
        printf(", taken = %d\n", taken);
    }
    printf("Taken places: %d;\nFree places: %d;\n\n", taken, (5 * CHAR_BIT) - taken);
    printf("12.120, comparing sums of column and row values;\n");
    matrix_print(array, columns, rows, 0, mx_prn_default);
    length_y = 0;
    sum_1 = matrix_info(array, &length_y, &rows, mx_mod_col | mx_info_sum);
    length_y = columns - 1;
    sum_2 = matrix_info(array, &length_y, &rows, mx_mod_col | mx_info_sum);
    printf("a)sum of values less in first(%d) or last(%d) column?;\n", sum_1, sum_2);
    if (sum_1 > sum_2)
        printf("in first;\n");
    else if (sum_2 > sum_1)
        printf("in last;\n");
    else
        printf("sum is equal;\n");
    length_x = 0;
    sum_1 = matrix_info(array, &columns, &length_x, mx_mod_row | mx_info_sum);
    length_x = rows - 1;
    sum_2 = matrix_info(array, &columns, &length_x, mx_mod_row | mx_info_sum);
    printf("b)sum of values more in first(%d) or last row(%d)?;\n", sum_1, sum_2);
    if (sum_1 > sum_2)
        printf("in first;\n");
    else if (sum_2 > sum_1)
        printf("in last;\n");
    else
        printf("sum is equal;\n");
    printf("\n12.123, the salary of all employees in 1-st column is less than in last column?;\n");
    length_y = 0;
    sum_1 = matrix_info(array, &length_y, &rows, mx_mod_col | mx_info_sum);
    length_y = columns - 1;
    sum_2 = matrix_info(array, &length_y, &rows, mx_mod_col | mx_info_sum);
    printf("First = %d;\nLast = %d;\n", sum_1, sum_2);
    if (sum_1 > sum_2)
        printf("Yes;\n");
    else if (sum_2 > sum_1)
        printf("No;\n");
    else
        printf("Sum is equal;\n");
    printf("\n12.125, find the largest family on the 3rd and 4th floor;\n");
    length_x = 3;
    length_y = columns;
    sum_1 = matrix_info(array, &length_y, &length_x, mx_mod_row | mx_info_max);
    printf("On the 3rd floor(%d:%d) = %d;\n", length_x, length_y, sum_1);
    length_x = 4;
    length_y = columns;
    sum_2 = matrix_info(array, &length_y, &length_x, mx_mod_row | mx_info_max);
    printf("On the 4rd floor(%d:%d) = %d;\n\n", length_x, length_y, sum_2);
    printf("12.126;\n");
    result = matrix_info(array, &columns, &rows, mx_info_avr);
    min = 10;
    int idx_1 = 0, idx_2 = 0;
    for (i = 0; i < rows && min > 0; ++i) {
        printf("%d:\t", i);
        for (j = 0; j < columns && min > 0; ++j) {
            int offset = abs(array[i][j] - result);
            printf("%d ", offset);
            if (offset < min) {
                min = offset;
                idx_1 = i;
                idx_2 = j;
            }
        }
        printf("\n");
    }
    printf("Average = %d, min = %d, row = %d, column = %d;\n", result, min, idx_1, idx_2);
    printf("\n\n12.130, football championship;\n");
    int teams_counter = 5;
    int teams[teams_counter][teams_counter];
    rand_max = 3;
    //score[] = {0, 1, 3};
    for (i = 0; i < teams_counter; ++i)
        for (j = 0; j < i; ++j) {
            if (i != j)
                number = rand() % rand_max;
            else
                number = 0;
            teams[i][j] = score[number];
            teams[j][i] = score[rand_max - number - 1];
        }
    printf("   ");
    for (i = 0; i < teams_counter; ++i)
        printf("%d\t  ", i + 1);
    printf("\n");
    for (i = 0; i < teams_counter; ++i) {
        printf("%d: ", i + 1);
        for (j = 0; j < teams_counter; ++j) {
            if (i != j) {
                if (teams[i][j] == score[rand_max - 1])
                    printf(" Win\t");
                else if (teams[i][j] == score[rand_max - 2])
                    printf("Draw\t");
                else
                    printf("Lose\t");
            } else
                printf("  -\t");
        }
        printf("\n");
    }
    int quantity = 0, is_lose = 0, win = 0, lose = 0, total = 0;
    for (i = 0, result = 0, idx = 0, max = 0; i < teams_counter; ++i) {
        counter = 0;
        is_lose = 0;
        win = 0;
        lose = 0;
        sum = 0;
        for (j = 0; j < teams_counter; ++j) {
            if (i != j) {
                if (teams[i][j] == 3)
                    win++;
                else if (teams[i][j] == 0) {
                    lose++;
                    is_lose = 1;
                }
                sum += teams[i][j];
            }
        }
        if (is_lose == 0)
            array[0][quantity++] = i + 1;
        if (win > lose)
            result++;
        if (win > (teams_counter / 2))
            array[1][total++] = i + 1;
        array[2][i] = sum;
        array[3][i] = i;
        if (sum > max) {
            max = sum;
            idx = i + 1;
        }
    }
    printf("a) Quantity of teams with more wins than losses: %d;\n", result);
    printf("b) Numbers of teams that have never lost: ");
    for (i = 0; i < quantity; ++i)
        printf("%d ", array[0][i]);
    if (quantity == 0)
        printf("-");
    printf("\n");
    printf("c) Teams that have won more than half of the games: ");
    for (i = 0; i < total; ++i)
        printf("%d ", array[1][i]);
    if (total == 0)
        printf("-");
    printf("\n");
    printf("d) Champion team number: %d;\nscore =", idx);
    for (i = 0; i < teams_counter; ++i)
        printf(" %d", array[2][i]);
    printf(";\ne) Are the teams arranged according to their occupied places in the championship?\n");
    for (i = 0; i < teams_counter - 1 && array[2][i] >= array[2][i + 1]; ++i)
        ;
    if (i == teams_counter - 1)
        printf("Yes;\n");
    else
        printf("No;\n");
    for (k = 0; k < teams_counter - 1; ++k)
        for (i = teams_counter - 1; i > k; --i)
            if (array[2][i] > array[2][i - 1]) {
                exchange_of_values(&array[2][i],&array[2][i - 1]);
                exchange_of_values(&array[3][i],&array[3][i - 1]);
            }
    printf("f&g)\n");
    printf("Place:\tTeam:\tScore\n");
    for (i = 0; i < teams_counter; ++i)
        printf("  %d\t  %d\t  %d\n", i + 1, array[3][i] + 1, array[2][i]);
    printf("\n12.131, magic square;\n");
    int square_size = 5; // square_size != 2;
    int M = (square_size * (square_size * square_size + 1)) / 2;
    max = square_size * square_size; // max value in square
    printf("Square size = %dx%d;\n", square_size, square_size);
    printf("Total value = %d;\n", M);
    //Создадим магический квадрат.
    int square[square_size][square_size];
    for (i = 0; i < square_size; ++i)
        for (j = 0; j < square_size; ++j)
            square[i][j] = -1;
    columns = (square_size / 2) + 1; rows = square_size / 2;
    length_x = columns; length_y = rows;
    counter = 0;
    for (i = 1; i <= max; ++i, length_x = columns, length_y = rows) {
        counter++;
        square[rows][columns] = i;
        if (++columns > square_size - 1)
            columns = 0;
        if (--rows < 0)
            rows = square_size - 1;
        if (square[rows][columns] != -1) {
            rows = length_y;
            columns = length_x;
            if (columns + 2 > square_size - 1)
                columns -= square_size - 2;
            else
                columns += 2;
        }
    }
    for (i = 0; i < square_size; ++i) {
        for (j = 0; j < square_size; ++j)
            printf("%4d ", square[i][j]);
        printf("\n");
    }
    printf("%d;\n", counter);
    // Определим, является ли двухмерный массив магическим квадратом.
    for (i = 0; i < square_size; ++i) {
        sum_1 = 0;
        for (a1 = 0; a1 < square_size; ++a1)
            sum_1 += square[i][a1];
        if (sum_1 != M)
            break;
    }
    for (j = 0; j < square_size; ++j) {
        sum_1 = 0;
        for (a1 = 0; a1 < square_size; ++a1)
            sum_1 += square[a1][j];
        if (sum_1 != M)
            break;
    }
    sum_1 = 0;
    sum_2 = 0;
    for (k = 0; k < square_size; ++k) {
        sum_1 += square[k][k];
        sum_2 += square[k][square_size - k - 1];
    }
    if (i == square_size && j == square_size && sum_1 == M && sum_2 == M)
        printf("Yes, this is magic square, sum = (%d);\n", sum_1);
    else
        printf("No, this is not magic square, %d:%d:%d:%d;\n", i, j, sum_1, sum_2);
    printf("\n12.132 - 12.134, search for identical elements;\n");
    columns = rows = 3;
    rand_max = 10;
    matrix_create_sequence(array, columns, rows, rand_max, mx_cr_rnd);
    matrix_print(array, columns, rows, 0, mx_prn_default);
    counter = 1;
    printf("counter: %d;\n", counter);
    result = matrix_elements_copies(array, columns, rows, counter);
    printf("result = %d;\n", result);
    number = array[0][columns - 1];
    printf("\n12.135, find element in first row: %d\n", number);
    length_x = 0;
    length_y = columns;
    matrix_find_element(array, &length_y, &length_x, number, mx_mod_row | mx_chk_equal);
    printf("equal = %d:%d;\n\n", length_x,length_y);
    number = array[rows - 1][0];
    printf("12.137, find element in first column: %d\n", number);
    length_x = rows;
    length_y = 0;
    matrix_find_element(array, &length_y, &length_x, number, mx_mod_col | mx_chk_equal);
    printf("equal = %d:%d;\n\n", length_x,length_y);
    printf("12.139, find element;\n");
    length_x = rows; length_y = columns;
    number = 5;
    result = matrix_find_element(array, &length_y, &length_x, number, mx_chk_equal);
    if (result != -1)
        printf("a) element equal %d = %d:%d;\n", number, length_x, length_y);
    else
        printf("a) element equal %d missing\n", number);
    length_x = rows;
    length_y = columns;
    number = 5;
    result = matrix_find_element(array, &length_y, &length_x, number, mx_chk_div);
    if (result != -1)
        printf("b) element divided by %d = %d:%d;\n", number, length_x, length_y);
    else
        printf("b) element divided by %d missing;\n", number);
    printf("\n12.141, find sequence in matrix, with functions;\n");
    columns = 2; rows = 2; rand_max = 3;
    matrix_create_sequence(array, columns, rows, rand_max, mx_cr_rnd);
    matrix_print(array, columns, rows, 0, mx_prn_default);
    result = matrix_is_sequence(array, columns, 0, 0, mx_chk_asc | mx_mod_row);
    char* string[] = {"No","Yes"};
    printf("is first row is ascending order: %s;\n", string[result]);
    result = matrix_is_sequence(array, 0, rows, 0, mx_chk_dsc | mx_mod_col);
    printf("is first column is descending order: %s;\n", string[result]);
    columns = rows = 5;
    rand_max = -10;
    printf("\n");
    matrix_create_sequence(array, columns, rows, rand_max, mx_cr_rnd);
    matrix_print(array, columns, rows, 0, mx_prn_default);
    const int tasks_find_all = 10, tasks_find_rc = 4, tasks_find_seq = 8;
    const char* tasks_find_name[] = {"\n12.142\na) first element divided by 7",
                                     "b) last number more than 5",
                                     "\n12.144\na) first positive number",
                                     "b) first number div by 3",
                                     "\n12.146\na) first negative elements in rows",
                                     "b) last even element in row",
                                     "\n12.148\na) find positive elements in rows",
                                     "b) last elements divided by 3 in rows",
                                     "c) elements in ascending order in rows",
                                     "d) find equal elements 5"};
    const int tasks_find_mod[] = {mx_chk_div, 7,
                                  mx_chk_more | mx_mod_last, 5,
                                  mx_chk_more, 0,
                                  mx_chk_div, 3,
                                  mx_chk_less | mx_mod_row, 0, rows,
                                  mx_chk_div | mx_mod_row | mx_mod_last, 2, rows,
                                  mx_chk_more | mx_mod_row, 0, rows,
                                  mx_chk_div | mx_mod_row | mx_mod_last, 3, rows,
                                  mx_chk_asc | mx_mod_row, 0, rows,
                                  mx_chk_equal | mx_mod_row, 5, rows
                                 };
    for (i = 0; i < tasks_find_all; ++i) {
        printf("%s: ", tasks_find_name[i]);
        length_x = rows; length_y = columns;
        if (i < tasks_find_rc) {
            result = matrix_find_element(array, &length_y, &length_x,
                                         tasks_find_mod[i * 2 + 1], tasks_find_mod[i * 2]);
            printf("%d:%d;\n", length_x, length_y);
        }
        if (i >= tasks_find_rc) {
            int rs = tasks_find_rc * 2 + (i - tasks_find_rc) * 3;
            for (j = 0; j < tasks_find_mod[rs + 2]; ++j) {
                length_x = rows; length_y = columns;
                if (tasks_find_mod[rs] & mx_mod_row)
                    length_x = j;
                if (tasks_find_mod[rs] & mx_mod_col)
                    length_y = j;
                if (i != tasks_find_seq) {
                    result = matrix_find_element(array, &length_y, &length_x,
                                                 tasks_find_mod[rs + 1], tasks_find_mod[rs]);
                    if (result)
                        printf("%d[%d] ", array[length_x][length_y], length_x);
                } else {
                    result = matrix_is_sequence(array, length_y, length_x,
                                                tasks_find_mod[rs + 1], tasks_find_mod[rs]);
                    printf("%s[%d] ", string[result], length_x);
                }
            }
            printf("\n");
        }
    }
    columns = rows = 2;
    rand_max = -10;
    printf("\n");
    matrix_create_sequence(array, columns, rows, rand_max, mx_cr_rnd);
    matrix_print(array, columns, rows, 0, mx_prn_default);
    printf("\n12.151, find first column where all elements:\n");
    char* tasks_1[] = {"odd:",
                       "less than 5:",
                       "more than 5:",
                       "div 3:"};
    for (j = 0; j < 4; ++j) {
        printf("%s ", tasks_1[j]);
        for (i = 0; i < columns; ++i) {
            length_x = rows;
            length_y = i;
            switch (j) {
            case 0:
                result = matrix_find_element(array, &length_y, &length_x, 2, mx_chk_div | mx_mod_col);
                break;
            case 1:
                result = matrix_find_element(array, &length_y, &length_x, 5, mx_chk_less | mx_mod_col);
                break;
            case 2:
                result = matrix_find_element(array, &length_y, &length_x, 5, mx_chk_more | mx_mod_col);
                break;
            case 3:
                result = matrix_find_element(array, &length_y, &length_x, 3, mx_chk_not_div | mx_mod_col);
                break;
            }
            if (!result)
                printf("%d ", i);
        }
        if (i == columns)
            printf("-");
        printf("\n");
    }
    return;
    printf("\n12.153, find column where:\n");
    char* tasks_2[] = {"all elements equal 0:",
                       "all elements more than 0 and less than 5:",
                       "all elements even:",
                       "elements quantity negative equal positive:",
                       "there are equal elements:",
                       "half of the values is the minimum:"};
    int negative = 0, positive = 0, flag = 0;
    length_x = rows;
    length_y = columns;
    min = matrix_info(array,&length_y,&length_x,mx_info_min);
    for (i = 0; i < 6; ++i) {
        printf("%s ", tasks_2[i]);
        for (j = 0; j < columns; ++j, negative = 0, positive = 0, flag = 0, counter = 0)
            for (k = 0; k < rows; ++k) {
                if (i == 0) {
                    if (array[k][j] != 0)
                        break;
                    if (k == rows - 1)
                        printf("%d ", j);
                } else if (i == 1) {
                    if (array[k][j] < 0 || array[k][j] > 5)
                        break;
                    if (k == rows - 1)
                        printf("%d ", j);
                } else if (i == 2) {
                    if (array[k][j] % 2 != 0)
                        break;
                    if (k == rows - 1)
                        printf("%d ", j);
                } else if (i == 3) {
                    if (array[k][j] < 0)
                        ++negative;
                    if (array[k][j] > 0)
                        ++positive;
                    if (k == rows - 1 && negative == positive)
                        printf("%d ", j);
                } else if (i == 4) {
                    int g = 0;
                    for (g = 0; g < rows; ++g)
                        if (g != k && array[g][j] == array[k][j])
                            break;
                    if (g != rows && flag == 0) {
                        flag = 1;
                        printf("%d ", j);
                    }
                } else {
                    if (array[k][j] == array[length_x][length_y])
                        ++counter;
                    if (k == rows - 1 && counter == (rows / 2))
                        printf("%d ", j);
                }
            }
        printf("\n");
    }
    return;
}
