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
 Текстовый файл 24-179.txt содержит строку из заглавных букв A, B, C, D, E, F,
 всего не более чем из 106 символов.
 Определите, сколько встречается комбинаций вида CB*BC,
 где на месте "*" может стоять любая буква, кроме A, B и F.
 В ответе укажите сначала букву, которая чаще всего встречается на месте "*",
 затем общее количество подходящих комбинаций.
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
