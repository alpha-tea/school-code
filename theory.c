//Разбираем теорию С.Прато.
#include <stdio.h>
#define DATA_SIZE 3
void theory_10_1(int data[], int n)
{
    printf("function 10_1, data address = %p, elements(n) = %d: ", data, n);
    for (int i = 0; i < n; ++i)
        printf("%d ",data[i]);
    printf("\n");
}

void theory_10_2(int* first, int* last)
{
    printf("function 10_2, first = %p, last = %p: ", first, last);
    while (first <= last) {         //or using >= ,  <=
        printf("%d ", *first);
        ++first;
    }
    printf("\n");
}

void print_array_addr(void* data, const int n, int element_size)  // Потом использовать часть этой функции для вывода в print_array.
{
    printf("Array with %d elements and memory size is %u.\n", n, element_size * n);
    if (element_size < 1 || element_size > 4 || n < 1 || data == NULL) {
        printf("error, element size or other parameters isn't correct!\n");
        return;
    }
    printf("addr:\t\tdata:\n");
    for (int i = 0; i < n; ++i) {
        printf("%p\t", data);
        switch (element_size) {
         case sizeof (char):
            printf("char: %d, hex(char): ", *((char*)data));
            break;
         case sizeof (short):
            printf("short: %hd, hex(char): ", *((short*)data));
            break;
        case sizeof (int):
            printf("int: %d, hex(char): ", *((int*)data));
            break;
        default:
            printf("unknown size;\n");
        }
        for (int j = 0; j < element_size; ++j)
            printf("%x(%c) ", *((char*)data + j), *((char*)data + j));
        data = (void*)((char*)data + element_size);
        printf("\n");
    }
}

void theory_10(void)
{
    printf("Array and addreses:\nTheory part 10;\n");
    //const int data_size = 3;
    //int data[data_size];
    int var_array[sizeof (short) * 5];
    int data[DATA_SIZE] = {1, 2, 3};
    printf("data array of integers, elements = %d, size in memory = %u;\n", DATA_SIZE, sizeof (data));
    const char* colors[] = {"red", "yellow", "green"};
    //colors[0][1] = 'a'; - error
    short short_arr[] = {1, [2] = 5};
    printf("Partly defined array: ");
    for (int i = 0; i < DATA_SIZE; ++i)
        printf("%hd ", short_arr[i]);
    //data[-1] = 5; - very dangerous code
    //printf("\nprint -1 element of data array value is %d;\n", data[-1]);
    int matrix[][DATA_SIZE] = {{1,2,3},{4,5,6}};
    printf("\narray with sizes: [2][3], size in memory = %d, bytes;\n", sizeof (matrix));
    printf("Element and addreses of array %p;\n",(void*)(matrix));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < DATA_SIZE; ++j)
            printf("%d[%p]\t", matrix[i][j], (void*)(&matrix[i][j]));
        printf("\n");
    }
    int offset = (int)(&data[1] - data);
    printf("Offset as dif between addreses of integer, %d\n", offset);
    offset = (int)((char*)&data[1] - (char*)data);
    printf("Offset as dif between addreses of char - bytes, %d\n", offset);
    offset = (int)((void*)(&short_arr[2]) - (void*)short_arr);
    printf("Offset as dif between addreses of words, %d\n", offset);
    char kub[2][2][2] = { {{'a','b'},{'c','d'}} , {{'e','f'},{'g','h'}} };
    printf("size of kub = %d, bytes, side = [2], addr = %p;\n", sizeof (kub), (void*)kub);
    char* addr_char = (char*)(kub);
    printf("using addreses of kub of chars(2,2,2), from a to h, start at %p;\n", (void*)addr_char);
    addr_char = addr_char + 2 * 1 + 1;
    printf("char at [0][1][1] as address and value: %c[%p];\n", *addr_char, (void*)addr_char);
    addr_char++;
    printf("char at [1][0][0] as address and value: %c[%p];\n", *addr_char, (void*)addr_char);
    addr_char = addr_char - 2 * 2 + 2;
    printf("char at [0][1][0] as address and value: %c[%p];\n", *addr_char, (void*)addr_char);
    if (*(addr_char + 3) == 'e')
        printf("Yes! Char is %c;\n", *(addr_char + 3));
    else
        printf("No! Char is %c;\n", *(addr_char + 3));
    theory_10_1(data,DATA_SIZE);
    theory_10_2(&data[1],&data[2]);
    print_array_addr((void*)(short_arr), DATA_SIZE, sizeof (short));
    printf("\nassign addr of array to int*.\n");
    int* i_addr_1 = (int*)(short_arr);
    short_arr[1] = 3;
    print_array_addr((void*)(i_addr_1), DATA_SIZE - 2, sizeof (int));
    printf("\nassign addr of array to char*.\n");
    char* c_addr_1 = (char*)(short_arr);
    short_arr[1] = 540;
    print_array_addr((void*)(c_addr_1), DATA_SIZE * 2, sizeof (char));
    printf("\nValue at addr %p is %hd;\n", (void*)(short_arr + 1), *(short_arr + 1));
    short* addr = short_arr;
    short** addr_1 = &(addr);
    printf("addr of addr array %p, addr of array = %p, first element = %hd\n",
           addr_1, (void*)(*addr_1), *(*addr_1));
    printf("next and prev elements from first element.\n");
    addr = (short_arr + 1);
    printf("next elememt = %hd, prev element = %hd;\n", *(addr + 1), *(addr - 1));
    if (addr == &short_arr[1]) // *(short_arr + 1) - element
        printf("Yes, addr = %p, addr of first element = %p;\n", addr, short_arr);
    else
        printf("No, addr = %p, addr of first element = %p;\n", addr, short_arr);
    char c1 = 'a';
    char* a_c1_1 = &c1;
    char* a_c1_2 = &c1;
    printf("addr 1 = %p(%c), addr 2 = %p(%c);\n", a_c1_1, *a_c1_1, a_c1_2, *a_c1_2);
    printf("array with 3d[2,2,2] of char\n");
    print_array_addr((void*)kub, 8, sizeof (char));
    theory_10_1((int[3]){1,2,3},3);
}















