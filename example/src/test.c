#include <stdio.h>
#include <math.h>

double pow2(int n) {
  return pow(2.0, (double)n);
}

double f(double first, double n, int t) {
  if (t == 0) {
    return first;
  } else {
      double ft = f(first, n, t - 1);
    if (ft >= 0 && ft < pow2(-n)) {
      return pow2(n) * ft;
    } else {
      return - (pow2(n) * (ft - pow2((-n) + 1)));
    }
  }
}

int main() {
  double first = 0.5;
  double n = 1; // 例としてn=1を使用
  
  for (int t = 0; t <= 100; t++) {
    printf("f(%d) = %f\n", t, f(first, n, t));
  }

  return 0;
}
