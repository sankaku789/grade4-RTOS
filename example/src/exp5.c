#include <stdio.h>
#include <math.h>

typedef union {
  double d;
  long p;
} DL;

void f_tPlus1(double f_t, int step, int parameter) {
    DL Ft;
    Ft.d = f_t;
    for(; step < 100; step++) {
        if (step < 1) {
            printf("f(%d) = %.20f ( 0x%lx)\n", step, Ft.d, Ft.p);
        } else {
            while(!(0 <= Ft.d && Ft.d <= pow(2, 1 - parameter))) {
                Ft.d = Ft.d - pow(2, 1 - parameter);
            }
            if (0 <= Ft.d && Ft.d < pow(2, -parameter)) {
                Ft.d = pow(2, parameter) * Ft.d;
                printf("f(%d) = %.20f ( 0x%lx)\n", step, Ft.d, Ft.p);
            } else {
                Ft.d = -pow(2, parameter) * (Ft.d - pow(2, 1 - parameter));
                printf("f(%d) = %.20f ( 0x%lx)\n", step, Ft.d, Ft.p);
            }
        }
    }
}


int main(void) {
    int t = 0, n = 1;
    double f_zero = 0.0;

    printf("input n, f(0) -> ");
    scanf("%d %lf", &n, &f_zero);

    for(int i = 1;  i < n + 1; i ++){
        f_tPlus1(f_zero, t, i);
        printf("\n");   
    }
    return 0;
}
