#include "global.h"
#include "library.h"

int array_information(void* data, int type, int size, int ret)
{
    int size_elem = sizeof (data), size_array = size_elem * size;
    printf("Array Information:\n");
    printf("addr = %p;\nsize = %d;\nquantity = %d;\n", &data, size_array, size);
    if (size_elem == 1)
        printf("type = char(1 byte);\n");
    else
        printf("type = int(4 bytes);\n");
    int* i = data;
    int quantity = 0;
    switch (type) {
    case 0: {
        int positive = 0;
        for (;quantity < size; ++i, ++quantity)
            if (*i > 0)
                ++positive;
        type = positive;
        break;
    }
    case 1: {
        int negative = 0;
        for (;quantity < size; ++i, ++quantity)
            if (*i < 0)
                ++negative;
        type = negative;
        break;
    }
    case 2: {
        int null = 0;
        for (;quantity < size; ++i, ++quantity)
            if (*i == 0)
                ++null;
        type = null;
        break;
    }
    case 3: {
        int even = 0;
        for (;quantity < size; ++i, ++quantity) {
            printf("%d ",*i);
            if (*i % 2 == 0)
                ++even;
        }
        type = even;
        break;
    }
    case 4: {
        int odd = 0;
        for (;quantity < size; ++i, ++quantity)
            if (*i % 2 == 0)
                ++odd;
        type = odd;
        break;
    }
    case 5: {
        int sum = 0;
        for (;quantity < size; ++i, ++quantity)
            sum += *i;
        type = sum;
        break;
    }
    case 6: {
        int sum = 1;
        for (;quantity < size; ++i, ++quantity)
            sum *= *i;
        type = sum;
        break;
    }
    case 7: {
        int sum = 0;
        for (;quantity < size; ++i, ++quantity)
            sum += *i;
        type = sum / size;
        break;
    }
    case 8: {
        int sum = 1;
        for (;quantity < size; ++i, ++quantity)
            sum *= *i;
        type = sqrt(sum);
        break;
    }
    case 9: {
        int prime = 0;
        for (;quantity < size; ++i, ++quantity)
            if (prime_number(*i) == 1)
                ++prime;
        type = prime;
        break;
    }
    case 10: {
        int sum = 0, b = 1;
        for (;quantity < size; ++i, ++quantity, b *= -1)
            sum += pow(*i,-1);
        type = sum;
        break;
    }
    case 11: {
        int sum = 1;
        for (;quantity < size; ++i, ++quantity)
            sum *= *i;
        type = sum;
        break;
    }
    }
    if (ret == 1)
        printf("result = %d\n",type);
    return type;
}

int array_modify_elements(int data[], int type, int parameter, int limit)
{
    if (limit < 0)
        return -1;
    int i = 0;
    if (type == 0)
        for (i = 0; i < limit; ++i)
            data[i] -= parameter;
    if (type == 1)
        for (i = 0; i < limit; ++i)
            data[i] += parameter;
    if (type == 2)
        for (i = 0; i < limit; ++i)
            data[i] *= parameter;
    if (type == 3)
        for (i = 0; i < limit; ++i)
            data[i] /= parameter;
    return i;
}

int array_check_element(int data[], int offset, int parameter, int type, int limit)
{
    if (offset > limit || limit < 0)
        return -1;
    if (type == 0 && data[offset] == parameter)
        return 1;
    if (type == 1 && data[offset] > -1)
        return 1;
    if (type == 2 && data[offset] % 2 == 0)
        return 1;
    if (type == 3 && data[offset] >= parameter)
        return 1;
    if (type == 4 && data[offset] * data[offset] == parameter)
        return 1;
    return 0;
}

void array_print(int data[], int limit)
{
    for (int i = 0; i < limit; ++i)
        printf("%d ", data[i]);
}

int array_create_input(int data[], int init[], int isInput, int limit)
{
    int i = 0;
    if (limit <= 0) {
        printf("empty array, error;");
        return -1;
    }
    switch (isInput) {
    case 0:
        for (i = 0; i < limit; ++i)
            data[i] = init[i];
        break;
    default:
        for (i = 0; i < limit; ++i)
            scanf("%d",&data[i]);
        break;
    }
    return i;
}

int is_Fibonacci(int n)
{   //Является ли число элементом последовательности Фибоначчи. Числа Фибоначчи могут быть отрицательными. Знакопеременная последовательность.
    int f1 = 1, f2 = 1, f3 = 0;
    while ((f3 = f1 + 2) < n) {
        f1 = f2;
        f2 = f3;
    }
    if (f3 == n || (n >= 0 && n <= 1))
        return 1;
    else
        return 0;
}

