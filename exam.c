#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Задание 8:
 Все 4-буквенные слова, составленные из букв П, Р, В, Д, А,
 записаны в алфавитном порядке и пронумерованы. Вот начало списка:
 1. АААА
 2. АААВ
 3. АААД
 4. АААП
 5. АААР
 6. ААВА
 ...
 Найдите номер первого слова в этом списке, которое не содержит гласных и одинаковых букв.

    Задание 17:
 В файле 17-204.txt содержится последовательность целых чисел,
 которые принимают значения от -10000 до 10000 включительно.
 Тройка идущих подряд чисел последовательности называется уникальной,
 если только второе из них является положительным числом, заканчивающимся на 9.
 Определите количество уникальных троек чисел, а затем – максимальную из всех сумм таких троек.

    Задание 24:
 Текстовый файл 24.txt содержит строку из заглавных букв A, B, C, D, E, F,
 всего не более чем из 106 символов.
 Определите, сколько встречается комбинаций вида CB*BC,
 где на месте "*" может стоять любая буква, кроме A, B и F.
 В ответе укажите сначала букву, которая чаще всего встречается на месте "*",
 затем общее количество подходящих комбинаций.

    Задание 25:
 Среди чисел, больших 520000, найти такие, сумма всех делителей которых,
 не считая единицы и самого числа, образует число-палиндром
 (например, число 1221: если его «перевернуть», получается то же самое число).
 Вывести первые пять чисел, удовлетворяющих вышеописанному условию,
 справа от каждого числа вывести его максимальный делитель.

    Задание 26:
 Организация купила для своих сотрудников
 все места в нескольких подряд идущих рядах на концертной площадке.
 Известно, какие места уже распределены между сотрудниками.
 Найдите ряд с наибольшим номером, в котором есть два соседних места,
 таких что слева и справа от них в том же ряду места уже распределены (заняты).
 Гарантируется, что есть хотя бы один ряд, удовлетворяющий условию.
 Входные данные представлены в файле 26-59.txt следующим образом.
 В первой строке входного файла находится одно число:
 N – количество занятых мест (натуральное число, не превышающее 10 000).
 В следующих N строках находятся пары чисел: ряд и место выкупленного билета, не превышающие 100000.
 В ответе запишите два целых числа:
 номер ряда и наименьший номер места из найденных в этом ряду подходящих пар.
 */

void exam_8()
{
    /*
    Задание 8:
 Все 4-буквенные слова, составленные из букв П, Р, В, Д, А,
 записаны в алфавитном порядке и пронумерованы. Вот начало списка:
 1. АААА
 2. АААВ
 3. АААД
 4. АААП
 5. АААР
 6. ААВА
 ...
 Найдите номер первого слова в этом списке, которое не содержит гласных и одинаковых букв.
 АВДПР = от 0 до 4
     */
    printf("Test 8. Variant 1:\n");
    const int word_size = 4, values = 5;
    int word[word_size], is_vowels = 1, is_copies = 1, is_limit = 0, i = 0, j = 0, counter = 0;
    for (i = 0; i < word_size; ++i)
        word[i] = 0;
    while (!is_limit && (is_vowels || is_copies)) {
        for(i = 0, is_vowels = 1; i < word_size && word[i] != 0; ++i)
            ;
        if (i == word_size)
            is_vowels = 0;
        for (i = 0, is_copies = 0; i < word_size - 1 && !is_copies; ++i)
            for (j = i + 1; j < word_size && !is_copies; ++j)
                if (word[i] == word[j])
                    is_copies = 1;
        printf("word: ");
        for (i = 0; i < word_size; ++i)
            printf("%d", word[i]);
        printf(", is vowels = %d, is copies = %d;\n", is_vowels, is_copies);
        i = word_size - 1;
        while (i >= 0 && ++word[i] == values)
            word[i--] = 0;
        /*
        for (i = word_size - 1, is_inc = 0; i >= 0 && !is_inc; --i) {
            word[i]++;
            if (word[i] == values)
                word[i] = 0;
            else
                is_inc = 1;
        }
        */
        if (i == -1)
            is_limit = 1;
        //is_vowels = 1;
        ++counter;
    }
    printf("counter = %d;\n\n", counter);
}

#define BUFF_SIZE 1024

void exam_17()
{
    /*
6303
-224
1131
-4167
4126
-5061
1729
-3487
-4434
1112
    Задание 17:
 В файле 17-204.txt содержится последовательность целых чисел,
 которые принимают значения от -10000 до 10000 включительно.
 Тройка идущих подряд чисел последовательности называется уникальной,
 если только второе из них является положительным числом, заканчивающимся на 9.
 Определите количество уникальных троек чисел, а затем – максимальную из всех сумм таких троек.
     */
    printf("Test 17. Variant 1:\n");
    FILE*  file = fopen("17_2.txt", "r");
    if (file == NULL) {
        printf("error: file '17_1' not found;\n");
        return;
    }
    char line[BUFF_SIZE];
    const int seq_size = 3;
    int seq_data[seq_size], sequences = 0, counter = 1, max = -20000, sum = 0, max_pos = -1, i = 0;
    for (i = 0; i < seq_size; ++i)
        seq_data[i] = 11111;
    while ((fgets(line,BUFF_SIZE,file)) != NULL) {
        seq_data[seq_size - 1] = atoi(line);
        printf("\nsource string '%s' and integer = %d, counter = %d;\n",
               line, seq_data[seq_size - 1], counter);
        for (i = 0; i < seq_size && seq_data[i] != 11111; ++i)
            ;
        if (i == seq_size) {
            if (seq_data[0] < 0 && (seq_data[1] > 0 && seq_data[1] % 10 == 9) && seq_data[2] < 0) {
                sequences++;
                sum = 0;
                for (i = 0; i < seq_size; ++i)
                    sum += seq_data[i];
                if (sum > max) {
                    max = sum;
                    max_pos = counter;
                }
            }
        }
        printf("data sequence before shift: ");
        for (i = 0; i < seq_size; ++i)
            printf("%d ", seq_data[i]);
        for (i = 0; i < seq_size - 1; ++i)
            seq_data[i] = seq_data[i + 1];
        ++counter;
    }
    printf("\nMaximum sum sequence is %d at position %d, total = %d;\n", max, max_pos, sequences);
    if (fclose(file))
        printf("error: can't close file");
}

