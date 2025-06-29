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

int array_rotate_range(int data[], int size, int start, int length, int direct);

int number_to_digits(int number, int data[], int size);

int find_max_recur(int numbers[], int length, int* idx, int max);

int char_to_hex(char c);

int uniq_gen_fast_alt(int number[], int length, int limit);

void string_reverse(char string[]);

int int_to_string(char dst[], int num, int base);

int uniq_gen_fast_alt_1(int number[], int start, int limit);

void print_binary_byte(unsigned char byte);

void exchange_of_values(int *a, int *b);
#endif
