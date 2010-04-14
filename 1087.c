#include <stdio.h>
#include <string.h>

#define MAX_N 10001
#define MAX_M 50

int n, m, k[MAX_M];
int best[2][MAX_N];

int main(void) {
  int i, j, l;

#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
  freopen("output", "w", stdout);
#endif

  scanf("%d%d", &n, &m);
  for (i = 0; i < m; ++i) {
    scanf("%d", &k[i]);
  }

  memset(best, 0xff, sizeof(best));

  for (i = 0; i < m; ++i) {
    if (k[i] <= n) {
      best[0][k[i]] = 1;
      best[1][k[i]] = 0;
    }
  }

  for (i = 1; i <= n; ++i) {
    for (j = 0; j < 2; ++j) {
      int wins = 0;

      for (l = 0; l < m; ++l) {
        if ((i - k[l]) > 0 && best[1 - j][i - k[l]] == j) {
          wins = 1;
          break;
        }
      }

      best[j][i] = (wins) ? j : (1 - j);
    }
  }

  printf("%d\n", (best[0][n] == 0) ? 1 : 2);

  return 0;
}
