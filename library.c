#include "global.h"
#include "library.h"

int string_length(char s[])
{
    int len = 0;
    while (s[len] != '\0') {
        ++len;
    }
    return len;
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

int evklid_first_step(int a, int b)
{
    int c,d,i = 0;
    printf("Algoritm Evklida\n");
    while (a != 0 && b != 0) {
        if (a > b) {
            c = a;
            a %= b;
            ++i;
            printf("%d)a(%d) > b(%d);\nTotal: a = %d;\n\n",i,c,b,a);
        } else {
            d = b;
            b %= a;
            ++i;
            printf("%d)b(%d) > a(%d)\nTotal: b = %d;\n\n",i,d,a,b);
        }
    }
    return a + b;
}

int length_number(int number)
{
    int i = 0;
    while (number > 0) {
        number /= 10;
        ++i;
    }
    return i;
}
