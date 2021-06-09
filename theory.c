//Разбираем теорию С.Прато.
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
}
