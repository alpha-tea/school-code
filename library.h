#ifndef LIBRARY_H
#define LIBRARY_H

// Общая библиотека универсальных функций для всех глав задачника.

int string_length(char s[]);

int string_char_counter(char s[], char c);

int ideal_number(int a);

int evklid_first_step(int a, int b);

int length_number(int number);

int string_copy_substr(char src[], char dst[], int start, int length);

int string_is_equal(char string_1[], char string_2[]);
#endif