void exam_24()
{
    //ABCDEF_CBABC_CBBBC_____CBCBC_____BCDBC_____CBEBC_CBEBC_CBFBC_CBFBC_B_CBDBC
    /*
    Задание 24:
 Текстовый файл 24.txt содержит строку из заглавных букв A, B, C, D, E, F,
 всего не более чем из 106 символов.
 Определите, сколько встречается комбинаций вида CB*BC,
 где на месте "*" может стоять любая буква, кроме A, B и F.
 В ответе укажите сначала букву, которая чаще всего встречается на месте "*",
 затем общее количество подходящих комбинаций.
*/
    printf("Test 24. Variant 1:\n");
    FILE*  file = fopen("24_1.txt", "r");
    if (file == NULL) {
        printf("error: file '17_1' not found;\n");
        return;
    }
    const int seq_size = 5, freq_size = 6;
    int seq_data[BUFF_SIZE], seq_freq[BUFF_SIZE], sequences = 0, counter = 1, max = -1, max_pos = -1;
    int i = 0, c = 0;
    for (i = 0; i < BUFF_SIZE; ++i) {
        seq_data[i] = 0;
        seq_freq[i] = 0;
    }
    while ((c = getc(file)) != EOF) {
        seq_data[seq_size - 1] = c;
        printf("\n%d) source sequence: ", counter);
        for (i = 0; i < seq_size; ++i)
            printf("%c", seq_data[i]);
        if (counter >= seq_size) {
            if (seq_data[0] == 'C' && seq_data[1] == 'B' && seq_data[3] == 'B' && seq_data[4] == 'C'
                    && seq_data[2] != 'A' && seq_data[2] != 'B' && seq_data[2] != 'F') {
                sequences++;
                int freq_idx = seq_data[2] - 'A';// Или любое другое правило
                printf(", check OK, idx = %d, data = %d, c = '%c';", freq_idx, seq_data[2], seq_data[2]);
                seq_freq[freq_idx]++;
            }
        }
        for (i = 0; i < seq_size - 1; ++i)
            seq_data[i] = seq_data[i + 1];
        ++counter;
    }
    printf("\nfreqency: ");
    for (i = 0; i < freq_size; ++i) {
        printf("%d ", seq_freq[i]);
        if (seq_freq[i] > max) {
            max = seq_freq[i];
            max_pos = i;
        }
    }
    printf("\nmax sequence = %d, c = '%c' and counter = %d, sequences = %d;\n",
           max, 'A' + max_pos, counter, sequences);
    if (fclose(file))
        printf("error: can't close file");
}

void exam_25()
{
    /*
     Задание 25.
 Среди чисел, больших 520000, найти такие, сумма всех делителей которых,
 не считая единицы и самого числа, образует число-палиндром
 (например, число 1221: если его «перевернуть», получается то же самое число).
 Вывести первые пять чисел, удовлетворяющих вышеописанному условию,
 справа от каждого числа вывести его максимальный делитель.
     */
    printf("Test 25. Variant 1:\n");
    int i = 0, n = 0, counter = 0, sum = 0, max = 0;
    for (n = 1000; counter < 5; ++n) {
        printf("n = %d, dividers: ", n);
        for (i = 2, sum = 0; i < n - 1; ++i) {
            if (n % i == 0) {
                max = i;
                sum += i;
                printf("%d ", i);
            }
        }
        printf("  sum = %d;\n", sum);
        if (sum != 0) {
            /*
            int order = 0, tmp = sum;
            while (tmp > 0) {
                ++order;
                tmp /= 10;
            }
            int array[order], length = 0;
            tmp = sum;
            while (tmp > 0) {
                array[length++] = tmp % 10;
                tmp /= 10;
            }
            for (i = 0; i < (order / 2) && array[i] == array[order - i - 1]; ++i)
                ;
            if (i == (order / 2)) {
                printf("Yes, sum is palindrome, max div = %d\n", max);
                ++counter;
            } else
                printf("No, sum is just a number;\n");
                */
            int order = 1, tmp = sum;
            while (tmp) {
                order *= 10;
                tmp /= 10;
            }
            order /= 10;
            printf("order = %d; ", order);
            tmp = sum;
            int dl = 0, dr = 0;
            while (sum && dl == dr) {
                dl = tmp / order % 10;
                dr = sum % 10;
                sum /= 10;
                order /= 10;
            }
            if (dl == dr) {
                printf("Yes, sum is palindrome, max div = %d\n", max);
                ++counter;
            } else
                printf("No, sum is just a number;\n");

        }
    }
}

#define ROWS_MAX 100000

