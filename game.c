#include "global.h"
#include "library.h"

int uniq_gen_fast_alt_1(int number[], int start, int limit)
{
    const int num_max = limit;
    if (limit < 1)
        return -1;
    for (int i = 0; i < limit; ++i)
        number[i] = start + i;
    int tmp = 0, idx_1 = 0 , idx_2 = 0;
    for (int i = 0; i < limit * limit; ++i) {
        idx_1 = rand() % num_max;
        idx_2 = rand() % num_max;
        tmp = number[idx_1];
        number[idx_1] = number[idx_2];
        number[idx_2] = tmp;
    }
    return 0;
}

int uniq_gen_fast_alt(int number[], int length, int limit)
{
    const int num_max = limit;
    if (length < 1 || length > num_max)
        return -1;
    for (int i = 0; i < limit; ++i)
        number[i] = i;
    int tmp = 0, idx_1 = 0 , idx_2 = 0;
    for (int i = 0; i < length * length; ++i) {
        idx_1 = rand() % num_max;
        idx_2 = rand() % num_max;
        tmp = number[idx_1];
        number[idx_1] = number[idx_2];
        number[idx_2] = tmp;
    }
    return 0;
}

int uniq_gen_fast(int number[], int length, int limit)
{
    const int num_max = limit;
    if (length < 1 || length > num_max)
        return -1;
    int digits[limit];
    for (int i = 0; i < limit; ++i)
        digits[i] = i;
    int tmp = 0, idx_1 = 0 , idx_2 = 0;
    for (int i = 0; i < length * length * length && digits[0] == 0; ++i) {
        idx_1 = rand() % num_max;
        idx_2 = rand() % num_max;
        tmp = digits[idx_1];
        digits[idx_1] = digits[idx_2];
        digits[idx_2] = tmp;
    }
    // Подставить частный случай нуля.
    for (int i = 0; i < length; ++i)
        number[i] = digits[i];
    return 0;
}

int uniq_gen_fast_symbols(char string[], int length)
{
    const int symbol_max = 26;
    if (length < 1 || length > symbol_max)
        return -1;
    char symbols[symbol_max];
    for (int j = 0; j < 26; ++j)
        symbols[j] = 'A' + j;
    char tmp;
    int idx_1 = 0 , idx_2 = 0, i = 0;
    for (i = 0; i < length * length * length; ++i) {
        idx_1 = rand() % symbol_max;
        idx_2 = rand() % symbol_max;
        tmp = symbols[idx_1];
        symbols[idx_1] = symbols[idx_2];
        symbols[idx_2] = tmp;
    }
    for (i = 0; i < length; ++i)
        string[i] = symbols[i];
    string[length] = '\0';
    return 0;
}

int string_rand_change(char string[], int level_change) {
    int length = string_length(string);
    if (length == 0 || level_change < 1)
        return -1;
    int mass_idx[level_change];
    char mass_symbol[level_change];
    uniq_gen_fast(mass_idx, level_change, length);
    uniq_gen_fast_symbols(mass_symbol, level_change);
    for (int i = 0; i < level_change; ++i)
        string[mass_idx[i]] = mass_symbol[i];
    return 0;
}

void bulls_and_cows()
{
    int i = 0, j = 0, k = 0, counter = 0, quantity = 0, positions = 0;
    const int number_length = 4;
    int number[number_length], entered_number[number_length], is_equal = 0;
    srand(time(NULL));
    uniq_gen_fast(number,number_length,9);
    printf("Hack the terminal, guess the number size %d, with using digits.\n",number_length);
    printf("Number with all unique digits and not statring with zero!\n");
    //printf("Debug number: ");
    //for (i = 0; i < number_length; ++i) {
    //   printf("%d", number[i]);
    //}
    printf("\n");
    printf("Guess:\tCorrect:\tPositions:\n");
    while (is_equal == 0) {
        scanf("%d",&k);
        if (length_number(k) == number_length) {
            for (i = number_length - 1; i >= 0 && k != 0; --i) {    // Можно написать доп. функцию.
                entered_number[i] = k % 10;
                k /= 10;
            }
            for (j = 0, counter = 0, positions = 0; j < number_length; ++j) {
                for (k = 0; k < number_length; ++k) {
                    if (number[k] == entered_number[j]) {
                        counter++;
                        if (j == k)
                            positions++;
                    }
                }
            }
            if (positions == number_length)
                is_equal = 1;
            quantity++;
            printf("%d\t%d\t\t%d\n", quantity, counter, positions);
        } else
            printf("You entered a number with the wrong length!;\n");
    }
    printf("Hooray, you won!\nNumber of attempts = %d;\n\n",quantity);
}