int array_create_sequence(int data[], int first, int last, int par, int flags, int limit)
{//Инициализация массива данных последовательности, заданный по правилам, и с учётом элементов.
    if (limit <= 0) {
        printf("error, empty array;\n");
        return -1;
    }
    int elements = 0;
    switch (flags) {
    case 0b00000001://Random values.
        if (par > 0)
            for (int i = 0; i <= limit; ++i)
                data[i] = rand() % par;
        else
            printf("error generate random;\n");
        break;
    case 0b00000010: {//arif_progres.
        int i = 0;
        for (i = 0; elements < limit && first != last; ++i, first += par, elements++)
            data[i] = first;
        if (first == last)
            data[i] = last;
        else
            printf("warning: sequence doesn't reach last element.\n");
    } break;
    case 0b00000100: { //geomet_progres.
        int i = 0;
        for (i = 0; elements <= limit && first != last; ++i, first *= par, elements++)
            data[i] = first;
        if (first == last)
            data[i] = last;
        else
            printf("warning: sequence doesn't reach last element.\n");
      }  break;
    case 0b00001000: {// fibonachi, проверить на полный крадрат по совету Андрея.
        if (is_Fibonacci(first)) {
            if (!is_Fibonacci(last))
                printf("warning: last element is not fibonacci;\n");
            for (int i = 0, f1 = 0, f2 = 1, f3 = 1; elements < limit && f3 != last; ++i) {
                f3 = f1 + f2;
                if (f3 >= first)
                    data[elements++] = f3;
                f1 = f2;
                f2 = f3;
            }
        } else
            printf("error: first element is not fibonacci;\n");
    }   break;
    case 0b00010000: {// Все числа уникальные.
        if (abs(last) - abs(first) <= par && par > 0) {
            for (int i = 0; i < par && i < limit; ++i, first++, elements++)
                data[i] = first;
            int tmp = 0, idx_1 = 0 , idx_2 = 0;
            for (int i = 0; i < limit * limit; ++i) {
                idx_1 = rand() % par;
                idx_2 = rand() % par;
                tmp = data[idx_1];
                data[idx_1] = data[idx_2];
                data[idx_2] = tmp;
            }
        } else
            printf("error: elements more than delta from first to last;\n");
    } break;
    default:
        printf("error in flags!;\n\n");
        break;
    };
    return 0;
}

void chapter_11()
{
    printf("11.1 - 11.2, moving data across arrays;\n");
    int i = 0;
    int length = 10, random_max = 10;
    int data[OBJECTS_MAX];
    int init[OBJECTS_MAX];
    srand(time(NULL));
    for (i = 0; i < length; ++i)
        init[i] = rand() % random_max;
    printf("source elements: ");
    array_print(init,length);
    array_create_input(data, init, 0, length);
    printf("output: ");
    for (i = 0; i < length; ++i)
        printf("%d ",data[i]);
    printf(";\n\n");
    printf("11.3 - 11.9, filling the array elements with integer elements of sequence, length = %d\n", length);
    printf("random sequence with random_max = %d: ", random_max);
    int first = 0, last = 9, par = random_max, flags = 0b00000001;   //warning: binary integer literals are a GNU extension
    array_create_sequence(data, first, last, par,flags, length);
    array_print(data,length);
    first = 3, last = 15, par = 3, flags = 0b00000010;
    printf("\narif. sequence from %d to %d, step = %d: ", first, last, par);
    array_create_sequence(data, first, last, par,flags, length);
    array_print(data,length);
    first = 2, last = 32, par = 2, flags = 0b0000100;
    printf("\ngeometr. sequence from %d to %d, step = %d: ", first, last, par);
    array_create_sequence(data, first, last, par,flags, length);
    array_print(data,length);
    first = 21, last = 89, par = 5, flags = 0b0001000;
    printf("\nFibonacci sequence from %d to %d: ", first, last);
    array_create_sequence(data, first, last, par,flags, length);
    array_print(data,length);
    first = 0, last = 9, par = 10, flags = 0b0010000;
    printf("\nunique sequence with parameter = %d: ", par);
    array_create_sequence(data, first, last, par,flags, length);
    array_print(data,length);
    return;
    printf("\n11.12, filling an array with prime and natural numbers;\n");
    int quantity = 0;
    printf("A(natural, divisible by 13 or 17 and more than 299):\n");
    for (i = 300; quantity < 20; ++i) {
        if (i % 13 == 0 || i % 17 == 0) {
            data[quantity] = i;
            ++quantity;
        }
    }
    array_print(data,quantity);
    printf("\nB(first 30 primes numbers):\n");
    for (i = 2, quantity = 0; quantity < 30; ++i) {
        if (prime_number(i) == 1) {
            data[quantity] = i;
            ++quantity;
        }
    }
    array_print(data,quantity);
    printf("\n\n11.13 - 11.14, outputting array values;\n");
    for (i = 0; i < length; ++i)
        data[i] = rand() % OBJECTS_MAX;
    printf("output: ");
    array_print(data,length);
    int parameter = 0, type = 3;
    printf("\n\n11.15 - 11.16, checking an element in an array,parameter = %d, type = %d;\n", parameter, type);
    data[0] = 5;
    int result = array_check_element(data,0,0,3,OBJECTS_MAX);
    printf("element = %d, result = %d;\n\n", data[0], result);
    parameter = 5, type = 1;
    printf("11.17 - 11.18, changing all elements of the array to a parameter = %d, type = %d;\n", parameter, type);
    quantity = 10;
    printf("source values: ");
    for (i = 0; i < quantity; ++i) {
        data[i] = rand() % OBJECTS_MAX;
        printf("%d ", data[i]);
    }
    printf("\nresult values: ");
    array_modify_elements(data,type,parameter,quantity);
    array_print(data,quantity);
    printf("\n\n");
    printf("11.19, output of array characteristics;\n");
    quantity = 10;
    printf("source values: ");
    for (i = 0; i < quantity; ++i) {
        data[i] = rand() % OBJECTS_MAX;
        printf("%d ", data[i]);
    }
    printf("\n");
    type = 9;
    array_information(&data,type,quantity,1);
}

