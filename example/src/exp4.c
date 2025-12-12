#include <stdio.h>

#define OFFSET 0.5
#define TIME 1000
#define BITWIDTH 64

typedef union {
    double d;
    long p;
} DL;

int main(void) {
    DL u;
    u.d = 0.0;

    for (int i = 0; i < TIME; i ++) {
        printf("%.20f ( %lx )\n", u.d, u.p);
        u.d += OFFSET;
    }
    printf("%.20f ( %lx )\n", u.d, u.p);

    if (u.d == TIME * OFFSET) {
        printf("%d * %lf = %lf\n", TIME, OFFSET, TIME * OFFSET);
    }
    else {
        printf("%d * %lf != %lf\n", TIME, OFFSET, TIME * OFFSET);
    }
}