void hack_the_terminal(int length, int quantity, int attempts)
{
    if (length < 1 || quantity < 2 || length > 26) {
        printf("error in parameters;\n\n");
        return;
    }
    srand(time(NULL));
    int likeness_idx[OBJECTS_MAX];
    int likeness = 0, div = 0, rem = 0;
    printf("length = %d, quantity = %d;\n", length, quantity);
    if (quantity > length) {
        rem = (quantity - 1) % length;
        div = (quantity - 1) / length;
    } else {
        rem = (quantity - 1) % length;
        div = length % (quantity - 1); // Поменять на другую переменную.
    }
    printf("div = %d;\nrem = %d;\n", div, rem);
    likeness_idx[quantity - 1] = length;
    for (int i = 0; i < quantity - 1;) {
        if (quantity > length)
            for (int j = 0; j < div; ++j)
                likeness_idx[i++] = likeness;
        if (rem > 0) {                              // Заполняем массив, если пароль длиннее чем кол-во вариантов...
            likeness_idx[i++] = likeness;
            rem--;
        }
        if (quantity > length)
            likeness++;
        else {
            likeness += length / (quantity - 1);
            if (div > 0) {
                likeness++;
                div--;
            }
        }
    }
    printf("Variants likeness: \n");
    for (int i = 0; i < quantity; ++i)
        printf("%d ", likeness_idx[i]);
    return;
}

int stalker_evaluation_function(int properties[])
{
    const int properties_quantity = 14;
    double properties_point[14] = {16,32,120,4.7,8,80.1,50,32,50,32,32,32,28,0.01};
    if (properties[0] < 0)
        return INT_MIN;
    double points = 0;
    for (int i = 0; i < properties_quantity; ++i)
        points += properties[i] * properties_point[i];
    return (int)(points);
}

int checking_nearby_paths(int size, int place[size][size], int x, int y)
{
    int sum = 0;
    if (x < size - 1 && place[x + 1][y] == '*')
        ++sum;
    if (y < size - 1 && place[x][y + 1] == '*')
        ++sum;
    if (x > 0 && place[x - 1][y] == '*')
        ++sum;
    if (y > 0 && place[x][y - 1] == '*')
        ++sum;
    if (sum > 1)
        return 0;
    else
        return 1;
}

void labyrinth_direction_create(int size, int place[size][size], int *x, int *y, int *branches_counter, char empty)
{
    int way = 0, flag = 0, result = 0;
    int directions[][2] = { {-1, 0}, {0, +1}, {+1, 0}, {0, -1}};
    while (flag == 0) {
        way = rand() % 4;
        int tmp_x = *x + directions[way][0], tmp_y = *y + directions[way][1];
        if (tmp_x >= 0 && tmp_x < size && tmp_y >= 0 && tmp_y < size &&
                place[tmp_x][tmp_y] == empty) {
            result = checking_nearby_paths(size, place, tmp_x, tmp_y);
            if (result) {
                flag = 1;
                *x = tmp_x;
                *y = tmp_y;
            }
        }
    }
    place[*x][*y] = '*';
    ++branches_counter;
    if (!(rand() % 4)) {
         labyrinth_direction_create(size, place, x, y, branches_counter, empty);
        ++branches_counter;
    }
}

void labyrinth_basic_create(int size, int place[size][size], int branches, char empty)
{
    int x = 0, y = 0, branches_counter = 0;
    while (branches_counter < branches && x < size && y < size) {
        labyrinth_direction_create(size, place, &x, &y, &branches_counter, empty);
    }
    ++branches_counter;
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y)
            printf("%c", place[x][y]);
        printf("\n");
    }
    return;
}

void labyrinth(int size, int branches)
{
    srand(time(NULL));
    int place[size][size];
    char empty = ' ';
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            place[i][j] = empty;
    place[0][0] = '*';
    labyrinth_basic_create(size, place, branches, empty);
}