void exam_26()
{
    /*
    Задание 26:
 Организация купила для своих сотрудников
 все места в нескольких подряд идущих рядах на концертной площадке.
 Известно, какие места уже распределены между сотрудниками.
 Найдите ряд с наибольшим номером, в котором есть два соседних места,
 таких что слева и справа от них в том же ряду места уже распределены (заняты).
 Гарантируется, что есть хотя бы один ряд, удовлетворяющий условию.
 Входные данные представлены в файле 26-59.txt следующим образом.
 В первой строке входного файла находится одно число:
 N – количество занятых мест (натуральное число, не превышающее 10 000).
 В следующих N строках находятся пары чисел: ряд и место выкупленного билета, не превышающие 100000.
 В ответе запишите два целых числа:
 номер ряда и наименьший номер места из найденных в этом ряду подходящих пар.
 10
 5 5
 5 9
 5 6    7 - 8 свободны
 16 9
 16 3   4 - 5 и 7 - 8 свободны
 16 6
 20 23
 20 28
 20 35
 20 40

     */
    printf("Test 26. Variant 1:\n");
    FILE*  file = fopen("26_1.txt", "r");
    if (file == NULL) {
        printf("error: file '26_1' not found;\n");
        return;
    }
    char s[BUFF_SIZE];
    int seats_data[BUFF_SIZE], rows_data[ROWS_MAX], total = 0, counter = 0,
            min = ROWS_MAX, min_row = -1, file_seats = 0, file_act = 0;
    if ((fgets(s, BUFF_SIZE, file)) == NULL) {
        printf("total seats error;\n");
        return;
    }
    total = atoi(s);
    file_seats = ftell(file);
    printf("total seats = %d, seats data position = %d\n", total, file_seats);
    while ((fgets(s, BUFF_SIZE, file)) != NULL) {
        file_act = ftell(file);
        s[strlen(s) - 1] = '\0';    // Необязательно
        printf("\nsource string: offset = %d '%s', ", file_act, s);
        char* s2 = strchr(s, ' ');
        *s2++ = '\0';
        int row = atoi(s), seat = atoi(s2);
        printf("row = '%s'(%d), seat = '%s'(%d);\n", s, row, s2, seat);
        int row_size = 0, is_loaded = 0;
        for (int i = 0; i < counter; ++i)
            if (rows_data[i] == row)
                is_loaded = 1;
        if (!is_loaded) {
            rows_data[counter++] = row;
            seats_data[row_size++] = seat;
            while ((fgets(s, BUFF_SIZE, file)) != NULL) {
                s[strlen(s) - 1] = '\0';
                s2 = strchr(s, ' ');
                *s2++ = '\0';
                int next_row = atoi(s), next_seat = atoi(s2);
                printf("next row = '%s'(%d), next seat = '%s'(%d);\n", s, next_row, s2, next_seat);
                if (next_row == row)
                    seats_data[row_size++] = next_seat;
            }
            printf("seats in row %d: ", row);
            for (int i = 0; i < row_size; ++i)
                printf("%d ", seats_data[i]);
            printf("\nseats in row after sort:");
            for (int i = 0; i < row_size; ++i)
                for (int j = 0; j < row_size - i - 1; ++j)
                    if (seats_data[j + 1] < seats_data[j]) {
                        int t = seats_data[j];
                        seats_data[j] = seats_data[j + 1];
                        seats_data[j + 1] = t;
                    }
            for (int i = 0; i < row_size; ++i)
                printf("%d ", seats_data[i]);
            printf("\nsearch in pairs with min seats, ");
            for (int i = 0; i < row_size - 1; ++i) {
                if ((seats_data[i + 1] - seats_data[i] == 3) && (seats_data[i] < min)) {
                    printf("min row is founded between %d and %d seats;\n",
                           seats_data[i], seats_data[i + 1]);
                    min = seats_data[i] + 1; //if ((seats_data[i] + 1) < min)
                    min_row = row;
                }
            }
            if (min_row != row)
                printf("min is less then current row;\n");
        } else
            printf("row %d is already processed;\n", row);
        fseek(file, file_act, SEEK_SET);
    }
    printf("\nmin seat is %d, row is %d and rows in buffer = %d;\n", min, min_row, counter);
    printf("rows in buffer: ");
    for (int i = 0; i < counter; ++i)
        printf("%d ", rows_data[i]);
    if (fclose(file))
        printf("error: can't close file");
}

static int group_data[BUFF_SIZE], lcm_size[BUFF_SIZE], lcm_data[BUFF_SIZE][BUFF_SIZE];

void exam_27()
{
    /*
     Задание 27:
    Набор данных состоит из групп натуральных чисел, каждая группа записана в отдельной строке.
    В любой группе содержится не менее двух чисел.
    Из каждой группы выбрали два числа и нашли их наименьшее общее краткое (НОК).
    Затем все полученные таким образом значения НОК сложили. Определите наибольшую сумму,
    кратную числу 5 или 7 (но не одновременно двум этим числам),
    которая может быть получена таким образом.
    Входные данные. Даны два входных файла (файл A и файл B),
    каждый из которых содержит в первой строке количество чисел N (2 ≤ N ≤ 100000).
    В каждой из следующих N строк файлов записан сначала размер группы K (N <= 10),
    а затем – K натуральных чисел, не превышающих 500.

    4 - количество групп чисел.
    2 8 6 - группа из двух чисел (одна пара).
    3 2 7 8 - группа из 3-х (три пары).
    2 6 5 - группа из двух чисел (одна пара).
    4 7 3 8 6 - группа из четырёх чисел (шесть пар).
    1-я группа НОК = 24;
    2-я группа НОК = 14, 8, 56;
    3-я группа НОК = 30;
    4-я группа НОК = 6, 21, 24, 24, 42, 56;
    Сумма = 24 + 14 + 30 + 42 = 110 (оно делится на 5);
    Комбинации: n * (n / 2) = 500 * 250 = 125000 * 100000 = 12.500.000.000 = 12.5 * 10^9 * 4 ~ 50Gb;
    */
    printf("Test 27. Variant 1:\n");
    FILE*  file = fopen("27_2.txt", "r");
    if (file == NULL) {
        printf("error: file '27_1' not found;\n");
        return;
    }
    char s[BUFF_SIZE];
    int total = 0, counter = 0, group_size = 0, i = 0, j = 0, k = 0;
    if ((fgets(s, BUFF_SIZE, file)) == NULL) {
        printf("total seats error;\n");
        return;
    }
    total = atoi(s);
    printf("total groups = %d\n", total);
    while ((fgets(s, BUFF_SIZE, file)) != NULL) { // сохраняем все НОК для последующего перебора.
        char* s_next, *s_data;
        s[strlen(s) - 1] = '\0';
        s_next = strchr(s, ' ');
        *s_next++ = '\0';
        group_size = atoi(s);
        //printf("\n\ngroup data founded, size is '%s' and %d: ", s, group_size);
        for (i = 0; s_next != NULL; s_next = s_data, ++i) {
            s_data = strchr(s_next, ' ');
            if (s_data != NULL)
                *s_data++ = '\0';
            group_data[i] = atoi(s_next);
            //printf("'%s'(%d) ", s_next, group_data[i]);
        }
        //printf("\n All LCM in group %d; Pair n-m and (LCM): ", counter);
        //Все числа в группе уникальны, если будут повторения, то подстаховаться.

        int gcd, lcm, lcm_sum;
        for (i = 0, lcm_size[counter] = 0; i < group_size - 1; ++i) {
            for (j = i + 1; j < group_size; ++j) {
                int a = group_data[i], b = group_data[j]; //Если что - функция.
                while (a != 0 && b != 0)
                    if (a > b)
                        a %= b;
                    else
                        b %= a;
                gcd = a + b;
                lcm = abs(group_data[i] * group_data[j]) / gcd;
                lcm_data[counter][lcm_size[counter]] = lcm;
                ++lcm_size[counter];
                printf("%d-%d(%d) ", group_data[i], group_data[j], lcm);
            }
        }
        ++counter;
    }


    for (i = 0; i < counter; ++i)
        for (j = 0; j < lcm_size[i]; ++j)
            for (k = 0; k < lcm_size[i] - j - 1; ++k)
                if (lcm_data[i][k] < lcm_data[i][k + 1]) {
                    int t = lcm_data[i][k];
                    lcm_data[i][k] = lcm_data[i][k + 1];
                    lcm_data[i][k + 1] = t;
                }
    printf("\n\nAll LCM data(maybe) sorted: ");
    for (i = 0; i < counter; ++i) {
        //printf("\n%d, size = %d: ", i , lcm_size[i]);
        for (j = 0; j < lcm_size[i]; ++j)
            ;//printf("%d ", lcm_data[i][j]);
    }

    int sum_idx[BUFF_SIZE], idxs[BUFF_SIZE], sum = -1, sum_max = -1;
    for (i = 0; i < BUFF_SIZE; ++i) {
        sum_idx[i] = -1;
        idxs[i] = 0;
    }
    printf("\n\nSearch max sum from LCM groups divided by 5 or 7 (not both);");
    do {
        printf("\nindexes and data to sum: ");
        for (i = 0, sum = 0; i < counter; ++i) {
            sum += lcm_data[i][idxs[i]];
            //printf("%d:%d(%d) ", idxs[i], lcm_data[i][idxs[i]], sum);
        }
        if ((sum % 5 == 0 || sum % 7 == 0) && !(sum % 5 == 0 && sum % 7 == 0)) {
            printf("-Yes, sum is founded, ");
            if (sum > sum_max) {
                sum_max = sum;
                ;//printf("new max = %d;\n", sum_max);
            } else
                ;//printf("but less than max %d;\n", sum_max);
        }
        i = 0;
        while (i < counter && ++idxs[i] == lcm_size[i])
            idxs[i++] = 0;
    } while(i < counter);
    if (fclose(file))
        printf("error: can't close file");
}

