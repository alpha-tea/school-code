﻿#include "global.h"
#include "library.h"

int string_char_find(char s[], char c, int direct, int debug)
{
    int index = string_length(s);
    if (index == 0) {
        if (debug == 1)
            printf("No chars in string;\n");
        return -1;
    }
    if (debug == 1)
        printf("Char before find: ");
    if (direct == 0) {
        index = 0;
        while (s[index] != c && s[index] != '\0') {
            if (debug == 1)
                printf("%c",s[index]);
            index++;
        }
    } else {
        index--;
        while (s[index] != c && index >= 0) {
            if (debug == 1)
                printf("%c",s[index]);
            index--;
        }
    }
    if (debug == 1)
        printf("\n");
    if (s[index] == c)
        return index;
    else
        return -1;
}

int string_length(char s[])
{
    int len = 0;
    while (s[len] != '\0') {
        ++len;
    }
    return len;
}

int string_is_equal(char string_1[], char string_2[])
{
    int help = 0;
    if (string_length(string_1) == 0 || string_length(string_2) == 0) {
        printf("String or substring are empty;\n");
        return -2;
    }
    for (int i = 0; string_1[i] != '\0' &&  string_2[i] != '\0'; ++i)
        if (string_1[i] == string_2[i])
            ++help;
    if (help > 0 && help < string_length(string_1))
        return help;
    else if (help == string_length(string_1))
        return 0;
    else
        return -1;
}

int string_copy_substr(char src[], char dst[], int start, int length)
{
    if (string_length(src) < length + start)
        return -1;
    int i = 0;
    for (i = 0; i < length; ++i)
        dst[i] = src[i + start];
    dst[i] = '\0';
    return i;
}

int string_char_counter(char s[], char c)
{
    int index = 0, src_len = string_length(s);
    for (int i = 0; i < src_len; ++i)
        if (s[i] == c)
            ++index;
    return index;
}

int ideal_number(int a)
{
    int b = a;
    int sum = 1;
    int i = 2;
    while (b > 1) {
        if (b % i == 0) {
            sum += i;
            b /= i;
        } else
            ++i;
    }
    return (a == sum);
}

int evklid(int a, int b)
{
    while (a != 0 && b != 0) {
        if (a > b)
            a %= b;
        else
            b %= a;
    }
    return a + b;
}

int length_number(int number)
{
    int i = 0;
    /*
    while (number > 0) {    //Для нуля и больше.
        number /= 10;
        ++i;
    }
    */
    do {
        number /= 10;
        ++i;
    } while (number > 0);
    return i;
}

int factorial(int n)
{
    int result = 1;
    for (; n > 0; --n)
        result *= n;
    return result;
}

int prime_number(int number)
{
    int i = 2;
    for (i = 2; i < number && number % i != 0; ++i)
        ;
    return (i == number);
}

int string_insert( char dst[], char ins[], int start, int limit)
{
    int ins_len = string_length(ins), dst_len = string_length(dst), i;
    if (ins_len == 0 || ins_len + start >= limit)
        return -1;
    for (i = ins_len + dst_len; i >= start + ins_len; --i)
        dst[i] = dst[i - ins_len];
    for (int j = start, i = 0; j < ins_len + start; ++j, ++i)
        dst[j] = ins[i];
    return 0;
}

int array_rotate_range(int data[], int size, int start, int length, int direct)
{
    if (size < 2 || start + length > size || length <= 1) {
        printf("error: in size or start or length;\n");
        return -1;
    }
    if (direct == 0) {  //Направление движения: если direct = 0 - влево, иначе вправо.
        int element = data[start];
        for (int i = start; i < start + length; ++i)
            data[i] = data[i + 1];
        data[start + length - 1] = element;
    } else {
        int element = data[start + length - 1];
        for (int i = start + length - 1; i > start; --i)
            data[i] = data[i - 1];
        data[start] = element;
    }
    return 0;
}

int number_to_digits(int number, int data[], int size)
{           // Преобразование числа в масив цифр, знак не учитывается.
    if (size < 1) {
        printf("error: int size or number;\n");
        return -1;
    }
    int counter = 0;
    do {
        data[counter] = number % 10;
        number /= 10;
        counter++;
    } while (number != 0 && counter < size);
    for (int i = 0; i < counter / 2; ++i) {
        int tmp = data[i];
        data[i] = data[counter - i - 1];
        data[counter - i - 1] = tmp;
    }
    return counter;
}
