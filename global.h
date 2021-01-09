#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
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
int factorial(int n);
int multiply(int x, int y);
int numerical_generation_int();

void chapter_5();

// Функции и константы для шестой главы задачника.

#define ARRAY_SIZE 15

int evklid_first_step(int a, int b);
void number_of_degrees (int n);
void fibonachi (int n);
int arif_sequence (int n, int f, int s);
int geom_seqence (int m, int g, int z);
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

void chapter_9();

// Функции и константы для десятой главы задачника.

void chapter_10();

#endif      // global.h
