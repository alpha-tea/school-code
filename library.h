#ifndef LIBRARY_H
#define LIBRARY_H

// Общая библиотека универсальных функций для всех глав задачника.

int string_length(char s[]);

int string_char_counter(char s[], char c);

int ideal_number(int a);

int evklid(int a, int b);

int length_number(int number);

int string_copy_substr(char src[], char dst[], int start, int length);

int string_is_equal(char string_1[], char string_2[]);

int string_insert( char dst[], char ins[], int start, int limit);

int factorial(int n);

int prime_number(int number);

int string_char_find(char s[], char c, int direct, int debug);

#endif
