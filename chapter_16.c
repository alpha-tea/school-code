﻿//#include "library.h"

//Это дополнительные задания на классические структуры данных, какие то главы по теории
// и теоритический материал к экзамену.
//Раскидать попозже.

/*
#define STACK_MAX 64


void rotate_test();
int bits_counter(int value);

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

/*
#define QUEUE_MAX 256

unsigned char queue[QUEUE_MAX];
int queue_size;

struct queue_object {
    short code;	// Случайный код.
    char name;	// И его обозначение буквой.
};

void queue_init()
{
    printf("Initialization of queue, size = 0 and clear all data;\n");
    for (int i = 0; i < QUEUE_MAX; ++i)
        queue[i] = 0;
    queue_size = 0;
}

void queue_print(int field, int is_all)
{
    printf("Print queue, size = %d;\n", queue_size);
    printf("idx:\tdh:\tdl:\tcode:\tname:\n");
    const int size = sizeof(struct queue_object), base = 10;
    for (int i = 0; i < size * queue_size || (is_all && i < QUEUE_MAX); i += size) {
        struct queue_object obj;
        int dh = queue[i + sizeof(char)];
        int dl = queue[i];
        printf("%d\t%d\t%d\t", i, dh, dl);
        obj.code = (dh << CHAR_BIT) + dl;
        obj.name = queue[i + sizeof(short)];
        char code[QUEUE_MAX];
        code[field] = '\0';
        for (int j = field - 1; j >= 0; --j) { // Or use while() or obj.code > 0;
            code[j] = '0' + obj.code % base;
            obj.code /= base;
        }
        printf("%s\t%c\n", code, obj.name);
    }
}

int queue_first(struct queue_object* object)
{
    if (!queue_size) {
        printf("Queue is empty;\nerror reading first element;\n");
        return -1;
    }
    object->code = queue[0] + (queue[sizeof(char)] << CHAR_BIT);
    object->name = queue[sizeof(short)];
    printf("First element is %d code, name = '%c';\n", object->code, object->name);
    return 0;
}

int queue_last(struct queue_object* object)
{
    if (!queue_size) {
        printf("Queue is empty;\nerror reading last element;\n");
        return -1;
    }
    int last = (queue_size - 1) * sizeof(struct queue_object);
    object->code = queue[last] + (queue[last + sizeof(char)] << CHAR_BIT);
    object->name = queue[last + sizeof(short)];
    printf("Last element is %d code, name = '%c';\n", object->code, object->name);
    return 0;
}

int queue_push(struct queue_object* object)
{
    if (queue_size == QUEUE_MAX / sizeof(struct queue_object)) {
        printf("can't push new element, queue is full, size = %d;\n", queue_size);
        return -1;
    }
    const int size = sizeof(struct queue_object);
    for (int i = (queue_size + 1) * size; i >= size; --i)
        queue[i] = queue[i - size];
    unsigned char dh = object->code >> CHAR_BIT, dl = object->code & UCHAR_MAX;
    queue[0] = dl;
    queue[sizeof(char)] = dh;
    queue[sizeof(short)] = object->name;
    ++queue_size;
    printf("Push new element to start queue, code = %d(dh = %d, dl = %d), "
                "name = '%c', and new size is %d;\n", object->code, dh, dl, object->name, queue_size);
    return 0;
}

int queue_pop(struct queue_object* object)
{
    if (!queue_size) {
        printf("queue is empty, nothing to pop;\n");
        return -1;
    }
    int last = --queue_size * sizeof(struct queue_object);
    object->code = queue[last] + (queue[last + sizeof(char)] << CHAR_BIT);
    object->name = queue[last + sizeof(short)];
    printf("Pop last element from queue, code = %d, name = '%c' and new size = %d;\n",
           object->code, object->name, queue_size);
    return 0;
}

int queue_reverse(void) {
    if (queue_size < 2) {
        printf("Queue has less than 2 elements, size = %d;\n", queue_size);
        return -1;
    }
    printf("Reverse elements in queue;\n");
    struct queue_object obj;
    const int size = sizeof(struct queue_object);
    for (int i = 0; i < queue_size / 2; ++i) {
        int idx_a = i * size;
        int idx_b = (queue_size - i - 1) * size;
        obj.code = queue[idx_a] + (queue[idx_a + sizeof(char)] << CHAR_BIT);
        obj.name = queue[idx_a + sizeof(short)];
        printf("Left element, code = %d, name = '%c' at index = %d;\n", obj.code, obj.name, idx_a);
        obj.code = queue[idx_b] + (queue[idx_b + sizeof(char)] << CHAR_BIT);
        obj.name = queue[idx_b + sizeof(short)];
        printf("Right element, code = %d, name = '%c' at index = %d;\n", obj.code, obj.name, idx_b);
        for (int j = 0; j < size; ++j)
            queue[idx_b + j] = queue[idx_a + j];
        queue[idx_a] = obj.code & UCHAR_MAX;
        queue[idx_a + sizeof(char)] = obj.code >> CHAR_BIT;
        queue[idx_a + sizeof(short)] = obj.name;
    }
    return 0;
}

int main()
{
    printf("Simple queue with struct;\n");
    const int debug_elements = 5;
    queue_init();
    struct queue_object obj;
    printf("Size of structure = %u, size of char = %u, size of short = %u,"
            "bits in char = %u, uchar max = %u", sizeof(struct queue_object), sizeof(char), sizeof(short),
           CHAR_BIT, UCHAR_MAX);
    printf("\nname:\toffset:\t\tsize:\n");
    printf("code:\t%p\t%u\n", NULL, sizeof(obj.code));
    printf("name:\t%p\t%u\n", (void*)((void*)&obj.name - (void*)&obj), sizeof(obj.name));
    for (int i = 0; i < debug_elements; ++i) {
        obj.code = rand() % SHRT_MAX;
        obj.name = 'A' + rand() % 26;
        printf("\nadding element to queue, code = %d, name = '%c';\n", obj.code, obj.name);
        queue_push(&obj);
        queue_print(5, 0);
    }
    printf("\n");
    queue_first(&obj);
    printf("\n");
    queue_last(&obj);
    printf("\n");
    for (int i = 0; i < debug_elements - 4; ++i) {
        printf("Pop %d element from queue tail;\n", i);
        queue_pop(&obj);
    }
    queue_print(5, 0);
    printf("\n");
    queue_reverse();
    queue_print(5, 0);
    return 0;
}
 */
