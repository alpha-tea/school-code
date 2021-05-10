#include "global.h"
#include "library.h"

void number_of_degrees (int n)
{
    int i,k,a = 1;
    for ( i = 3, k = 5; (i <= n || k <= n) && i != n && k != n; i *= 3, k *= 5) {
        ++a;
        printf("%d:%d\n",i,k);
    }
    if ( i == n)
        printf("n - %d power of 3\n\n",a);
    else
        printf("Number n is not a power of 3\n");
    if (k == n)
        printf("n - %d power of 5\n\n",a);
    else
        printf("Number n is not a power of 5\n\n");
}

void fibonachi (int n)
{
    int a = 1, b = 1, c = 0;
    printf("Fibonachi: %d %d ", a, b);
    while (c < n) {
        c = a + b;
        a = b;
        b = c;
        printf("%d ",c);
    }
    if (c == n)
        printf("\nYes, n is a fibonacci number!\n\n");
    else
        printf("\nNo, n is not a Fibonacci number!\n\n");
}

int arif_sequence (int n, int f, int s)
{
    printf("Sequence: ");
    for (int i = 0; f < n; ++i, f += s)
        printf("%d ",f);
    printf("\n");
    return f;
}

int geom_seqence (int m, int g, int z)
{
    printf("Sequence: ");
    for (int i = 0; g < m; ++i, g *= z)
        printf("%d ",g);
    printf("\n");
    return g;
}

int natural_number(int n)
{
    int k = 0, x = 0, sum = 0, product = 1, sred_arif = 0;
    int sum_square = 0, sum_cube = 0, first_number = 0, sum_first_and_last = 0;
    while (n > 0) {
        x = n % 10;
        sum += x;
        product *= x;
        sum_square += x * x;
        sum_cube += pow(x,3);
        n /= 10;
        ++k;
        if (k == 1)
            first_number = x;
    }
    //sred_arif = sum / k;
    sum_first_and_last = first_number + x;
    printf("a)the number of digits in it: %d\n",k);
    printf("b)the sum of his digits: %d\n",sum);
    printf("v)product of its numbers: %d\n",product);
    printf("g)arithmetic mean of its digits: %d\n",sred_arif);
    printf("d)the sum of the squares of its digits: %d\n",sum_square);
    printf("e)the sum of the cubes of its digits: %d\n",sum_cube);
    printf("zh)its first digit: %d\n",first_number);
    printf("z)the sum of its first and last digits: %d\n\n",sum_first_and_last);
    return 0;
}

int lcm (int a, int b)
{
    return (abs(a * b) / evklid(a,b));
}