void stalker_best_combination_of_artifacts()
{
    const int artifacts_quantity = 15;
    const int properties_quantity = 14;
    const char* artifacts[15] = {"Пружина","Вспышка","Глаз Ворона","Душа","Выверт","Слизь","Слизняк","Кровь камня",
                                 "Каменный цветок","Дикобраз","Капля","Морской ёж","Колючка","Ломоть мяса","Медуза"};
    const int artifacts_properties[15][14] =
    {{0,0,0,0,0,0,0,0,10,0,0,0,0,0},{0,-10,0,0,0,6,0,0,0,-10,0,0,0,0},{-10,0,-7,0,0,0,0,0,0,15,20,10,-10,0},
     {10,10,0,0,60,0,-7,0,-7,0,0,0,0,0},{-3,0,0,0,0,0,2,0,2,0,0,0,0,0},{0,0,0,67,0,0,0,0,0,0,-20,-10,0,0},
     {0,0,0,133,0,0,0,0,0,0,-10,-10,0,0},{3,3,0,0,20,0,-3,0,-3,0,0,0,0,0},{-5,0,4,0,0,0,0,0,0,0,0,0,0,0},
     {40,0,0,0,0,-2,0,0,0,0,0,0,0,0},{5,0,0,0,0,-7,0,0,0,0,0,0,0,0},{20,0,0,-100,0,0,0,0,0,0,0,0,0,0},
     {5,0,0,-100,0,0,0,0,0,0,0,0,0,0},{5,5,0,0,40,0,-5,0,-5,0,0,0,0,0},{0,-3,2,0,0,0,0,0,0,0,0,0,0,0}};
    int artifacts_counter[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int properties[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char* properties_name[14] = {"Вывод радиации","Радиация","Пулестойкость","Кровотечение","Здоровье","Выносливость",
                                 "Разрыв", "Взрыв","Удар","Электрошок","Ожог","Химический ожог","Телепатия","Сытость"};
    int i = 0, j = 0, k = 0, tmp = 0, properties_max;
    int a_c[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int a_p[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for (i = 0; i < artifacts_quantity; ++i) {
        printf("%s: ", artifacts[i]);
        scanf("%d",&artifacts_counter[i]);
        printf("\n");
    }
    // 0 0 0 - no artifacts.
    // 1 0 1 - raven and spring.

    for (i = 0; i < artifacts_quantity; ++i)
        for (j = 0; j < artifacts_counter[i]; ++j)
            for (k = 0; k < properties_quantity; ++k)
                properties[k] += artifacts_properties[i][k];
    for (int i = 0; i < 14; ++i)
        printf("%d ",properties[i]);
    properties_max = stalker_evaluation_function(properties);
    printf("%d ",properties_max);
    for (a_c[0] = 0; a_c[0] <= artifacts_counter[0]; ++a_c[0])      //представить наличие или отсутствие артефакта в двочном виде.
        for (a_c[1] = 0; a_c[1] <= artifacts_counter[1]; ++a_c[1])
            for (a_c[2] = 0; a_c[2] <= artifacts_counter[2]; ++a_c[2])
                for (a_c[3] = 0; a_c[3] <= artifacts_counter[3]; ++a_c[3])
                    for (a_c[4] = 0; a_c[4] <= artifacts_counter[4]; ++a_c[4])
                        for (a_c[5] = 0; a_c[5] <= artifacts_counter[5]; ++a_c[5])
                            for (a_c[6] = 0; a_c[6] <= artifacts_counter[6]; ++a_c[6])
                                for (a_c[7] = 0; a_c[7] <= artifacts_counter[7]; ++a_c[7])
                                    for (a_c[8] = 0; a_c[8] <= artifacts_counter[8]; ++a_c[8])
                                        for (a_c[9] = 0; a_c[9] <= artifacts_counter[9]; ++a_c[9])
                                            for (a_c[10] = 0; a_c[10] <= artifacts_counter[10]; ++a_c[10])
                                                for (a_c[11] = 0; a_c[11] <= artifacts_counter[11]; ++a_c[11])
                                                    for (a_c[12] = 0; a_c[12] <= artifacts_counter[12]; ++a_c[12])
                                                        for (a_c[13] = 0; a_c[13] <= artifacts_counter[13]; ++a_c[13])
                                                            for (a_c[14] = 0; a_c[14] <= artifacts_counter[14]; ++a_c[14]) {
                                                                for (i = 0; i < artifacts_quantity; ++i)
                                                                    for (j = 0; j < a_c[i]; ++j)
                                                                        for (k = 0; k < properties_quantity; ++k)
                                                                            a_p[k] += artifacts_properties[i][k];
                                                                tmp = stalker_evaluation_function(a_p);
                                                                if (tmp > properties_max) {
                                                                    properties_max = tmp;
                                                                    printf("\n");
                                                                    for (int i = 0; i < 15; ++i)
                                                                        printf("%d ",a_c[i]);
                                                                    printf(" | %d",tmp);
                                                                    printf("\n");
                                                                    for (int i = 0; i < 14; ++i)
                                                                        printf("%d ",a_p[i]);
                                                                }
                                                                for (i = 0; i < 14; ++i)
                                                                    a_p[i] = 0;
                                                            }

}