void exam_1()
{
    // Решается устно. По таблице.
}

#define WORD_MAX 7
#define SEQ_MAX 4

int sequences[WORD_MAX][SEQ_MAX] = {{ -1, -1, -1, -1 },
                                    { 0, 1, -1, -1 },
                                    { 1, 1, 0, -1 },
                                    { -1, -1, -1, -1},
                                    { 1, 0, 1, 0 },
                                    { -1, -1, -1, -1},
                                    { 0, 0, 1, -1},
                                   };

void print_seq(int word_size, char word[])
{
    for (int i = 0, j = 0, size = 0; i < word_size; ++i) {
        printf("%c: ", word[i]);
        for (j = 0, size = 0; j < SEQ_MAX; ++j)
            if (sequences[i][j] != -1) {
                printf("%2d", sequences[i][j]);
                ++size;
            } else
                printf("  ");
        printf(" :size = %d;\n", size);
    }
}

void exam_4()
{
    //Для кодирования некоторой последовательности, состоящей из букв П, О, Е, Х, А, Л, И,
    //решили использовать неравномерный двоичный код, удовлетворяющий условию Фано.
    //Для букв О, Е, А, И использовали соответственно кодовые слова 01, 110, 1010, 001.
    //Найдите наименьшую возможную суммарную длину всех кодовых слов.
    const int word_size = 7;
    char word[WORD_MAX + 1] = "ABCDEFG";
    int seq_sizes[WORD_MAX], sequence_code = 0, path[SEQ_MAX], path_size = 0;
    //int path_stack[WORD_MAX * SEQ_MAX]; Если дерево потребует расширения.
    int chars_freq[WORD_MAX];   // Заменить генератором с разбросом по всему дереву.
    for (int i = 0; i < WORD_MAX; ++i) {
        seq_sizes[i] = 0;
        chars_freq[i] = 0;
    }
    printf("Task 4. Prefix code.\n"
    "Init sequences with max size = %d and word size = %d;\n", SEQ_MAX, word_size);
    printf("Sequences and sizes:\n");
    for (int i = 0; i < word_size; ++i) {
        for (int j = 0; j < SEQ_MAX; ++j)
            if (sequences[i][j] != -1)
                seq_sizes[i]++;
        if (seq_sizes[i] > 0)
            sequence_code++;
        chars_freq[word[i] - 'A']++;
    }
    print_seq(word_size, word);
    printf("char freqency in word %s: ", word);
    for (int i = 0; i < word_size; ++i) {
        if (seq_sizes[i] > 0)
            printf("%c:%d(coded)\n", word[i], chars_freq[i]);
        else
            printf("%c:%d(not coded)\n", word[i], chars_freq[i]);
    }
    /*
    path[0] = 1;
    path[1] = 0;
    path[2] = 0;
    path[3] = 0;
    path_size = 3;
    */
    for (int i = 0; i < SEQ_MAX; ++i) {
        path[i] = 0;
    }
    path_size = 1;
    //sequence_code = 6;
    while (sequence_code < word_size) {
        printf("\n\nTry to compare path with size %d: ", path_size);
        for (int i = 0; i < path_size; ++i)
            printf("%d ", path[i]);
        int is_comp = sequence_code, j = 0; // Возможно обратный порядок более удобен.
        for (int i = 0; i < word_size && is_comp; ++i) {
            printf("\nCompare with %d path in table: ", i);
            if (seq_sizes[i] > 0) {
                for (j = 0; j < seq_sizes[i]; ++j)
                    printf("%d ", sequences[i][j]);
                printf("\n");
                for (j = 0; j < path_size && j < seq_sizes[i] && sequences[i][j] == path[j]; ++j)
                    ;
                if ((path_size <= seq_sizes[i] && j == path_size) ||
                        (path_size > seq_sizes[i] && j == seq_sizes[i])) {
                    printf("Path is incorrect and %d position;\n", j);
                    is_comp = 0;
                } else
                    printf("Path is correct;\n");
            } else
                printf("sequences is empty, nothing to compare;\n");
        }
        if (is_comp) {
            printf("All sequences is correct, copy to path table;\n");
            int free = 0;
            while (seq_sizes[free] != 0)
                free++;
            for (int i = 0; i < path_size; ++i)
                sequences[free][i] = path[i];
            seq_sizes[free] = path_size;
            sequence_code++;
            print_seq(word_size, word);
        } else
            printf("sequences blocking path;\n");
        int k = 0;
        while (k < path_size && ++path[k] == 2)
            path[k++] = 0;
        if (k == path_size) {
            path_size = k + 1;
            for (int k = 0; k < SEQ_MAX; ++k)
                path[k] = 0;
        }
    }
}

