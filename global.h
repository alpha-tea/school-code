﻿#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
//#include <stdbool.h>
#include <time.h>


// Глобальные константы (define) для всего проэкта.
#define STRING_MAX 256
#define OBJECTS_MAX 256
#define BYTE_NUMS 256   // Пока только в 9 главе. Кол - во чисел в байте.
#define WORD_BITS 16

// Функции и константы для первой главы задачника.

void chapter_1();


// Функции и константы для второй главы задачника.

void chapter_2();

// Функции и константы для третьей главы задачника.

double kalk(int c1, int c2);

void chapter_3();

// Функции и константы для четвёртой главы задачника.

void chapter_4();

// Функции и константы для пятой главы задачника.

double summary(int n);
int value(int a, int n, int base);
int sqrt_5_92();
int cubing(int n);
int squaring(int n);
void invert_1(const char s[], int len);
int group_values(int n,int g);
double exponentiation(double a, unsigned int n);
int multiply(int x, int y);
int numerical_generation_int();

void chapter_5();

// Функции и константы для шестой главы задачника.

#define ARRAY_SIZE 15

int evklid_first_step(int a, int b);
void number_of_degrees (int n);
void fibonachi(int n);
int arif_sequence(int n, int f, int s);
int geom_seqence(int m, int g, int z);
int natural_number(int n);
int lcm (int a, int b);

void chapter_6();

// Функции и константы для седьмой главы задачника.

#define SIZE 10

int string_size_special(char string[]);
void string_reverse_special(char string[]);
void to_binary(unsigned char byte, char string[]);
void ScriptedEngeneer_1();

void chapter_7();

// Функции и константы для восьмой главы задачника.

int prime_number(int number);
int digital_root(int n);

void chapter_8();

// Функции и константы для девятой главы задачника.

void string_exchange(char** s1, char** s2);
int string_find_sub(char s1[], char s2[]);
void string_clear(char s[], int len);
int string_concat(char src[], char dst[]);
int string_palindrom(char c[]);
int string_char_find(char s[], char c, int direct, int debug);
int string_find_seq(char s[], char c, int start, int length);
int num_radix(char src[], char dst[], int from, int to);
void print_binary_byte(unsigned char byte);
void print_binary_word(unsigned short int word);
unsigned char shift_logical_right(unsigned char dst[], unsigned char counter);
unsigned char add_byte(unsigned char dst[], unsigned char src[]);
unsigned char not_gate(unsigned char bit_1);
unsigned char and_gate(unsigned char bit_1, unsigned char bit_2);
unsigned char or_gate(unsigned char bit_1, unsigned char bit_2);
unsigned char xor_gate(unsigned char bit_1, unsigned char bit_2);
unsigned char nand_gate(unsigned char bit_1, unsigned char bit_2);
int string_xchg_chars(char src[], int table[], int count);
int string_delete(char src[], int start, int length);
void string_rlc(char src[], int counter);
void string_rrc(char src[], int counter);
int int_to_string(char dst[], int num, int base);
void string_reverse(char string[]);
int string_is_symmetrical(char string[]);
int string_checking_brackets(char src[]);
char boolean_calculator(char src[]);
int string_checking_brackets(char src[]);

void chapter_9();

// Функции и константы для десятой главы задачника.

#define SEQUENCE_LENGTH 11
#define NUMBERS_QUANTITY 6

int ackermann(int m, int n);
int symmetric_check_recur(char string[], int start, int end, int limit);
int prime_check_recur(int number, int* num_ptr);
void print_integer_recur(int number, int base);
int revers_number(int n, int result);
int flip_number(int n);
int find_max_recur(int numbers[], int length, int* idx, int max);
int fibonacci_recur(int n);
int arif_recur(int a1, int d, int n, int* sum);
int sum_arith_progres(int d, int n, int a1);
int value_arith_progres(int d, int n, int a1);
int digital_root_recur(int number);
int number_of_digits_recur(int number);
int sum_of_digits_recur(int number);
int expt (int base, int power);
int exp_recur(int power, int base);
int factorial_recur(int number);
int is_command_correct(char command[], int idx, int pars, int src_size);
void clear_screen(char* buffer, int size_x, int size_y, char fill);
void output_screen(char* buffer, int size_x, int size_y);
int pair_min(int a, int b);
int pair_max(int a, int b);
void exchange_of_values(int *a, int *b);
char hex_to_char(int c);
int char_to_hex(char c);
double triangle_heron(double a, double b, double c);
int check_even_or_odd(int mode, int value);
double line_vertex(double vertex[]);
int quadratic_equations(int a, int b , int c);
double perimeter_isosceles_trapezoid(double bases_1, double bases_2, double height);
double perimeter(double a, double b, double c);
double hypotenuse(double a, double b);
int sign(int number);
double calc_exp_10_1(int numbers[], int is_sqrt[], int exp_size, int terms);
double fraction_calculator_with_factorials(int numbers[], int is_factorial[]);
int digits_in_num(int num, int start, int len, int* sum);
int max_int_pair(int a, int b);
int degree_check(int value, int base);
int date_prev_day(int* day, int* month, int* year);
int date_next_day(int* day, int* month, int* year);
void print_date(int day, int month, int year, char* format);
int days_in_month(int month, int year);
int reduction_of_fractions(int numerator, int denominator, int debug);
int evklid_many_numbers(int mass[], int size);

void chapter_10();

// Функции и константы для одиннадцатой главы задачника.

void chapter_11();

// Функции и константы для допольнительных задач.
int uniq_gen_fast_alt(int number[], int length, int limit);
int uniq_gen_fast(int number[], int length, int limit);
int uniq_gen_fast_symbols(char string[], int length);
int bits_counter(int value);
void bulls_and_cows();
void hack_the_terminal(int length, int quantity, int attempts);
#endif      // global.h
