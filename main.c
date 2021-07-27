#include "global.h"
#include "library.h"

#define Y CHAR_MAX
#define Z CHAR_MIN
#define DIGIT 5
#define SEQUENCE_LENGTH 11
#define NUMBERS_QUANTITY 6

void theory_10(void);
/*
   # 4.120
print("Task 4.118")
# г) белая ладья и черный слон
# chessboard-1.jpg
print("Problem 1")
rook1   = [6, 4]
bishop1 = [2, 5]
point1  = [3, 4]

if point1[0] == bishop1[0] + 1 and point1[1] == bishop1[1] - 1:
    print("Point is unsafe")
else:
    print("Point is safe")
print()

# з) белый ферзь и черный слон
# chessboard-2.jpg
print("Problem 2")
queen2  = [3, 2]
bishop2 = [5, 6]
point2  = [3, 6]
bishop2_attack = [(1, 2), (2, 3), (3, 4), (4, 5), (6, 7), (7, 8), (3, 8), (4, 7), (6, 5), (7, 4), (8, 3)]

if point2 in bishop2_attack:
    print("Point is unsafe")
else:
    print("Point is safe")
print()

# 4.122-124
a, b, c = 9, 12, 15


if any((a <= b + c, b <= a + c, c <= a + b)):
    print("Triange can be done")
else:
    print("Triangle can't be done")


if any(((a * a) == (b * b) + (c * c), (b * b) == (a * a) + (c * c), (c * c) == (a * a) + (b * b))):
    print("Triangle is right-angle")
else:
    print("Triangle is not right-angle")

import math
angle_a = math.degrees(math.acos((math.pow(a, 2) + math.pow(c, 2) - math.pow(b, 2)) / (2 * a * c)))
angle_b = math.degrees(math.acos((math.pow(a, 2) + math.pow(b, 2) - math.pow(c, 2)) / (2 * a * b)))
angle_c = math.degrees(math.acos((math.pow(b, 2) + math.pow(c, 2) - math.pow(a, 2)) / (2 * c * b)))

if any((angle_a > 90, angle_b > 90, angle_c > 90)):
    print("Triangle is tupoi")

if any((angle_a == 90, angle_b == 90, angle_c == 90)):
    print("Triangle is right-angle")

if angle_a < 90 and angle_a < 90 and angle_a < 90:
    print("Triangle is ostriy")

if any((angle_a == angle_b, angle_b == angle_c, angle_a == angle_c)):
    print("Triangle is ravnobedrenniy")

if angle_a == angle_b == angle_c:
    print("Triangle is ravnostoronniy")

print(angle_a, angle_b, angle_c)
 */

/*
void chess( )    //Все позиции по умолчанию верны относительно доски и положительны.
{
    int a = 2, b = 2;   //Координаты первой фигуры. Х:У
    int c = 5, d = 6;   //Координаты второй фигуры.
    int e = 2, f = 6;   //Конечная координата первой фигуры.
    printf("Classic chess, positions of figures as vertical and horizontal;\n");
    printf("b) moving rook from %d:%d to %d:%d, threat from queen at %d:%d;\n", a, b, e, f, c, d);
    if (a == e || b == f) {
        printf("move rook is correct and ");
        if (c == e || d == f || (abs(e - c) == abs(f - d)))
            printf("under threat of queen.\n");
        else
            printf("it's safe from queen.\n");
    } else
        printf("move rook is incorrect;\n");
    a = 2; b = 2; c = 7; d = 7; e = 5; f = 5;
    printf("z) moving queen from %d:%d to %d:%d, threat from bishop at %d:%d;\n", a, b, e, f, c, d);
    if (a == e || b == f || (abs(a - e) == abs(b - f))) {
         printf("move queen is correct and ");
         if (abs(e - c) == abs(f - d))
             printf("under threat of bishop.\n");
         else
             printf("it's safe from bishop.\n");
    } else
        printf("move queen is incorrect;\n");
    a = 3; b = 3; c = 6; d = 7; e = 4; f = 5;
    printf("k) moving knight from %d:%d to %d:%d, threat from rook at %d:%d;\n", a, b, e, f, c, d);
    if ((abs(e - a) == 2 && abs(f - b) == 1) || (abs(e - a) == 1 && abs(f - b) == 2)) {
         printf("move knight is correct and ");
         if (c == e || d == f)
             printf("under threat of rook.\n");
         else
             printf("it's safe from rook.\n");
    } else
        printf("move knight is incorrect;\n");
    a = 3; b = 3; c = 5; d = 6; e = 5; f = 5;
    printf("u) moving king from %d:%d to %d:%d, threat from knight at %d:%d;\n", a, b, e, f, c, d);
    if (abs(e - a) <= 1 && abs(f - b) <= 1 && (a != e && b != f)) {
         printf("move king is correct and ");
         if ((abs(e - c) == 2 && abs(f - d) == 1) || (abs(e - c) == 1 && abs(f - d) == 2))
             printf("under threat of knight.\n");
         else
             printf("it's safe from knight.\n");
    } else
        printf("move king is incorrect;\n");
}
*/
void theory_bonus()
{
    static char a = 'a';
    static short b = 500;
    static int c = 128;
    a = b;
    printf("a = %d(%p), b = %c(%p), c = %c(%p);\n", a, &a, b, &b, c, &c);
    int a1 = -14, b2 = 17;
    printf("%d / 5 = %d, %d / 5 remain %d;\n", a1, a1 / 5, a1, a1 % 5);
    printf("%d / 5 = %d, %d / 5 remain %d;\n", b2, b2 / 5, b2, b2 % 5);
    printf("%.2f to int = %d, %.2f to int = %d", -2.9, (int)(-2.9), 2.9, (int)2.9);
    char string[OBJECTS_MAX] = "8-Bit Tea Party!";
    char key = '6';
    printf("\nsource text: ");
    for (int i = 0; i < 16; ++i)
        printf("%c",string[i]);
    printf("\nresult: ");
    for (int i = 0; i < 16; ++i) {
        string[i] ^= key;
        printf("%c",string[i]);
    }
    printf("\ndecript: ");
    for (int i = 0; i < 16; ++i) {
        string[i] ^= key;
        printf("%c",string[i]);
    }
}

int main()
{
    chapter_11();
    return 0;
}