void task_5()
{
    /*Автомат обрабатывает десятичное натуральное число N по следующему алгоритму:
    1) Строится двоичная запись числа N.
    2) К этой записи справа дописывается 0, если число нечетное, и слева 1 в обратном случае.
    3) Если единиц в двоичном числе получилось четное количество, справа дописывается 1, иначе 0.
    Например, двоичная запись 1010 числа 10 будет преобразована в 110100.
    Полученная таким образом запись (в ней на два разряда больше, чем в записи исходного числа N)
    является двоичной записью числа – результата работы данного алгоритма.
    Укажите минимальное число N, для которого результат работы алгоритма будет больше 228.
    В ответе это число запишите в десятичной системе счисления.*/
    printf("Number in binary with shifts, that more than 15;\n");
    int n = 1, m, r = 0, bits, mask, bits_on;
    while (r <= 228) {
        m = n;
        bits = 0;
        mask = 0x01;
        bits_on = 0;
        while (m > 0) {
            ++bits;
            m >>= 0x01;
            mask <<= 0x01;
        }
        printf("n = %d, bits = %d, mask = %X hex\n", n, bits, mask);
        r = 15;
        m = n;
        if (m % 2 != 0) {
            m <<= 0x01;
            printf("number is odd, insert low bit(0), number = %d;\n", m);
        } else {
            m |= mask;
            printf("number is even, insert high bit(1), number = %d;\n", m);
        }
        r = m;
        while (m) {
            if (m & 0x01)
                ++bits_on;
            m >>= 0x01;
        }
        if (bits_on % 2 == 0) {
            r = (r << 0x01) | 0x01;
            printf("bits_on = %d, is even, set low bit to 1, number = %d;\n", bits_on, r);
        } else {
            r <<= 0x01;
            printf("bits_on = %d, is odd, set low bit to 0, number = %d;\n", bits_on, r);
        }
        ++n;
    }
}

void task_6()
{
    /*Какое максимальное значение переменной s, подаваемого на вход программе,
     для которого в результате работы программы на экран будет выведено значение 46?*/
    int n = 1, s = 0, m = 200;
    printf("Source code from task 6 with par, s[200..n], for algorithm;\n");
    while (n <= 46) {
        n = 1; s = ++m;
        while(s > 200) {
            s = s - 15;
            n = n + 3;
        }
        printf("s = %d, n = %d;\n", m, n);
    }
    printf("s par with n = 46 is %d;\n", --m);
}

void task_7()
{
    /*
    Найдите битовую глубину кодирования растрового изображения размером 512x300 пикселей,
    которое занимает 600 Кбайт. В ответе запишите только целое число, единицу измерения писать не нужно.
    */
    const int scr_x = 512, scr_y = 300, vram_kb = 600;
    printf("bit map sizes %dx%d pixels and vram %d kbyte;\n", scr_x, scr_y, vram_kb);
    int scr_pixels = scr_x * scr_y;
    int vram_bits = vram_kb * (0x01 << 10) * CHAR_BIT;
    int bits_per_pixel = vram_bits / scr_pixels;
    printf("screen pixels = %d, vram in bits = %d and color depth is %d bits;\n",
           scr_pixels, vram_bits, bits_per_pixel);
}

void task_11()
{
    /*
  * Автомобильный номер состоит из одиннадцати букв русского алфавита
  * A, B, C, E, H, K, M, O, P, T, X и десятичных цифр от 0 до 9.
  * Каждый номер состоит из двух букв, затем идет 3 цифры и еще одна буква.
  * Например, АВ901С. В системе каждый такой номер кодируется посимвольно,
  * при этом каждая буква и каждая цифра кодируются одинаковым минимально возможным количеством бит.
  * Укажите, на сколько бит можно уменьшить размер памяти,
  * выделенной для хранения одного номера, если кодировать с помощью минимально
  * возможного количества бит каждую из трех групп – первые две буквы, три цифры и последняя буква.
  */
    const int alphabet_size = 11, digit_size = 10, fields = 3;
    const int field_sizes[] = {2, 3, 1}, all_fields = 6, bits_std = 4;
    printf("Task 11. Coding %d chars and %d digits, usint bit fields;\n", alphabet_size, digit_size);
    printf("Every number format: %d chars + %d digits + %d char, example = AB901C;\n",
           field_sizes[0], field_sizes[1], field_sizes[2]);
    printf("Every char need %d bits and every digit %d bits (more than 2^3 but less than 2^4);\n",
           bits_std, bits_std);
    int field_bits[] = {0, 0, 0}, total_bits = all_fields * bits_std, packed_bits = 0;
    for (int i = 0; i < fields; ++i) {
        if (field_sizes[i] > 0) {
            field_bits[i] = 0;
            int comb = (i != 1) ? alphabet_size : digit_size;
            for (int j = 0; j < field_sizes[i] - 1; ++j)
                if (i != 1)
                    comb *= alphabet_size;
                else
                    comb *= digit_size;
            printf("field = %d, size = %d, max combinations = %d;\n", i, field_sizes[i], comb);
            while(comb > 0) {
                ++field_bits[i];
                comb /= 2;
            }
            printf("bits to store = %d;\n", field_bits[i]);
            packed_bits += field_bits[i];
        } else
            printf("error: field size = 0;\n");
    }
    printf("Total bits as is(4 * 6 = 24) = %d\n", total_bits);
    printf("Total bits as fields = %d;\n", packed_bits);
    printf("diff packed mod = %d;\n", total_bits - packed_bits);
}

