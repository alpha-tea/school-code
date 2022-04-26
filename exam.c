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
    int seats_data[BUFF_SIZE], total = 0, counter = 0,
            max = -1, max_pos = -1, file_seats = 0, file_act = 0;
    if ((fgets(s, BUFF_SIZE, file)) == NULL) {
        printf("total seats error;\n");
        return;
    }
    total = atoi(s);
    file_seats = ftell(file);
    printf("total seats = %d, seats data position = %d\n", total, file_seats);
    while ((fgets(s, BUFF_SIZE, file)) != NULL) {
        file_act = ftell(file);
        s[strlen(s) - 1] = '\0';
        printf("\nsource string: offset = %d '%s', ", file_act, s);
        char* s2 = strchr(s, ' ');
        *s2++ = '\0';
        int row = atoi(s), seat = atoi(s2);
        printf("row = '%s'(%d), seat = '%s'(%d);\n", s, row, s2, seat);
        int row_size = 0;
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
        fseek(file, file_act, SEEK_SET);
    }
    if (fclose(file))
        printf("error: can't close file");
}