void chapter_6()
{
    srand(0);
    printf("6.1\n");
    int n = 0, sum = 0, quantity = 1;
    printf("Hello! Please enter any integers in turn or write 0 to complete;\n");
    scanf("%d",&n);
    while (n != 0) {
        sum += n;
        ++quantity;
        scanf("%d",&n);
    }
    printf("Sum of %d numbers equals = %d;\n\n",quantity,sum);
    printf("6.4\n");
    n = 5;
    int a1 = 0;
    while ((a1 = rand() % 10) > 5  && (n > 0)) {
        printf("%d; ",a1);
        --n;
    }
    n = 99;
    printf("\n\n6.8.posledowatelnost kvadratov chisel < n(%d)\n",n);
    for (int i = 1; i * i < n;++i)
        printf("%d; ",i * i);
    printf("\n\n6.11.posledowantelnost v intervale ot 1 do 1.5\n");
    double a = 1.3;
    n = 7;
    if (a > 1.0 && a <= 1.5) {
        for (int i = 2; i < n; ++i) {
            double double_value = 1.0 + (1.0 / i);
            if (double_value < a)
                printf("1 + (1 / %d) < a(%.1f)\n",i,a);
            else
                printf("Value(%.2f) not printed\n",double_value);
        }
    } else
        printf("You entered incorrect value!\n\n");
    a = 1.1;
    printf("\n6.14.max n pri a = %.2f\n",a);
    double double_value = 1.0 + (1.0 / 2);
    if (a > 1 && a <= 1.5) {
        for (int i = 2; double_value > a; ++i) {
            double_value = 1.0 + (1.0 / i);
            if (double_value > a)
                printf("1.0 + 1.0 / %d > a(%.1f), n = %d\n",i,a,i);
        }
    } else
        printf("You entered incorrect value!\n\n");
    a = 2.5;
    double summ = 30;
    printf("6.17.summa 1 + 1 / 2 + 1 / 3 ... + 1 / n > a, a = %.2f\n",a);
    for (n = 2; summ < a || n == 2; ++n) {
        printf("n = %d: ",n);
        int x = 1;
        summ = 0;
        while (x <= n) {
            summ += 1.0 / x;
            printf("summ = %.2f; ",summ);
            ++x;
        }
        if (summ < a)
            printf("summ < a, next n;\n");
        else
            printf("summ > a, end;\n");
    }
    double eps = 0.000001;
    printf("\n6.20.posledowatelnost y(n), eps = %.2f\n",eps);
    double double_x = 5;
    double prev_y = 0.5 * (double_x / -1), y = 0.5 * (prev_y + (double_x / (prev_y - 1)));
    for (int i = 1; fabs(y * y - prev_y * prev_y) >= eps;++i) {
        prev_y = y;
        y = 0.5 * (prev_y + (double_x / (prev_y - 1)));
        double delta = fabs(y * y - prev_y * prev_y);
        printf("%.9f; ",delta);
    }
    n = 124236;
    printf("\n\n6.23, n = %d\n",n);
    int value = 0;
    int x1 = 3; int x2 = 0; // a
    int x3 = 4; int x4 = 0; // б
    int x5 = 5; sum = 0;    // в
    int x6 = 3;int x7 = 2;int x8 = 0;int x9 = 0; //г
    while (n > 0) { // Длинна числа.
        value = abs(n) % 10;
        n /= 10;
        if (x1 == value)
            ++x2;
        if (value % x3 == 0)
            ++x4;
        if (value > x5 && x5 <= 8 && x5 >= 0)
            sum += value;
        if (x6 == value)
            ++x8;
        if (x7 == value)
            ++x9;
    }
    if (x8 > x9)
        x8 = x9;
    printf("a)%d;\nb)%d;\nv)%d;\ng)%d\n",x2,x4,sum,x8);
    n = 246957;
    printf("\n6.26 and 6.29, number is %d;\n",n);
    int k = 0;
    int x_max = 0;
    int x_min = 9;
    int max_pos = 0, min_pos = 0;

    while (n > 0) {
        value = n % 10;
        n /= 10;
        ++k;
        if (value > x_max) {
            x_max = value;
            max_pos = k;
        }
        if (value < x_min) {
            x_min = value;
            min_pos = k;
        }
    }
    printf("a)max = %d;\nfrom start = %d;\nfrom the end = %d\n",x_max,max_pos,k - max_pos + 1);
    printf("b)min = %d;\nfrom start = %d;\nfrom the end = %d\n",x_min,min_pos,k - min_pos + 1);
    n = 12345;
    printf("\n6.32, n = %d\n",n);
    x_min = 9;
    int x_amount = 0;
    while (n > 0) {
        value = n % 10;
        n /= 10;
        if (value < x_min) {
            x_amount = 0;
            x_min = value;
        }
        if (value == x_min)
            ++x_amount;
    }
    printf("min = %d,quantity = %d;\n\n",x_min,x_amount);
    printf("6.35\n");
    x1 = 0;
    for (n = 500;x1 < 10;++n) {
        if (n % 13 == 0) {
            ++x1;
            printf("%d %% 13 = 0;\n",n);
        }
        if (n % 17 == 0) {
            ++x1;
            printf("%d %% 17 = 0;\n",n);
        }
    }
    n = 1237174;
    x1 = n;
    printf("\n6.38, n = %d\n",n);
    while (n > 0) {
        value = n % 10;
        n /= 10;
    }
    while (x1 > 0) {
        x2 = x1 % 10;
        x1 /= 10;
        if (x2 == value)
            ++n;
    }
    printf("first number %d; quantity %d;\n\n",value,n);
    n = 987123;
    printf("6.41, n = %d\n",n);
    x1 = 0;
    x2 = 9;
    x3 = 0;
    x4 = 0;
    while (n > 0) {
        value = n % 10;
        n /= 10;
        if (value > x1) {
            x3 = x1;
            x1 = value;
        } else
            if (value > x3 && x1 > x3 && value != x1)
                x3 = value;
        if (value < x2) {
            x4 = x2;
            x2 = value;
        } else
            if (value < x4 && x2 < x4 && value != x2)
                x4 = value;
    }
    printf("max(1) = %d; max(2) = %d\n",x1,x3);
    printf("min(1) = %d; min(2) = %d\n",x2,x4);
    printf("\n6.43 - 6.44\n");
    srand(3);
    n = 10;
    int is_seq = 0;
    int seq_am = 0;
    k = 0;
    int mass[n], digits[n];
    printf("Sequence: %d\n",n);
    for (int i = 0;i < n;++i) {
        mass[i] = k;
        k += rand() % 2;
        printf("%d ",mass[i]);
        digits[i] = 0;
    }
    for (int i = 0;i < n;++i) {
        if (i > 0 && !is_seq && mass[i] == mass[i - 1]) {
            is_seq = 1;
            ++seq_am;
        } else  if (mass[i] != mass[i - 1])
            is_seq = 0;
        ++digits[mass[i]];
    }
    printf("\nresult = %d\n",seq_am);
    printf("Chastota chisel :=");
    for (int i = 0; i < n;++i)
        printf(" %d:%d",i,digits[i]);
    printf("\n\n6.45\n");
    x1 = 7;//a
    x2 = 35;//b
    x3 = 33;//c
    if (x1 > 0 && x2 > 0 && x3 > 0) {
        int help_nod_first_step = 0, help_nod_second_step = 0;
        help_nod_first_step = evklid(x1,x2);
        printf("NOD(a,b) = NOD(%d,%d) = %d\n",x1,x2,help_nod_first_step);
        help_nod_second_step = evklid(help_nod_first_step,x3);
        printf("NOD(a,b,c) = NOD(%d,%d,%d) = %d\n\n",x1,x2,x3,help_nod_second_step);
    } else {
        printf("You entered incorrect numbers!!\n\n\a");
    }
    value = 12345;
    printf("6.48, value = %d,digits: ",value);
    sum = 0;
    k = 7;
    quantity = 0;
    int b = 1234;
    int x = 1;
    int y1 = 6, y2 = 0;
    a1 = 13;
    int prod_numbers = 1;
    int m = 3;
    n = 5;
    int help = value, help1 = 0;
    while (help > 0) {
        help1 = help % 10;
        help /= 10;
        sum += help1;
        prod_numbers *= help1;
        ++quantity;
        if (quantity == 1)
            y2 = help1;
        printf("%d ",help1);
    }
    x1 = help1;
    printf("\n");
    if (sum > k)
        printf("a) Sum numbers(%d) > k(%d), ",sum,k);
    else
        printf("a) Sum numbers(%d) < k(%d), ",sum,k);
    if (value % 2 == 0)
        printf("value is even;\n");
    else
        printf("value is odd;\n");
    if (quantity % 2 == 0)
        printf("b) Number of digits(%d) - even number, ",quantity);
    else
        printf("b) Number of digits(%d) - odd number, ",quantity);
    if (value < b)
        printf("value < b(%d);\n",b);
    else
        printf("value > b(%d);\n",b);
    if (x == x1)
        printf("v) Number starts with x(%d), ",x);
    else
        printf("v) Number does not start with x(%d), ",x);
    if (y1 == y2)
        printf("number ends on y(%d);\n",y1);
    else
        printf("number does not end on y(%d);\n",y1);
    if (prod_numbers < a1)
        printf("g) Product of digits less than a(%d), ",a1);
    else
        printf("g) Product of digits greater than a(%d), ",a1);
    if (value % b == 0)
        printf("number is divisible by b(%d);\n",b);
    else
        printf("number is not divisible by b(%d);\n",b);
    if (sum > m)
        printf("d) Sum numbers(%d) > m(%d), ",sum,m);
    else
        printf("d) Sum numbers(%d) < m(%d), ",sum,m);
    if (value % n == 0)
        printf("number is divisible by n(%d);\n\n",n);
    else
        printf("number is not divisible by n(%d);\n\n",n);
    printf("6.51\n");
    n = 123321;
    help = n;
    k = 0;
    x = 0;
    while (help > 0) {
        help /= 10;
        ++k;
    }
    printf("Value = %d have %d digits: ",n,k);
    help = n;
    int mass1[k];
    k = 0;
    while (help > 0) {
        help1 = help % 10;
        help /= 10;
        mass1[k] = help1;
        ++k;
        printf("%d ",help1);
    }
    printf("\nCheck palindrom: ");
    while (x < k && mass1[x] == mass1[k - 1]) {
        printf("%d[%d]:%d[%d] ",mass1[x],x,mass1[k - 1],k - 1);
        ++x;
        --k;
    }
    if (x >= k)
        printf("\nThis is palindrom\n\n");
    else
        printf("\nThis is not palindrom\n\n");
    printf("6.54\n");
    n = 103;
    k = 0;
    x2 = 0;
    printf("Value, digits: %d\n",n);
    while (n > 0) {
        x = n % 10;
        n /= 10;
        x1 = x;
        x = n % 10;
        if (x1 <= x)
            ++x2;
        ++k;
        printf("%d:%d ",x,x1);
    }
    if (k > 1) {
        if (k - 1 == x2)
            printf("cifry po ne ubyvaniy\n\n");
        else
            printf("cifry po ubyvaniy\n\n");
    } else
        printf("nedostatochno cifr dla posledovatelnosty\n\n");
    printf("6.57, double data array, size %d: ",ARRAY_SIZE);
    double mass2[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE ; ++i) {
        mass2[i] = (double)(rand() % 10) / (double)(1 + rand() % 10);
        printf("%.2f ",mass2[i]);
    }
    printf("\n");
    y = 3.61; //n
    x = 0;
    double d1 = 0;
    d1 = fabs(mass2[0] - y);
    for (int i = 1;i < ARRAY_SIZE;++i) {
        a = fabs(mass2[i] - y);
        if (a < d1) {
            d1 = a;
            x = i;
        }
    }
    printf("%.2f:%d\n\n",mass2[x],x + 1);
    printf("6.60\n");
    srand(time(NULL));
    n = 0;
    int i;
    printf("Sequence: ");
    for (i = 1;i <= 10 && n % 10 != 7;++i) {
        n = rand() % 100;
        printf("%d ",n);
    }
    if (n % 10 == 7)
        printf("\n%d:%d\n\n",n,i - 1);
    else
        printf("\nThere is no number in the sequence that ends in 7\n\n");
    printf("6.63\n");
    srand(time(NULL));
    n = 0;
    k = 0;
    printf("Appraisals: ");
    for (int i = 1; i <= 5; ++i) {
        n = 1 + rand() % 5;
        printf("%d ",n);
        if (n == 2)
            ++k;
    }
    if (k != 0)
        printf("\nYes!\nTwos in class: %d\n\n",k);
    else
        printf("\nNo twos!\n\n");
    printf("6.66\n");
    srand(time(NULL));
    n = 0;
    k = 1;
    x1 = 0;
    x2 = 0;
    printf("Values: ");
    for (int i = 1; n != -1; ++i) {
        x = n;
        n = k + rand() % 10;
        printf("%d ",n);
        if (i > 2) {
            k = -1;
        }
        if (x == n && x2 != -1) {
            x2 = -1;
            x1 = i;
        }
    }
    if (x2 == -1) {
        printf("\n%d:%d\n\n",x1 - 1,x1);
    } else
        printf("\nNo couple;\n\n");
    printf("6.69\n");
    k = 0;
    printf("Sequence: ");
    srand(time(NULL));
    int mass3[ARRAY_SIZE];
    x = 1 + rand() % ARRAY_SIZE;
    for (int i = 0; i < ARRAY_SIZE; ++i)
        if (i == x)
            mass3[i] = i + rand() % 2;
        else
            mass3[i] = i + 1;
    for (int i = 0;i < ARRAY_SIZE - 1; ++i)
        if (mass3[i] < mass3[i + 1])
            printf("%d ",mass3[i]);
        else {
            k = -1;
            printf("|%d| ",mass3[i]);
        }
    if (k != 0)
        printf("\nThe sequence was broken!!!\n\n");
    else
        printf("\nThe sequence is normal!!!\n\n");
    printf("6.72\n");
    const int com_table = 3;
    int commands[com_table];
    printf("Score:\n");
    for (int i = 0; i < com_table; ++i) {
        commands[i] = rand() % 25;
        printf("%d) %d\n",i + 1, commands[i]);
    }
    for (i = 0; i < com_table - 1; ++i) {
        if (commands[i] < commands[i+1]) {
            printf("\nItems are not in the correct order!\n\n");
            break;
        }
    }
    if (i == 2)
        printf("Everything is OK):D)\n\n");
    printf("6.75\n");
    printf("Create bazaar: ");
    const int bazaar_size = 28;
    const int bone_size = 2;
    const int total_dots = 7;
    int bazaar_mass[bazaar_size][bone_size];
    for (int i = 0, m = 0, n = 0, j = 0; i < total_dots * total_dots; ++i) {
        if (m <= n){
            bazaar_mass[j][0] = m;
            bazaar_mass[j][1] = n;
            ++j;
            printf("%d:%d ",m,n);
        }
        ++n;
        if (n == 7) {
            n = 0;
            ++m;
        }
    }
    for (int i = 0; i < bazaar_size; ++i) {
        int p1 = rand() % bazaar_size;
        int p2 = rand() % bazaar_size;
        int m = bazaar_mass[p1][0];
        int n = bazaar_mass[p1][1];
        bazaar_mass[p1][0] = bazaar_mass[p2][0];
        bazaar_mass[p1][1] = bazaar_mass[p2][1];
        bazaar_mass[p2][0] = m;
        bazaar_mass[p2][1] = n;
    }
    printf("\nbazar ready to game: ");
    for (int i = 0; i < bazaar_size; ++i)
        printf("%d:%d ",bazaar_mass[i][0], bazaar_mass[i][1]);
    int left = bazaar_mass[0][0];
    int right = bazaar_mass[0][1];
    printf("\n");
    printf("Start bone: %d:%d\n", left, right);
    for (int i = 1; i < bazaar_size; ++i) {
        if (bazaar_mass[i][0] == left || bazaar_mass[i][1] == left) {
            printf("left: bazar: %d:%d, old left: %d, ", bazaar_mass[i][0], bazaar_mass[i][1], left);
            if (bazaar_mass[i][0] == left)
                left = bazaar_mass[i][1];
            else
                left = bazaar_mass[i][0];
            printf(" new left: %d;\n",left);
            continue;
        }
        if (bazaar_mass[i][0] == right || bazaar_mass[i][1] == right) {
            printf("right: bazar: %d:%d, old right: %d, ", bazaar_mass[i][0], bazaar_mass[i][1], right);
            if (bazaar_mass[i][0] == right)
                right = bazaar_mass[i][1];
            else
                right = bazaar_mass[i][0];
            printf(" new right: %d;\n",right);
            continue;
        }
        break;
    }
    n = 2187;
    printf("\n6.76(a and b), number: %d\n",n);
    number_of_degrees(n);
    n = 113;
    printf("6.77, n: %d\n",n);
    fibonachi(n);
    n = 21;
    int f = 0;
    int s = 7;
    printf("6.78, n = %d, f = %d, s = %d;\n",n,f,s);
    int result = arif_sequence(n,f,s);
    if (result == n)
        printf("Yes;\n\n");
    else
        printf("No;\n\n");
    m = 48;
    int g = 3;
    int z = 2;
    printf("6.79, m = %d, g = %d, z = %d;\n", m, g, z);
    result = geom_seqence(m,g,z);
    if (result == m)
        printf("Yes;\n\n");
    else
        printf("No;\n\n");
    n = 905090955;
    int nine = 0;
    int zero = 0;
    printf("6.80, n = %d;\n",n);
    while (n > 0) {
        x = n % 10;
        printf("%d ",x);
        n /= 10;
        if (x == 9)
            ++nine;
        if (x == 0)
            ++zero;
    }
    if (nine > zero)
        printf("\nThere are more nines(%d) than zeros(%d);\n\n",nine,zero);
    else
        if (zero > nine)
            printf("\nThere are more zeros(%d) than nines(%d);\n\n",zero,nine);
        else
            printf("\nThe number of zeros(%d) and nines(%d) is the same;\n\n",zero,nine);
    n = 20311;
    int max = 0;
    int min = 9;
    max_pos = 0;
    min_pos = 0;
    k = 0;
    printf("6.82, 6.84, n = %d\n",n);
    while (n > 0) {
        x = n % 10;
        n /= 10;
        if (x > max) {
            max = x;
            max_pos = k;
        }
        if (x < min) {
            min = x;
            min_pos = k;
        }
        ++k;
    }
    printf("(min: %d + max: %d) %% 2 =  ", min, max);
    if ((min + max) % 2 == 0)
        printf("even;\n");
    else
        printf("odd;\n");
    if (max_pos > min_pos)
        printf("Maximum value: %d to the left; Max pos = %d\n\n",max,max_pos);
    else {
        if (min_pos > max_pos) {
            printf("Minimum value: %d to the left; Min pos = %d\n\n",min, min_pos);
        } else
            printf("Values(%d:%d), position(%d:%d);\n\n",max,min,max_pos,min_pos);
    }
    x = 3; //a
    b = 4; //b
    n = 12345;
    help = 0;
    help1 = 0;
    k = 0;
    printf("6.86, a = %d, b = %d, n = %d\n",x,b,n);
    while (n > 0) {
        x1 = n % 10;
        n /= 10;
        ++k;
        if (x1 == x && help == 0)
            help = k;
        if (x1 == b && help1 == 0)
            help1 = k;
    }
    if (help < help1)
        printf("a(%d) is more to the right than b(%d);\n\n",help, help1);
    else
        printf("b(%d) is more to the right than a(%d);\n\n",help1, help);
    printf("6.90\n");
    i = 10;
    x = 15;
    printf("a,number: power 1) ");
    while (i <= x) {
        printf("%d:%d ", i, i * i);
        ++i;
    }
    printf("\nb,number: power 2) ");
    i = 10;
    x = 15;
    do {
        printf("%d:%d ", i, i * i);
        ++i;
    } while (i <= x);
    printf("\n\n");
    n = 908809;
    printf("6.91, n = %d\n",n);
    natural_number(n);
    printf("6.93\n");
    srand(time(NULL));
    int precipitation[31];
    precipitation[0] = 0;
    printf("Sequance: %d ", precipitation[0]);
    for (int i = 1; i <= 30; ++i) {
        precipitation[i] = rand() % 10;
        printf("%d ",precipitation[i]);
    }
    i = 1;
    while (precipitation[i] != 0) {
        printf("\nDay: %d, precipiatation: %d;", i, precipitation[i]);
        ++i;
    }
    if (i == 30) {
        printf("\nNo precipitation in May\n\n");
    } else
        printf("\nfirst dry day: %d\n",i);
    printf("\n6.95\n");
    for (i = 5000; i % 39 != 0 && i >= 39; --i)
        ;
    printf("i: %d;\n\n",i);
    printf("6.102\n");
    int NOK = 0;
    n = 64;
    x = 48;
    NOK = lcm(n,x);
    printf("NOK(%d,%d):= %d\n\n",n,x,NOK);
    printf("6.103\n");
    n = 75; // числитель
    x = 125; // знаменатель
    result = evklid(n,x);
    printf("NOD = %d;\n",result);
    printf("Was: %d/%d;\n",n,x);
    x /= result;
    n /= result;
    printf("Became: %d/%d;\n\n",n,x);
    printf("6.105\n");
    x = 13;  //a
    n = 4;  //b
    i = 1;
    while (x > 0 && n > 0) {
        if (x > n) {
            x -= n;
            printf("%d)square: %dx%d;\n",i,n,n);
        } else {
            n -= x;
            printf("%d)square: %dx%d;\n",i,x,x);
        }
        ++i;
    }
    x = 21;
    b = 7;
    printf("\n6.106, a = %d, b = %d\n",x,b);
    i = 0;
    while (x - b >= 0) {
        x -= b;
        ++i;
    }
    printf("a) a / b = %d;\n",i);
    printf("b) a %% b = %d;\n\n",x);
    m = 64;
    n = 48;
    printf("6.107, m = %d, n = %d\n",m,n);
    for (i = 1; i <= m * n; ++i) {
        while (m % i == 0) {
            printf("%d cratno %d\n",i,m);
            break;
        }
        while (n % i == 0) {
            printf("%d cratno %d\n",i,n);
            break;
        }
    }
    n = 256;
    printf("\n6.108, money = %d\n",n);
    int money[7] = {0,0,0,0,0,0,0};
    for (i = 0, x = 64; x >= 1; ++i, x /= 2)
        while (n >= x) {
            n -= x;
            ++money[i];
        }
    for (i = 0, x = 64; i <= 6; ++i, x /= 2)
        printf("%d = %d;\n",x,money[i]);
    printf("\n6.110\n");
    n = 12345;
    x = n;
    m = 3; //a
    k = 0;
    printf("a) ");
    while (x > 0) {
        x1 = x % 10;
        x /= 10;
        printf("%d",x1);
        ++k;
    }
    x1 = k;
    int number_1[x1];
    for (i = 0; n > 0; ++i) {
        x = n % 10;
        number_1[i] = x;
        n /= 10;
    }
    printf("\nb) N = ");
    int n1 = 0;
    for (i = -1, x = 1;i <= x1; ++i, x *= 10) {
        if (i == -1)
            n1 += 2;
        else if (i == x1)
            n1 += 2 * x;
        else
            n1 += number_1[x1 - i - 1] * x;
        printf("%d, ",n1);
    }
    printf("\nv) ");
    for (i = x1 - 1; i >= 0; --i)
        if (number_1[i] != m)
            printf("%d",number_1[i]);
    printf("\ng) ");
    x = number_1[0];
    number_1[0] = number_1[x - 1];
    number_1[x - 1] = x;
    for (i = x1 - 1; i >= 0; --i)
        printf("%d",number_1[i]);
    number_1[x - 1] = number_1[0];
    number_1[0] = x;
    printf("\nd) ");
    for (i = x1 - 1; i >= 0; --i)
        printf("%d",number_1[i]);
    for (i = x1 - 1; i >= 0; --i)
        printf("%d",number_1[i]);
    printf("\n\n6.111\n");
    n = 362880;
    x = 1;
    for (i = 0; x < n; ++i)
        x *= i + 1;
    if (x == n)
        printf("factorial = %d, number = %d;\n", n, i);
    else
        printf("This is not a factorial!\n\n");
}