int chars_counter(char s[],  char c)
{
    int index = 0, counter = 0;
    while (s[index] != '\0'){   //Частота определённой буквы.
        if (s[index] == c)
            counter++;
        index++;
    }
    return counter;
}

int length(char s[])
{
    int len = 0;                //Длинна строки.
    while (s[len] != '\0') {
        ++len;
    }
    return len;
}
/*
void invert(char s[])
{
    int len = length(s);
    while (--len >= 0)
        printf("%c",s[len]); //Инвертирование имени.
}

int bits_counter(int value)
{
    int counter = 0;
    value--;
    while (value > 0) {
        value /= 2;
        counter++;
    }
    return counter;
}

void demo()
{
    unsigned char font[5][8];
    //unsigned char font_1[3][16 * 2]; не используетсяё
    char video_buffer[2][2], scr_buffer[2 * 2 * 8 * 8];
    for (int i = 0; i < 4; ++i)
        for (int g = 0; g < 4; ++g) {
            font[i][g * 2] = 0xAA;
            font[i][g * 2 + 1] = 0x55;
        }
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            video_buffer[i][j] = 0;
    video_buffer[0][0] = 1;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) {
            char code = video_buffer[i][j];
            for (int k = 0; k < CHAR_BIT; ++k)
                for (int l = CHAR_BIT - 1; l >= 0; --l) {
                    char draw;
                    if ((font[(int)code][k] & (0x01 << l)) != 0)
                        draw = 'O';
                    else
                        draw = '.';
                    scr_buffer[i * 128 + j * 8 + k * 16 + (CHAR_BIT - 1 - l)] = draw;
                }
        }
    for (int i = 0; i < 16; ++i) {
        printf("%d: ",i);
        for (int j = 0; j < 16; ++j)
            printf("%c ", scr_buffer[i * 16 + j]);
        printf("\n");
    }
}

void rotate_test()
{
    int data[] = {0,1,2,3,4};
    printf("Rotate function test, 5 right and 5 left:\n");
    printf(" Right:\n");
    for (int i = 0; i < 5; ++i) {
        array_rotate_range(data,5,0,5,1);
        for (int j = 0; j < 5; ++j)
            printf("%d ",data[j]);
        printf("\n");
    }
    printf(" Left:\n");
    for (int i = 0; i < 5; ++i) {
        array_rotate_range(data,5,0,5,0);
        for (int j = 0; j < 5; ++j)
            printf("%d ",data[j]);
        printf("\n");
    }
}

void lesson_test_1()
{
    //int i1 = 1;
    //printf("i = ++i + ++i = %d\n",++i1 + ++i1);   //DANGER CODE!!!!!
    unsigned char x = ' ';
    const unsigned char end_x = 129;
    printf("Code    16-x system     symbol\n\n");
    while (x < end_x)
    {
        int k = 0;
        while (k < 3) {
            printf("%3d",x);
            printf("%#11x",x);
            printf("%13c\t",x);
            ++x;
            ++k;
        }
        printf("\n");
    }
    // Номер 3.
    char i = 1;
    unsigned char i2 = 1, bits = 0;
    while (i > 0) {
        bits++;
        i *= 2;
    }
    printf("bits in char = %d,bytes = %d\n",bits,bits / 8);
    bits = 0;
    while (i2 > 0) {
        bits++;
        i2 *= 2;
    }
    int Z = 0, Y = 0;
    printf("bits in unsigned char = %d, bytes = %d\n",bits,bits / 8);
    printf("\nNumber 3.\nChar = %d\n%d..%d\n",sizeof i,Z,Y);
    printf("Unsigned char = 0..%d\n",UCHAR_MAX);
    // Номер 4.
    double c = 1, f = 0, k = 0;
    const double m = 32;
    const double n = 1.8;
    const double l = 273.15;
    printf("\nNumber 4.\nCelsius\t   Fahrenheit\tKelvin\n\n");
    while (c < 55) {
        k = c + l;
        f = c * n + m;
        printf("%5.1f\t%10.1f\t%6e\n",c,f,k);
        c += 5.5;
    }
    //Номер 5.
    const double  dollars = 1 / 73.61;
    const double  euro = 1 / 79.63;
    double Dollar = 0, Euro = 0;
    int Ruble = 0, a1 = 1, help = 0;
    char name[15];
    printf("\nNumber 5\nPlease, enter your name!: ");
    scanf("%s", name);
    printf("Hello, %s!\n",name);
    printf("Your name consists of %d letters\n",length(name));
    printf("And also the name takes %d bytes in memory\n",sizeof (name));
    //size_t v1;
    //printf("%d",sizeof char );
    printf("Your inverted name:");
    invert(name);
    printf("\n");
    help = chars_counter(name,'a');
    printf("Quantity a in your name = %d\n",help);
    printf("Ok,now indicate your salary month in Ruble: ");
    scanf("%d", &Ruble);
    printf("\nHere is painted all your salary for the year in different currencies\n");
    printf("\nMounth\tRuble\tDollars\t Euro\n");
    help = Ruble;
    while (a1 < 13) {
        Dollar = Ruble * dollars;
        Euro = Ruble * euro;
        printf("%d\t%4d\t%4.f\t%4.f\n",a1,Ruble,Dollar,Euro);
        Ruble += help;
        a1++;
    }
    int per = 0;
    int per2 = 1, per3;
    per3 = (per || per2);
    printf("%d",per3);
    getchar();
}

void additional()
{
    char* v_mode_name[2] = {"txt", "gfx"};
    printf("Video modes is history\n");
    printf("1 - mode type;\n2 - screen resolution;\n3 - aspect ratio;\n"
    "4 - the dimension of the character in points;\n5 - number of unique colors per point;\n"
    "6 - effective or real screen resolution;\n7 - conventionally displayed screen resolution;\n"
    "8 - bit per color;\n9 - dots per byte;\n10 - byte per point;\n"
    "11 - video buffer size/font/palette size;");
    enum mode_type {text, gfx};
    int scr_y = 0, scr_x = 0, aspect_x = 0, aspect_y = 0, font_x = 0, font_y = 0;
    int colors = 0, effective_x = 0, effective_y = 0, displ_x = 0, displ_y = 0;
    int bit_per_color = 0, point_per_byte = 0, byte_per_point = 0;
    int buffer_size = 0, font_size = 0, palette_size = 0;
    unsigned short alphabet_size = 0;
    printf("\n");
    for (int i = 0; i < 11; ++i)
        printf("%d:\t", i + 1);
    printf("\n");
    // 0
    scr_x = 40; scr_y = 25;
    font_x = 8; font_y = 8;
    aspect_x = 1; aspect_y = 1;
    colors = 1;
    effective_x = scr_x * font_x; effective_y = scr_y * font_y;
    font_size = 256 * (font_x * font_y) / CHAR_BIT;
    buffer_size = (scr_x * scr_y) * 2;
    printf("%s\t%d:%d\t%d:%d\t%d:%d\t%d\t%d:%d\t%d:%d\t%d\t%d\t%d\t%d:%d:%d\n",
           v_mode_name[text], scr_x, scr_y, aspect_x, aspect_y, font_x, font_y, colors, effective_x, effective_y,
           effective_x, effective_y, 1, 0, 0, buffer_size, font_size, 0);
    // 1
    scr_x = 160; scr_y = 100;
    font_x = 0; font_y = 0;
    aspect_x = 4; aspect_y = 3;
    colors = 16;
    effective_x = scr_x; effective_y = scr_y;
    font_size = 0;
    bit_per_color = bits_counter(colors);
    point_per_byte = CHAR_BIT / bit_per_color; byte_per_point = bit_per_color / CHAR_BIT;
    if (byte_per_point > 0)
        buffer_size = (scr_x * scr_y) * byte_per_point;
    else
        buffer_size = (scr_x * scr_y) / point_per_byte;
    displ_x = scr_x; displ_y = scr_x / aspect_x * aspect_y;
    printf("%s\t%d:%d\t%d:%d\t%d:%d\t%d\t%d:%d\t%d:%d\t%d\t%d\t%d\t%d:%d:%d\n",
           v_mode_name[gfx], scr_x, scr_y, aspect_x, aspect_y, font_x, font_y, colors, effective_x, effective_y,
           displ_x, displ_y, bit_per_color, point_per_byte,
           byte_per_point, buffer_size, font_size, colors);
    // 2
    scr_x = 80; scr_y = 25;
    font_x = 9; font_y = 8;
    aspect_x = 1; aspect_y = 2;
    colors = 16;
    effective_x = scr_x * font_x; effective_y = scr_y * font_y * aspect_y;
    font_size = (font_x * font_y) / CHAR_BIT;
    buffer_size = (scr_x * scr_y) * (bits_counter(colors) + 1);
    printf("%s\t%d:%d\t%d:%d\t%d:%d\t%d\t%d:%d\t%d:%d\t%d\t%d\t%d\t%d:%d:%d\n",
           v_mode_name[text], scr_x, scr_y, aspect_x, aspect_y, font_x, font_y, colors, effective_x, effective_y,
           effective_x, effective_y, 1, 0, 0, buffer_size, font_size, 0);
    // 11
    scr_x = 32; scr_y = 24;
    font_x = 64; font_y = 64;
    aspect_x = 1; aspect_y = 1;
    colors = 1;
    effective_x = scr_x * font_x; effective_y = scr_y * font_y;
    font_size = 16 * (font_x * font_y) / CHAR_BIT;
    buffer_size = (scr_x * scr_y) / 2;
    printf("%s\t%d:%d\t%d:%d\t%d:%d\t%d\t%d:%d\t%d:%d\t%d\t%d\t%d\t%d:%d:%d\n",
           v_mode_name[text], scr_x, scr_y, aspect_x, aspect_y, font_x, font_y, colors, effective_x, effective_y,
           effective_x, effective_y, 1, 0, 0, buffer_size, font_size, 0);
    //
    font_x = 0; font_y = 0;
    aspect_x = 4; aspect_y = 3;
    colors = 2;
    font_size = 0;
    bit_per_color = bits_counter(colors);
    point_per_byte = CHAR_BIT / bit_per_color; byte_per_point = bit_per_color / CHAR_BIT;
    buffer_size = 8 * 1024;
    int points = buffer_size * point_per_byte;
    scr_x = sqrt(points); scr_y = scr_x;
    effective_x = scr_x; effective_y = scr_y;
    displ_x = effective_x; displ_y = effective_y;
    printf("%s\t%d:%d\t%d:%d\t%d:%d\t%d\t%d:%d\t%d:%d\t%d\t%d\t%d\t%d:%d:%d\n",
           v_mode_name[gfx], scr_x, scr_y, aspect_x, aspect_y, font_x, font_y, colors, effective_x, effective_y,
           displ_x, displ_y, bit_per_color, point_per_byte,
           byte_per_point, buffer_size, font_size, colors);
    // 13
    aspect_x = 1; aspect_y = 1;
    colors = 4;
    font_size = 1024;
    buffer_size = 256;
    scr_x = sqrt(buffer_size); scr_y = scr_x;
    font_x = sqrt(font_size / 32 * CHAR_BIT); font_y = font_x;
    effective_x = scr_x * font_x; effective_y = scr_y * font_y;
    printf("%s\t%d:%d\t%d:%d\t%d:%d\t%d\t%d:%d\t%d:%d\t%d\t%d\t%d\t%d:%d:%d\n",
           v_mode_name[text], scr_x, scr_y, aspect_x, aspect_y, font_x, font_y, colors, effective_x, effective_y,
           effective_x, effective_y, 1, 0, 0, buffer_size, font_size, 0);
    // CA - 1101 1010
    // C0F1 - 1101 0000 1111 0001
    // E85F - 1110 1000 0101 1111
    // 1EBA73 - 0001 1110 1011 1010 0111 0011
    // 713(8) - 3 * 8 ^ 0 + 1 * 8 ^ 1 + 7 * 8 ^ 2 = 3 + 8 + 448 = 459;
    // 713(8) - 111 001 011;
    // 1011 1110 0100 0010 = BE42
    // 314(7) -> 4 * 7 ^ 0 + 1 * 7 ^ 1 + 3 * 7 ^ 2 = 4 + 7 + 147 = 158;
    // 158 -> 14 + 9 * 16 -> 9E
    // 215(6) -> 0,1,2,3 -> 010 001 101
    //
    aspect_x = 2; aspect_y = 1;
    colors = 2;
    font_size = 0;
    bit_per_color = bits_counter(colors);
    point_per_byte = CHAR_BIT / bit_per_color; byte_per_point = bit_per_color / CHAR_BIT;
    buffer_size = 16 * 1024;
    scr_x = 256; scr_y = scr_x / aspect_x * aspect_y;
    effective_x = scr_x; effective_y = scr_y;
    displ_x = effective_x; displ_y = effective_y;
    points = scr_x * scr_y;
    bit_per_color = (buffer_size * CHAR_BIT) / points;
    colors = 1 << bit_per_color;
    font_x = 0; font_y = 0;
    printf("%s\t%d:%d\t%d:%d\t%d:%d\t%d\t%d:%d\t%d:%d\t%d\t%d\t%d\t%d:%d:%d\n",
           v_mode_name[gfx], scr_x, scr_y, aspect_x, aspect_y, font_x, font_y, colors, effective_x, effective_y,
           displ_x, displ_y, bit_per_color, point_per_byte,
           byte_per_point, buffer_size, font_size, colors);
    // 7
    scr_x = 256; scr_y = 192;
    font_x = 32; font_y = 24;
    aspect_x = 4; aspect_y = 3;
    colors = 2;
    font_size = 0;
    bit_per_color = bits_counter(colors);
    point_per_byte = CHAR_BIT / bit_per_color; byte_per_point = bit_per_color / CHAR_BIT;
    buffer_size = (scr_x * scr_y) / point_per_byte + font_x * font_y * 1;
    effective_x = scr_x; effective_y = scr_y;
    displ_x = effective_x; displ_y = effective_y;
    printf("%s\t%d:%d\t%d:%d\t%d:%d\t%d\t%d:%d\t%d:%d\t%d\t%d\t%d\t%d:%d:%d\n",
           v_mode_name[gfx], scr_x, scr_y, aspect_x, aspect_y, font_x, font_y, colors, effective_x, effective_y,
           displ_x, displ_y, bit_per_color, point_per_byte,
           byte_per_point, buffer_size, font_size, colors);
    // 15
    alphabet_size = 1024;
    aspect_x = 1; aspect_y = 1;
    colors = 16;
    font_size = 1024 * 8;
    font_x = sqrt(font_size / alphabet_size * CHAR_BIT); font_y = font_x;
    scr_x = 64; scr_y = 64;
    effective_x = scr_x * font_x; effective_y = scr_y * font_y;
    buffer_size = (scr_x * scr_y) * 2 * 2;
    printf("%s\t%d:%d\t%d:%d\t%d:%d\t%d\t%d:%d\t%d:%d\t%d\t%d\t%d\t%d:%d:%d\n",
           v_mode_name[text], scr_x, scr_y, aspect_x, aspect_y, font_x, font_y, colors, effective_x, effective_y,
           effective_x, effective_y, 1, 0, 0, buffer_size, font_size, 0);
    // 8
    scr_x = 640; scr_y = 480;
    font_x = 0; font_y = 0;
    aspect_x = 4; aspect_y = 3;
    colors = 16;
    effective_x = scr_x; effective_y = scr_y;
    font_size = 0;
    bit_per_color = bits_counter(colors);
    point_per_byte = CHAR_BIT / bit_per_color; byte_per_point = bit_per_color / CHAR_BIT;
    palette_size = colors * 6 * 3;
    if (byte_per_point > 0)
        buffer_size = (scr_x * scr_y) * byte_per_point * 2;
    else
        buffer_size = (scr_x * scr_y) / point_per_byte * 2;
    displ_x = scr_x; displ_y = scr_x / aspect_x * aspect_y;
    printf("%s\t%d:%d\t%d:%d\t%d:%d\t%d\t%d:%d\t%d:%d\t%d\t%d\t%d\t%d:%d:%d\n",
           v_mode_name[gfx], scr_x, scr_y, aspect_x, aspect_y, font_x, font_y, colors, effective_x, effective_y,
           displ_x, displ_y, bit_per_color, point_per_byte,
           byte_per_point, buffer_size, font_size, palette_size);
     red    - 0   00  110
     * blue   - 1   01  101
     * green  - 2   10  100
     * yellow - 3   11  0
     * bgry -
     * ygyy - 8 - 6
     * Реализовать простейшее сжатие.

}
*/
