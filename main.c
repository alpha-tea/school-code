#include "global.h"
#include "library.h"

#define STACK_MAX 64

/*

static unsigned char stack[STACK_MAX];
static int sp;
enum stack_type {stack_nop, stack_byte, stack_word, stack_dword};
static const char* stack_type_name[] = {"no type", "byte", "word", "double word"};
static const int stack_type_size[] = {0, sizeof(char), sizeof(short), sizeof(int)};

struct stack_object {
    enum stack_type type; // необязательно
    int size;
};

void stack_init()
{
    sp = STACK_MAX;
    for (int i = 0; i < STACK_MAX; ++i)
        stack[i] = 0;
}

int stack_size()
{
    return  STACK_MAX - sp;
}

void stack_memory()
{
    printf("stack memory\n");
    printf("offset:\tdata:\n");
    for (int i = STACK_MAX - 1; i >= sp; --i)
        printf("%d\t%3d\n", i, stack[i]);
}

int stack_push(struct stack_object* info, void* data)
{
    if ((info->type < stack_nop || info->type > stack_dword) ||
            sp < (int)(info->size + sizeof(struct stack_object))) {
        printf("data type error or stack full;\n");
        return -1;
    }
    unsigned char* obj_ptr = (unsigned char*)(info);
    unsigned char* data_ptr = (unsigned char*)(data);
    printf("sp = %d, type = %s, size = %d;\n", sp, stack_type_name[info->type], info->size);
    sp -= info->size;
    for (int i = 0; i < info->size; ++i, ++sp, ++data_ptr) {
        stack[sp] = *data_ptr;
        printf("sp = %d, data = %d;\n", sp, *data_ptr);
    }
    sp -= sizeof(struct stack_object) + info->size;
    for (int i = 0; i < (int)(sizeof(struct stack_object)); ++i, ++sp, ++obj_ptr) {
        stack[sp] = *obj_ptr;
        printf("info = %d;\n", *obj_ptr);
    } // Можно через реинтепритацию типа.
    sp -= sizeof(struct stack_object);
    return 0;
}

int stack_pop(struct stack_object* info, void* data)
{
    if (sp == STACK_MAX) {
        printf("stack is empty;\n");
        return -1;
    }
    printf("%d", stack[sp]);
    struct stack_object *object_ptr = (struct stack_object*)(&stack[sp]);
    info->type = object_ptr->type;
    info->size = object_ptr->size;
    unsigned char* data_ptr = (unsigned char*)(data);
    sp += sizeof(struct stack_object);
    for (int i = 0; i < object_ptr->size; ++i, ++sp, ++data_ptr) {
        *data_ptr = stack[sp];
        printf("sp = %d, data = %d;\n", sp, *data_ptr);
    }
    return 0;
}

int main()
{
    printf("simple stack with data types(data size):\n");
    for (enum stack_type t = stack_nop; t <= stack_dword; ++t)
        printf("%s(%d);\n", stack_type_name[t], stack_type_size[t]);
    printf("size of structure 'stack object' and offsets: bytes total = %u;\n",
           sizeof (struct stack_object));
    struct stack_object data;
    printf("Type: offset = %lu, size = %u bytes;\n",
           (unsigned long)(&data.type) - (unsigned long)(&data), sizeof(data.type));
    printf("Size: offset = %lu, size = %u bytes;\n",
           (unsigned long)(&data.size) - (unsigned long)(&data), sizeof(data.size));
    stack_init();
    //sp -= 5;
    int result = 0;
    unsigned int value;
    unsigned int mask[] = {0, 0xFF, 0xFFFF, 0xFFFFFFFF};
    do {
        data.type = (rand() % 3) + 1;
        data.size = stack_type_size[data.type];
        value = rand() & mask[data.type];
        printf("value push = %u;\n", value);
        result = stack_push(&data, &value);
        stack_memory();
    } while (result != -1);
    result = 0;
    while (result != -1) {
        value = 0;
        result = stack_pop(&data, &value);
        printf("sp = %d, type = %d, size = %d, value = %u;\n", sp, data.type, data.size, value);
    }
    */


int main()
{
    /*
    FILE * file = fopen("17.txt","r");
    char string[256], c;
    int array[10000], length = 0, str_len = 0, max = 0, counter = 0;
    while ((c = fgetc(file)) != EOF) {
        if (c != '\n')
            string[str_len++] = c;
        else {
            string[str_len] = '\0';
            array[length++] = atoi(string);
            str_len = 0;
        }
    }
    for (int i = 0; i < length - 1; ++i) {
        if ((array[i] % 3 == 0 || array[i + 1] % 3 == 0)
                && ((array[i] + array[i + 1]) % 5 == 0)) {
            ++counter;
            if (array[i] + array[i + 1] > max)
                max = array[i] + array[i + 1];
        }
    }
    fclose(file);
    printf("%d %d", counter, max);
    */
    exam_26();
    return 0;
}

#define Y CHAR_MAX
#define Z CHAR_MIN
#define DIGIT 5
#define SEQUENCE_LENGTH 11
#define NUMBERS_QUANTITY 6








