#include <stdio.h>
#include <math.h>

/*
 *  Глава 3. Величины логического типа.
 */


double calc (int c1, int c2)
{
    // Калькулятор для главы 3
    double c3 = 0;
    c3 = c1 + c2;
    printf("SUMM = %.0f\n",c3);
    c3 = c1 - c2;
    printf("DIFFER = %.0f\n",c3);
    c3 = c1 * c2;
    printf("PROD = %.0f\n",c3);
    c3 = c1 / c2;
    printf("DIVIS = %.0f,",c3);
    c3 = c1 % c2;
    printf("%.0f\n",c3);
    c3 = pow(c1,c2);
    printf("EXPON = %.0f\n",c3);
    c3 = sqrt(c1);
    printf("sqrt(a1) = %.1f\n",c3);
    c3 = sqrt(c2);
    printf("sqrt(a2) = %.1f\n",c3);
    return c3;
}

void chapter_3()
{
    printf("Chapter 3. Logical type, operators and statements;\n\n");
    int a1 = 0, a2 = 0;
    printf("This is Calculator 3000 SUPER\n");
    printf("Please enter two numbers: ");
    scanf("%d %d", &a1, &a2);
    calc(a1, a2);
    printf("3.6:\n");
    int x = 1, y = 0, z = 0;
    int temp1, temp2, temp3;
    temp1 = (x || y) && !z;
    printf("a) (%d OR %d) AND NOT %d = %d\n", x, y, z, temp1);
    temp2 = !x && !y;
    printf("b) NOT %d && NOT %d = %d\n", x, y, temp2);
    temp3 = !(x && z) || y;
    printf("c) NOT (%d AND %d) OR %d = %d\n", x, z, y, temp3);
    temp1 = (x && !y) || z;
    printf("d) %d AND (NOT %d OR %d) = %d\n", x, y, z, temp1);
    temp2 = x && (!y || z);
    printf("e) %d AND (NOT %d OR %d) = %d\n", x, y, z, temp2);
    temp3 = x || (!(y || z));
    printf("f) %d || (NOT(%d OR %d)) = %d\n\n", x, y, z, temp3);
    printf("3.7:\n");
    int a = 0, b = 1, c = 0;
    temp1 = a || !(a && b) || c;
    printf("a) %d OR NOT (%d AND %d) OR %d = %d\n", a, a, b, c, temp1);
    temp2 = !a || (a && (b || c));
    printf("b) NOT %d OR (%d AND (%d OR %d)) = %d\n", a, a, b, c, temp2);
    temp3 = (a || (b && !c)) && c;
    printf("c) (%d OR (%d AND NOT %d)) AND %d = %d\n\n", a, b, c, c, temp3);
    printf("3.8:\n");
    x = 0; y = 0; z = 0;
    temp1 = (x && !(z || y)) || !z;
    printf("a) %d AND NOT (%d OR %d) OR NOT %d = %d\n", x, z, y, z, temp1);
    temp2 = !x || (x && (y || z));
    printf("b) NOT %d OR %d AND (%d OR %d) = %d\n", x, x, y, z, temp2);
    temp3 = (x || (y && !z)) && z;
    printf("c) (%d OR %d AND NOT %d) AND %d = %d\n\n", x, y, z, z, temp3);
    printf("3.9:\n");
    x = 1; y = 0; z = 0;
    temp1 = !x || !y || !z;
    temp2 = (!x || !y) && (x || y);
    temp3 = (x && y) || (x && z) || !z;
    printf("NOT x OR NOT y OR NOT z = !%d || !%d || !%d = %d\n", x, y, z, temp1);
    printf("(NOT x OR NOT y) AND (x OR y) = (!%d || !%d) && (%d || %d) = %d\n", x, y, x, y, temp2);
    printf("x AND y OR x AND z OR NOT z = ");
    printf("%d && %d || %d && %d || !%d = %d\n\n", x, y, x, z, z, temp3);
    printf("3.10:\n");
    int A = 0, B = 0, C = 1;
    temp1 = (!A || !B) && !C;
    printf("(NOT A OR NOT B) AND NOT C = (!%d || !%d) && !%d = %d\n", A, B, C, temp1);
    temp2 = (!A || !B) && (A || B);
    printf("(NOT A OR NOT B) AND (A OR B) = (!%d || !%d) && (%d || %d) = %d\n", A, B, A, B, temp2);
    temp3 = (A && B) || (A && C) || !C;
    printf("(A AND B) OR (A AND C) OR !C = (%d && %d) || (%d && %d) || !%d = %d\n\n", A, B, A, C, C, temp3);
    x = 1; y = 2; int temp = 0;
    temp = (!(x * y < 0)) || (y > x);
    printf("3.11 (x = 1, y = 2):\n");
    printf("a) (!(x * y < 0)) || (y > x) = %d\n", temp);
    temp = (x >= 0) || (pow(y, 2) != 4);
    printf("b) (x >= 0) || (pow(y, 2) != 4) = %d\n", temp);
    temp = ((x * y) != 0) || (y > x);
    printf("c) ((x * y) != 0) || (y > x) = %d\n\n", temp);
    a = 0;
    printf("3.13:\n");
    while (a <= 1) {
        b = 0;
        while (b <= 1) {
            temp = !(a && b);
            printf("a) NOT (A AND B) = !(%d && %d) = %d\n", a, b, temp);
            temp = !a || b;
            printf("b) NOT A OR B = !%d || %d = %d\n", a, b, temp);
            temp = a || !b;
            printf("c) A OR NOT B = %d || !%d = %d\n\n", a, b, temp);
            ++b;
        }
        ++a;
    }
    printf("3.17\n");
    a = 0; b = 1;
    temp1 = (!a && !b) || a;
    printf("a) NOT %d AND NOT %d OR %d = %d\n", a, b, a, temp1);
    temp2 = b || (!a && !b);
    printf("b) %d OR NOT %d AND NOT %d = %d\n", b, a, b, temp2);
    temp3 = b && !(a && !b);
    printf("c) %d AND NOT (%d AND NOT %d) = %d\n\n", b, a, b, temp3);
    int b1 = 0;
    a1 = 0;
    printf("3.19:\n");
    while (a1 <= 1) {
        b1 = 0;
        while (b1 <= 1) {
            temp = !(!a1 && !b1) && a1;
            printf("NOT (NOT A AND NOT B) AND A = !(!%d && !%d) && %d = %d\n", a1, b1, a1, temp);
            temp = !(!a1 || !b1) || a1;
            printf("NOT (NOT A OR NOT B) OR A = !(!%d || !%d) || %d = %d\n", a1, b1, a1, temp);
            temp = !(!a1 || !b1) && b1;
            printf("NOT (NOT A OR NOT B) AND B = !(!%d || !%d) && %d = %d\n\n", a1, b1, b1, temp);
            ++b1;
        }
        ++a1;
    }
    int n1 = 0, c1 = 0;
    printf("3.25:\n");
    while (n1 < 8) {
        a1 = n1 % 2;
        b1 = (n1 % 4) / 2;
        c1 = n1 / 4;
        printf("a = %d, b = %d, c = %d\n", a1, b1, c1);
        temp = !(a1 && b1) && (!a1 || !c1);
        printf("NOT (A AND B) AND (NOT A OR NOT C) = %d\n", temp);
        temp = !(a1 && !b1) || (a1 || !c1);
        printf("NOT (A AND NOT B) OR (A OR NOT C) = %d\n", temp);
        temp = (a1 && !b1) || !(a1 || !c1);
        printf("A AND NOT B OR NOT (A OR NOT C) = %d\n\n", temp);
        ++n1;
    }
    int n = 0;
    printf("3.26:\n");
    while (n < 8) {
        x = n % 2;
        y = (n % 4) / 2;
        z = n / 4;
        printf("x = %d, y = %d, z = %d\n", x, y, z);
        temp = !(x || y) && (!x || !z);
        printf("a) NOT(x OR y) AND (NOT x OR NOT z) = ");
        printf("!(%d || %d) && (!%d || !%d) = %d\n", x, y, x, z, temp);
        temp = !(!x && y) || (x && !z);
        printf("b) NOT (NOT x AND y) OR (x AND NOT z) = ");
        printf("!(!%d && %d) || (%d && !%d) = %d\n", x, y, x, z, temp);
        temp = x || (!y && !(x || !z));
        printf("c) x OR (NOT y AND NOT(x OR NOT z)) = ");
        printf("%d || (!%d && !(%d || !%d)) = %d\n\n", x, y, x, z, temp);
        ++n;
    }
    x = 5;
    y = 4;
    printf("3.27:\n");
    printf("a) x > 2 && y > 3 = %d > 2 && %d > 3 = %d\n", x, y, (x > 2 && y > 3));
    temp = 0 < (y <= 4) && (x < 5);
    printf("b) 0 < y <= 4 && x < 5 = 0 < %d <= 4 && %d < 5 = %d\n", x, y, temp);
    temp = !((x > 0) && (x < 5));
    printf("c) NOT((x > 0) AND (x < 5)) = %d\n", temp);
    temp = (x >= 0) && (y < 5);
    printf("d) (x >= 0) AND (y < 5) = %d\n\n", temp);
    x = 254; y = 0; z = -259;
    printf("3.29: x = %d, y = %d, z = %d\n", x, y, z);
    temp1 = (x % 2) && (y % 2);
    printf("a) x AND y odd = %d\n", temp1);
    temp2 = (x < 20) ^ (y < 20);
    printf("b) (x < 20) XOR (y < 20) = %d\n", temp2);
    temp3 = (x == 0) || (y == 0);
    printf("c) (x == 0) OR (y == 0) = %d\n", temp3);
    temp1 = x < 0 && y < 0 && z < 0;
    printf("d) x, y and z negative = %d\n", temp1);
    temp2 = ((x % 5 == 0) + (y % 5 == 0) + (z % 5 == 0)) == 1;
    printf("e) only 1 of x, y, z divided by 5 = %d\n", temp2);
    temp3 = (x > 100) || (y > 100) || (z > 100);
    printf("f) At least one of x, y, z more than 100 = %d\n\n", temp3);
    x = 10;
    temp = (x % 5 == 0) || (x % 7 == 0);
    printf("3.31:\na) (N %% 5 == 0) || (N %% 7 == 0) = (%d %% 5 == 0) || (%d %% 7 == 0) = %d\n", x, x, temp);
    temp = (x % 4 == 0) || (x % 10 != 0);
    printf("b) (x %% 4 == 0) || (x %% 10 != 0) = (%d %% 4 == 0) || (%d %% 10 != 0) = %d\n\n", x, x, temp);
    x = 3;
    y = 1;
    printf("3.32\n");
    temp = y >= 1 && x <= -2;
    printf("a) y >= 1 && x <= -2 = %d\n", temp);
    temp = y >= -2 && y <= 1.5;
    printf("b) -2 >= y <= 1.5 = %d\n", temp);
    temp = y <= 4 && x >= 1 && x <= 2;
    printf("c) y <= 4 && 1 <= x <= 2 = %d\n", temp);
    temp = x >= 1 && y >= 2 && y <= 4;
    printf("d) x >= 1 && 2 <= (y <= 4) = %d\n", temp);
    temp = (y >= 0 && x >= 2) || (y <= -1 && x >= 1);
    printf("e) (y >= 0 && x >= 2) || (y <= -1 && x >= 1) = %d\n", temp);
    temp = (y >= 1 && x >= 2) || (y <= -1.5 && x >= 2);
    printf("f) (y >= 1 && x >= 2) || (y <= -1.5 && x >= 2) = %d\n", temp);
    temp = x >= 1 && x <= 3 && y >= -2 && y <= -1;
    printf("g) 1 <= (x <= 3) && -2 <= (y <= -1) = %d\n", temp);
    temp = (y >= 0 && y <= 2 && x < 2) || (x >= 2);
    printf("h) (0.5 <= y <= 1.5 && x <= 2) || (x >= 2) = %d\n\n", temp);
    printf("3.34\n");
    int c_a = 0, c_b = 0, c_c = 0, c_d = 0;
    c_c = 7;
    temp = (c_a == c_c) || (c_d == c_b);
    printf("a) %d\n", temp);
    c_a = 3; // bishop
    c_b = 4;
    c_c = 1; // pawn
    c_d = 6;
    temp = abs(c_c - c_a) == abs(c_d - c_b);
    printf("b) bishop on (%d,%d) and pawn (%d,%d) = %d\n", c_a, c_b, c_c, c_d, temp);
    c_a = 3; // king
    c_b = 4;
    c_c = 3; // pawn
    c_d = 5;
    temp = (abs(c_c - c_a) <= 1) || (abs(c_d - c_b) <= 1);
    printf("c) king on (%d,%d) and pawn (%d,%d) = %d\n", c_a, c_b, c_c, c_d, temp);
    c_a = 5; // queen
    c_b = 4;
    temp = ((c_a == c_c) || (c_d == c_b)) || (abs(c_c - c_a) == abs(c_d - c_b));
    printf("d) queen on (%d,%d) and pawn on(%d,%d) = %d\n", c_a, c_b, c_c, c_d, temp);
    printf("3.35\n");
    c_a = 3; // rook
    c_b = 4;
    c_c = 5; // queen
    c_d = 5;
    int c_e = 3; // target
    int c_f = 7;
    temp = ((c_a == c_e) ^ (c_b == c_f));
    temp = temp && (((c_e == c_c) || (c_d == c_f)) || (abs(c_c - c_e) == abs(c_d - c_f)));
    printf("a) Rook on %d:%d moves to %d:%d, queen on %d:%d = %d;\n", c_a, c_b, c_e, c_f, c_c, c_d, temp);
    c_a = 1; // queen
    c_b = 2;
    c_c = 7; // bishop
    c_d = 8;
    c_e = 5; // target
    c_f = 6;
    temp = ((c_e == c_a) || (c_b == c_f)) || (abs(c_a - c_e) == abs(c_b - c_f));
    temp = temp && (abs(c_c - c_e) == abs(c_d - c_f));
    printf("b) Queen on %d:%d moves to %d:%d, bishop on %d:%d = %d;\n", c_a, c_b, c_e, c_f, c_c, c_d, temp);
    c_a = 4; // knight
    c_b = 4;
    c_c = 7; // bishop
    c_d = 8;
    c_e = 5; // target
    c_f = 6;
    temp = (abs(c_a - c_e) == 1 && abs(c_b - c_f) == 2) || (abs(c_a - c_e) == 2 && abs(c_b - c_f) == 1);
    temp = temp && (abs(c_c - c_e) == abs(c_d - c_f));
    printf("c) Knight on %d:%d moves to %d:%d, bishop on %d:%d = %d;\n\n", c_a, c_b, c_e, c_f, c_c, c_d, temp);
}
