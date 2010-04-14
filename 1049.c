#include <stdio.h>

#define N 10
#define MAX_VAL 10001

int powers[MAX_VAL];

int main(void) {
  int i, j, val, res = 1;
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
  freopen("output", "w", stdout);
#endif

  for (i = 0; i < N; ++i) {
    scanf("%d", &val);
    for (j = 2; val != 1; ++j) {
      while (!(val % j)) {
        ++powers[j];
        val /= j;
      }
    }
  }

  for (i = 2; i <= MAX_VAL; ++i) {
    res = (res * (powers[i] + 1)) % N;
  }

  printf("%d\n", res);

  return 0;
}
