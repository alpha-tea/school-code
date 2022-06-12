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

