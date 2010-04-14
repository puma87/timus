#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n, res;

  scanf("%d", &n);

  res = abs(n) * (abs(n) + 1) >> 1;
  if (n < 0) {
    res = 1 - res;
  } else if (!n) {
    res = 1;
  }

  printf("%d\n", res);

  return 0;
}
