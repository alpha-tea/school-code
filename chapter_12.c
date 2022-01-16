#include "global.h"
#include "library.h"

static const int matrix_act_mask = 0x1F;            // Константная маска до модификатора. Изменить, если поменяется назначение бит.
static const int matrix_check_mask = 0xF000;       // Маска для модификатора проверки массиива или элемента.

enum matrix_type { mx_nop, mx_init_par, mx_init_input, mx_init_all, mx_init_column, mx_init_row,
                   mx_cr_val, mx_cr_rnd, mx_cr_ariphmetic, mx_cr_geometry,
                   mx_roll_left, mx_roll_right, mx_roll_up, mx_roll_down,
                   mx_info_status, mx_info_sum, mx_info_multiply, mx_info_avr, mx_info_idxs,
                   mx_prn_default = 0x20, mx_prn_row = 0x40, mx_prn_column = 0x80, mx_prn_flipv = 0x100, mx_prn_fliph = 0x200,
                   mx_chk_equal = 0x1000, mx_chk_more = 0x2000, mx_chk_less = 0x4000, mx_chk_div = 0x8000,
                   mx_mod_col = 0x10000, mx_mod_row = 0x20000, mx_mod_sq = 0x40000, mx_mod_pair = 0x80000,
                   mx_end = 0xF0000
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
    if (type < mx_prn_default || type > mx_prn_fliph || columns > OBJECTS_MAX || rows > OBJECTS_MAX)
        return -1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            //for (int mask = 0x20; mask != mx_prn_end; mask <<= 1)
            switch (type) {  //type & mask
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
            default:
                printf("error");
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


int matrix_info(int data[OBJECTS_MAX][OBJECTS_MAX], int columns, int rows, enum matrix_type type)
{
    if (columns < 0 || rows < 0 || columns > OBJECTS_MAX || rows > OBJECTS_MAX ||
            type < mx_info_status || type >= mx_end) {
        printf("error: columns = %d, rows = %d, type = %d;\n", columns, rows, type);
        return -1;
    }
    int result = 0, counter = 0, square = 0, start_row = 0, start_column = 0, element = 0;
    result = ((type & matrix_act_mask) == mx_info_multiply) ? 1 : 0;
    square = (type & mx_mod_sq) ? 1 : 0;
    start_column = (type & mx_mod_col) ? columns++ : 0;
    start_row = (type & mx_mod_row) ? rows++ : 0;
    //printf("square = %d, start column = %d, start row = %d;\n", square, start_column, start_row);
    for (int i = start_row; i < rows; ++i)
        for (int j = start_column; j < columns; ++j) {
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
            default:
                printf("incorrect type of action %d;\n", type & matrix_act_mask);
                return -1;
            }
        }
    /*
    if (ret & mx_prn_default) {
        matrix_print(data,rows,columns,0,mx_prn_default);
        printf("\n");
        printf("sum = %d;\n", data_inf[0]);
        printf("sum of column(%d) = %d;\n", columns, data_inf[1]);
        printf("sum of row(%d) = %d;\n", rows, data_inf[2]);
        printf("average = %d;\n", data_inf[3]);
        printf("average sqrt = %d;\n", data_inf[4]);
    }
    */
    if (counter)
        result /= counter;
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
    int result = 0, counter = 0, square = 0, start_row = 0, start_column = 0,
            element = 0, check_type = 0, par = *par_cnt; *par_cnt = 0;
    result = ((check & matrix_act_mask) == mx_info_multiply) ? 1 : 0;
    square = (check & mx_mod_sq) ? 1 : 0;
    start_column = (check & mx_mod_col) ? columns++ : 0;
    start_row = (check & mx_mod_row) ? rows++ : 0;
    for (int i = mx_chk_equal; i <= mx_chk_div; i <<= 1)
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
    int result = matrix_info(array,columns, a1, mx_info_sum | mx_mod_row);
    printf("a) sum = %d;\n",result);
    result = matrix_info(array, a2, rows, mx_info_sum | mx_mod_col);
    printf("b) sum = %d;\n",result);
    printf("\n12.38, 12.41, source matrix:\n");
    number = 3; columns = 5; rows = 5;
    int rand_max = 10;
    matrix_create_sequence(array,columns,rows,rand_max,mx_cr_rnd);
    matrix_print(array,columns,rows,0,mx_prn_default);
    result = matrix_info(array, number, rows, mx_info_sum | mx_mod_col);
    printf("sum of scores spotrsmans = %d, column = %d;\n",result, number);
    result = matrix_info(array, columns, number, mx_info_sum | mx_mod_row);
    printf("sum of salary = %d, row = %d;\n", result, number);
    printf("\n12.44;\n");
    number = 3; columns = 5; rows = 5;
    matrix_print(array,columns,rows,0,mx_prn_default);
    result = matrix_info(array, number, rows, mx_info_sum | mx_mod_col);
    printf("students counter = %d, column = %d;\n",result, number);
    printf("\n12.47, multiply of %d row;\n", a1);
    result = matrix_info(array, columns, a1, mx_info_multiply | mx_mod_row);
    printf("multiply = %d;\n",result);
    printf("\n12.48;\n");
    matrix_print(array,columns,rows,0,mx_prn_default);
    a1 = 2; a2 = 3;
    result = matrix_info(array, columns, a1, mx_info_sum | mx_mod_sq | mx_mod_row);
    printf("a) sum of square(row = %d) = %d;\n",a1,result);
    result = matrix_info(array, a2, rows, mx_info_sum | mx_mod_sq | mx_mod_col);
    printf("b) sum of square(column = %d) = %d;\n\n",a2,result);
    printf("12.50, 12.55;\n");
    matrix_print(array,columns,rows,0,mx_prn_default);
    a1 = 2; a2 = 3;
    result = matrix_info(array, columns, a1, mx_info_avr | mx_mod_row);
    printf("a) average(row = %d) = %d;\n",a1,result);
    result = matrix_info(array, a2, rows, mx_info_avr | mx_mod_col);
    printf("b) average(column = %d) = %d;\n\n",a2,result);
    printf("12.56;\n");
    matrix_print(array,columns,rows,0,mx_prn_default);
    result = matrix_info(array, columns, rows, mx_info_sum);
    printf("a) sum of all elements = %d;\n",result);
    result = matrix_info(array, columns, rows, mx_info_sum | mx_mod_sq);
    printf("b) sum of square all elements = %d;\n",result);
    result = matrix_info(array, columns, rows, mx_info_avr);
    printf("c) average of all elements = %d;\n\n",result);
    printf("12.59;\n");
    a1 = 0;
    matrix_print(array, columns, rows, 0, mx_prn_default);
    result = matrix_check_info(array, columns, rows, &a1 ,mx_chk_equal | mx_info_sum);
    printf("equal 0 = %d;\n\n",a1);
    printf("12.61;\n");
    matrix_print(array, columns, rows, 0, mx_prn_default);
    double average_rating = 0;
    result = matrix_info(array, columns, rows, mx_info_sum);
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
        result = matrix_info(array, columns, rows, mx_info_sum);
        average_rating = (double)result / (double)(columns * rows);
        printf("average = %.2f;\n\n", average_rating);
        if (average_rating > max_d) {
            max_d = average_rating;
            idx = k;
        }
    }
    printf("max ratinf of groups #%d = %.2f;\n", idx, max_d);
    printf("12.67, 12.69;\nsource matrix:\n");
    columns = 5; rows = 5;
    matrix_create_sequence(array,columns,rows,-rand_max,mx_cr_rnd);
    matrix_print(array, columns, rows, 0, mx_prn_default);
    char* tasks[] = {"a) sum negative elements of 4-th row:",
                    "b) sum elements less than 5 of 3-rd column:",
                    "c) counter of elements of 3-rd row less than -3:",
                    "d) counter of elements of 1-st column more than -5:",
                    "a) average of odd elements of 2-nd row:",
                    "b) average of 3-th column, divided by 4:"};
    enum matrix_type tasks_type[] = {mx_info_sum | mx_chk_less | mx_mod_row,
                                    mx_info_sum | mx_chk_less | mx_mod_col
                                    };
    int tasks_par[] = {columns, 4, 0, // параметры задачи: столбц(ы), строк(и), параметр проверки
                      3, rows, 5};
    for (i = 0; i < 2; ++i) {
        result = matrix_check_info(array, tasks_par[i * 3], tasks_par[i * 3 + 1], &tasks_par[i * 3 + 2],
                tasks_type[i]);
        printf("#%d, %s %d;\n", i, tasks[i], result); // доделать...
    }
}