void task_12()
{
    /*
     * Исполнитель Редактор получает на вход строку цифр и преобразовывает её.
     *  Редактор может выполнять две команды, в обеих командах v и w обозначают цепочки символов.
     1. заменить (v, w)
     2. нашлось (v)
     Первая команда заменяет в строке первое слева вхождение цепочки v на цепочку w.
     Если цепочки v в строке нет, эта команда не изменяет строку.
     Вторая команда проверяет, встречается ли цепочка v в строке исполнителя Редактор.
     Дана программа для исполнителя Редактор:
     ПОКА нашлось(42) или нашлось(32)
     ЕСЛИ нашлось(42)
     ТО заменить(42, 51)
     ИНАЧЕ заменить(32, 61)
     КОНЕЦ ПОКА
     На вход программе подана строка, содержащая только 20 двоек, 15 троек и 10 четверок.
     Порядок символов заранее неизвестен. Определите максимально возможную сумму всех цифр в конечной строке.
     */
    printf("Task 12. Execute rules on string, using char without stdlib;\n");
    //3232..4242..4444 - maximum sum.
    const int digits_2 = 20;
    const int digits_3 = 15;
    const int digits_4 = 10;
    const int digits_total = 45;
    printf("digits 2 is %d, digits 3 is %d, digits 4 is %d, total digits is %d;\n",
           digits_2, digits_3, digits_4, digits_total);
#define TEXT_MAX 256
    char digits[TEXT_MAX];
    for (int i = 0; i < digits_total ;++i) {
        if (i < digits_3 * 2) {
            digits[i] = '3';
            digits[++i] = '2';
        } else if (i < digits_2 * 2) {
            digits[i] = '4';
            digits[++i] = '2';
        } else
            digits[i] = '4';
    }
    digits[digits_total] = '\0';
    printf("source string with default size %d: '%s';\n", digits_total,  digits);
    int is_32 = 1, is_42 = 1, sum_digits = 0;
    while (is_32 || is_42) { // более общие с перезаписью или два простых цикла если перезаписи нет.
        is_32 = 0;
        is_42 = 0;
        for (int i = 0; i < digits_total - 1; ++i) {
            if (digits[i] == '3' && digits[i + 1] == '2') {
                digits[i] = '6';
                digits[i + 1] = '1';
                is_32 = 1;
            }
        }
        for (int i = 0; i < digits_total - 1; ++i) {
            if (digits[i] == '4' && digits[i + 1] == '2') {
                digits[i] = '5';
                digits[i + 1] = '1';
                is_42 = 1;
            }
        }
    }
    for (int i = 0; i < digits_total; ++i)
        sum_digits += digits[i] - '0';
    printf("result after replace: '%s', and sum of digits = %d;\n", digits, sum_digits);
}

void task_22()
{
    /*
     Ниже на трёх языках программирования записан алгоритм.
     Получив на вход число X, этот алгоритм печатает одно число.
     Укажите наименьшее число Х, большее 80,
     при вводе которого алгоритм печатает число 17.
     */
    printf("Task 22. Param X with source code result 17;\n");
    int x = 80, y = 0, s = 0;
    while (s != 17) {
        y = ++x;
        s = 0;
        while (y > 0) {
            s = s + y % 9;
            y /= 3;
        }
        printf("param = %d, result = %d;\n", x, s);
    }
    printf("result = %d and x = %d;\n", s, x);
}

void print_words(unsigned short regs[], int words)
{
    for (int i = 0; i < words; ++i) {
        printf("reg %d:\t", i);
        for (unsigned short bits = sizeof(short) * CHAR_BIT - 1, mask = 0x8000; mask; --bits, mask >>= 0x01)
            printf("%d", (regs[i] & mask) >> bits);
        printf("\n");
    }
}

void task_14()
{
    /*
     Значение выражения (64^25 + 4^10) – (16^20 + 32^3)
     записали в системе счисления с основанием 4.
     В каком разряде четверичной записи числа при просмотре
     справа налево впервые встречается цифра 2?
     */
    // Сложение и вычитание по степеням. Умножения и деления нету.
    // 4 ^ 4 = 2 ^ (2 * 4) = 2 ^ 8 = 256.
    // (8 ^ 2 + 4 ^ 2) - (16 ^ 1 + 20) =
    // = (2^(3*2) + 2^(2*2)) - (2^4 + 2^4 + 2^2) =
    // = (2^6 + 2^4) - (2^4 + 2^4 + 2^2).
    // Максимальное значение 16 бит
    unsigned short regs[4] = {512, 4096};
    printf("Digits info in expr, 16 bits maximum: (8^2 + 4^2) - (16^1 + 20) = "
           "(2^(3*2) + 2^(2*2)) - (2^4 + 2^4 + 2^2) = "
           "(2^6 + 2^4) - (2^4 + 2^4 + 2^2).\n");
    printf("Example R1 decimal %d, octal %o, R2 decimal %d, hex %x;\n",
           regs[0], regs[0], regs[1], regs[1]);
    printf("All digits from left to right, from high to low memory;\n");
    printf("\nAdd 2^6 + 2^3;\n");
    regs[0] = 0x01 << 0x06;
    regs[1] = 0x01 << 0x03;
    regs[2] = regs[0] + regs[1];
    print_words(regs, 3);
    printf("\nsub 2^1 from 72, counter of 1 (max of base) is diff in positions;\n");
    regs[0] = regs[2];
    regs[1] = 0x01 << 0x01;
    regs[2] = regs[0] - regs[1];
    print_words(regs, 3);
    printf("\nMultiply digits in position to any number, 5 * 2^4, move left;\n");
    regs[0] = 0x01 << 0x04;
    regs[1] = 0x05;
    regs[2] = regs[0] * regs[1];
    print_words(regs, 3);
    printf("\nDivide any number in position, 80 / 2^3, move right;\n");
    regs[0] = 0x50;
    regs[1] = 0x01 << 0x03;
    regs[2] = regs[0] / regs[1];
    print_words(regs, 3);
    printf("\nCalculate expression: (2^4 + 2^4 + 2^2);\n");
    regs[0] = 0x01 << 0x04;
    regs[1] = regs[0];
    regs[2] = 0x01 << 0x02;
    regs[3] = regs[0] + regs[1] + regs[2];
    print_words(regs, 4);
    printf("\nCalculate expression: (2^6 + 2^4);\n");
    regs[0] = 0x01 << 0x06;
    regs[1] = 0x01 << 0x04;
    regs[2] = regs[0] + regs[1];
    print_words(regs, 3);
    printf("\nCalculate expression: (2^6 + 2^4) - (2^4 + 2^4 + 2^2);\n");
    regs[0] = regs[2];
    regs[1] = regs[3];
    regs[2] = regs[0] - regs[1];
    regs[3] = 0;
    print_words(regs, 3);
    printf("Bits counter in result: ");
    while(regs[2]) {
        printf("%d", regs[2] & 0x01);
        regs[3] += regs[2] & 0x01;
        regs[2] >>= 0x01;
    }
    printf("\nTotal %d bits;\n", regs[3]);
    printf("Simple method source expression: (64^25 + 4^10) – (16^20 + 32^3);\n");
    const int base = 4;
    printf("Expression using base: %d;\n", base);
    printf("(4^(3*25) + 4^10) - (4^(2*20) + 4^7 + 4^7);\n");
    // 32^3 = 1024 * 32 = 32768 = 16384 + 16384 = 4^7 + 4^7;
    printf("powers to add 75, 10, powers to sub 40, 2 * 7;\n");
    printf("digits 3, counter from 75 to 40 = 35. 0333..[35]");
    printf("digits 3, counter from 10(10 less than 40 and 35) - 2 = 8. (0333[8]);\n");
    printf("decriase digits from previous from 7 = 8 - 7 = 02333..[7];\n");
    printf("Result 7 as sub;\n");
    //1.000.000 - 10.000 = 990.000, powers 6 - 4
    // 990.000 + 1.000 = 991.000 powers 5 + 3
    // 991.000 - 100 = 990.900 = powers 3 - 2
    // 990.900 - 100 = 990.800 = powers 3 - 2 (3 - n)
}

