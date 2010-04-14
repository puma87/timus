#include <stdio.h>
#include <string.h>

#define MAX_K 32

long long n, k;
char exclamation_marks[MAX_K];

int main(void) {
  long long res = 1;

#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif

  scanf("%lld %s", &n, exclamation_marks);
  k = strlen(exclamation_marks);

  for (; n > 0; n -= k) {
    res *= n;
  }

  printf("%lld\n", res);

  return 0;
}
