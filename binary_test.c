#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tang.h"



typedef union{
    unsigned long long int i;
    long double d;
} value_l;

typedef union{
    unsigned long int i;
    double d;
} value_d;

int main(int argv, char* argc[])
{
        int a;
        long int b;
        unsigned long int c;
        unsigned long long int d;
        float e;
        double f;
        long double g;
        printf("%ld\n", sizeof(a));
        printf("%ld\n", sizeof(b));
        printf("%ld\n", sizeof(c));
        printf("%ld\n", sizeof(d));
        printf("%ld\n", sizeof(e));
        printf("%ld\n", sizeof(f));
        printf("%ld\n", sizeof(g));
        return 0;
}