void task_15()
{
    /*
     На числовой прямой даны два отрезка: P=[10,29] и Q=[13,18].
     Укажите наибольшую возможную длину такого отрезка A, что формула
     ((x ∈ A) → (x ∈ P)) ∨ (x ∈ Q)
     тождественно истинна, то есть принимает значение 1 при любом значении переменной х.
     */
#define SEG_MAX 8
    const int points = 4, infinity = -1;
    int pts[SEG_MAX] = {10, 29, 33, 38}, segs[SEG_MAX], sizes[SEG_MAX], prev_seg = -1, ranges = 0;
    printf("Expression: ((X from A) -> (X from P)) or (X from Q), where P=[%d:%d] and Q=[%d:%d],"
        " A has max rage;\n", pts[0], pts[1], pts[2], pts[3]);
    for (int i = 0; i < SEG_MAX; ++i) {
        if (i < points)
            segs[i] = pts[i];
        else
            segs[i] = 0;
        sizes[i] = 0;
    }
    for (int i = 0; i < points; ++i)
        for (int j = 0; j < points - 1; ++j)
            if (segs[j] > segs[j + 1]) {
                int tmp = segs[j];
                segs[j] = segs[j + 1];
                segs[j + 1] = tmp;
            }
    printf("Cheking values in all %d segments;\n", points + 1);
    for (int i = 0, j = 0, size = 0; i < points + 1; ++i) {
        if (i == 0) {
            printf("Segment(-,%d]: ", segs[0]);
            j = segs[i] - 1;
            if (1 <= (j >= pts[0] && j <= pts[1]) || (j >= pts[2] && j <= pts[3]))
                ++j; //С точки зрения математики возможен цикл.
            size = infinity;
        } else if (i < points) {
            printf("Segment[%d,%d]: ", segs[i - 1], segs[i]);
            for (j = segs[i - 1]; j < segs[i]; ++j) //Оптимизация!
                if (!(1 <= (j >= pts[0] && j <= pts[1]) || (j >= pts[2] && j <= pts[3])))
                    break;
            size = segs[i] - segs[i - 1];
        } else  {
            printf("Segment:[%d,+): ", segs[i - 1]);
            j = segs[i - 1] + 1;
            if (1 <= (j >= pts[0] && j <= pts[1]) || (j >= pts[2] && j <= pts[3]))
                --j;
            size = infinity;
        }
        if (j == segs[i]) {
            printf("Yes, expression is true and ");
            if (i > 0 && size != infinity && ((i - 1) == prev_seg) && ranges > 0) {
                // Правая точка предыдущего отрезка является левой текущего.
                sizes[ranges - 1] += size;
                prev_seg++;
                printf("Previous segment all is true, update range, new size = %d;\n",
                       sizes[ranges - 1]);
            } else {
                sizes[ranges] = size;
                prev_seg = i;
                ranges++;
                printf("size is new range = %d, total ranges = %d;\n", size, ranges);
            }
        } else
            printf("No, expression is false;\n");
    }
    printf("All ranges with sizes: ");
    int max = 0, min = 100;
    for (int i = 0; i < ranges; ++i) {
        printf("%d ", sizes[i]);
        if (sizes[i] > max)
            max = sizes[i];
        if (sizes[i] < min)
            min = sizes[i];
    }
    printf("\nMax = %d and min = %d in ranges;\n", max, min);
}

static int rec_depth = 0;

int func_recur(int n)
{
    if (n < 0) {
        printf("error: n(%d) less than 0;\n", n);
        return -1;
    }
    printf("enter func with parameter %d and depth recur = %d;\n", n, rec_depth);
    if (n == 0 || n == 1)
        return 1;
    ++rec_depth;
    int result = 0;
    if (n % 2 == 0)
        result = func_recur(n - 1) - func_recur(n - 2) + 3 * n;
    else
        result = func_recur(n - 2) - func_recur(n - 3) + 2 * n;
    --rec_depth;
    printf("func returned %d, depth recur = %d;\n\n", result, rec_depth);
    return result;
}

#define CACHE_MAX 3

static int calls = 0, calls_max = 5;

struct cache_pair
{
    int n;
    int result;
};

struct call
{
    int n;      // Само значение параметра вызова
    int left;   // Вызов функции слева
    int right;  // Вызов функции справа
    int add;    // Доп. параметр
    int ret_idx;// Индекс возврата, требуется для многопоточности

};

void print_calls(struct call* addr, int n)
{
    printf("Stack in memory with values, size = %d, bytes = %d;\n", calls, calls * sizeof(struct call));
    printf("addr:\t\tn:\tleft:\tright:\tadd:\tret_idx:\n");
    while (n > 0) {
        printf("%p\t%d\t%d\t%d\t%d\t%d\n",
               (void*)addr, addr->n, addr->left, addr->right, addr->add, addr->ret_idx);
        ++addr;
        --n;
    }
}

int push_call(struct call* addr, int n, int prev)
{   //При однопотоке используется предыдущий вызов, при многопотоке параметр предыдущего произволен.
    if (n < 2 || calls == calls_max || prev > calls) {
        printf("error: n = %d is less than 2, or prev call = %d is more than total, or stack is full;\n",
               n , prev);
        return -1;
    }
    addr[calls].n = n;
    addr[calls].ret_idx = prev;
    if (n % 2 == 0) {
        addr[calls].left = -1 * (n - 1);
        addr[calls].right = -1 * (n - 2);
        addr[calls].add = 3 * n;
    } else {
        addr[calls].left = -1 * (n - 2);
        addr[calls].right = -1 * (n - 3);
        addr[calls].add = 2 * n;
    }
    calls++;
    return 0;
}

int pop_call(struct call* addr)
{   //Вычисляем функцию если возможно, копируем результат в предыдущий первый отрицательный
    //или возвращаем окончательный.
    // Порядок исполнения имеет значение так как вычитание!
    if (calls <= 0) {
        printf("stack of calls is empty;\n");
        return -1;
    }
    if (addr[calls - 1].left < -1 || addr[calls - 1].right < -1) {
        printf("pop call incorrect for left %d or right %d values;\n",
               addr[calls - 1].left, addr[calls - 1].right);
        return 0; // результат функции всегда больше 0, или нужно ввести доп. флаг;
    }
    --calls;
    if (addr[calls].left == 0 || addr[calls].left == -1)
        addr[calls].left = 1;           // только для нашей функции т.к результат 0 или 1 невозможен.
    if (addr[calls].right == 0 || addr[calls].right == -1)
        addr[calls].right = 1;
    int result = addr[calls].left - addr[calls].right + addr[calls].add;
    if (calls == 0) {
        printf("top of stack, last result is %d;\n", result);
        return result;
    }
    int previous = addr[calls].ret_idx;
    if (addr[previous].left < 0) {
        printf("replace previous left = %d at index = %d with result = %d;\n",
               addr[previous].left, previous, result);
        addr[previous].left = result;
    } else if (addr[previous].right < 0) {
        printf("replace previous right = %d at index = %d with result = %d;\n",
               addr[previous].right, previous, result);
        addr[previous].right = result;
    } else {
        printf("error: no negative %d and %d right previous call;\n",
               addr[previous].left, addr[previous].right);
        return -1;
    }
    return result;
}

int cache_find(struct cache_pair* cache, int n)
{       // Линейный поиск значения функции в кеше.
    // Возвращаем значения всегда больше 0 или 0 если не нашли.
    int i = 0;
    while (i < CACHE_MAX && cache[i].n != n)
        ++i;
    if (i != CACHE_MAX)
        return cache->result;
    else
        return 0;
}

void cache_update(struct cache_pair* cache, int n, int result)
{       //Обновление кеша по всему размеру с простой очередью
    //для простых значений и поиском уже имеющихся
    if (cache_find(cache,n)) {
        printf("cache is already has value = %d;\n", n);
        return;
    }
    for (int i = CACHE_MAX - 1; i > 0; --i)
        cache[i] = cache[i - 1];
    printf("updating cache with new n = %d, result = %d", n , result);
    cache[0].n = n;
    cache[0].result = result;
}

void task_16()
{
    // Простая рекурсия или можно напрямую оба варианта.
    printf("Recursive function with parameter(40).\n"
               "F(0) = 1, F(1) = 1;\n"
               "F(n) = F(n - 1) - F(n - 2) + 3 * n, if n > 1 and even;\n"
               "F(n) = F(n - 2) - F(n - 3) + 2 * n, if n > 1 and odd.\n");
    //printf("Result of F(6) = %d.\n", func_recur(6));
    printf("\nresult of func without recur with dynamic memory;\n");
    struct call* data = calloc(calls_max, sizeof(struct call));
    struct cache_pair cache[CACHE_MAX];
    for (int i = 0; i < CACHE_MAX; ++i) {
        cache[i].n = 0;
        cache[i].result = 0;
    }

    printf("addr of data in heap = %p, %u, struct = %u and data = %u bytes;\n",
           data, sizeof(data), sizeof(struct call), sizeof(*data) * calls_max);
    //print_calls(data, calls_max);
    // Отрицательные значения с стеке слева и справа означают необходимость вычисления.
    // Отрицательные результаты невозможны в нашей функции.
    printf("Negative values using as call, positive as return result;\n");
    int n = 11, result = 1, iters = 0, is_error = 0, is_cache = 1, cache_hits = 0;
    if (n < 2) {
        printf("nothing to calculate, result is 1 or doesn't exist;\n");
        return;
    }
    printf("Partly recur until constants f(0) and f(1), pushs and pops;\n");
    print_calls(data, calls_max);
    push_call(data, n, 0);
    while (calls && !is_error) {
        printf("\n");
        print_calls(data, calls_max);
        if (data[calls - 1].left < -1) {        // или можно два значения одновременно
            n = -1 * data[calls - 1].left;
            printf("left call push to stack, n = %d;\n", n);
            if (is_cache && (result = cache_find(cache, n))) {
                printf("call founded in cache, result is %d, replace prev left value;\n", result);
                data[calls - 1].left = result;
                ++cache_hits;
            } else
                is_error = push_call(data, n, calls - 1);
        } else if (data[calls - 1].right < -1) {
            n = -1 * data[calls - 1].right;
            printf("right call push to stack, n = %d;\n", n);
            if (is_cache && (result = cache_find(cache, n))) {
                printf("call founded in cache, result is %d, replace prev right value;\n", result);
                data[calls - 1].right = result;
                ++cache_hits;
            } else
                is_error = push_call(data, n, calls - 1);
        }
        print_calls(data, calls_max);
        n = data[calls - 1].n;
        result = pop_call(data);
        if (result > 0) {
            ++iters;
            cache_update(cache, n, result);
        } else if (result == -1)
            is_error = 1;
        printf("\ncache: ");
        for (int i = 0; i < CACHE_MAX; ++i)
            printf("%d ", cache[i].n);
        printf("\n\n");
    }
    printf("Total calls = %d, cache hits = %d;\n", iters, cache_hits);
    free(data);
}




