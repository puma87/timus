#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int d, e, f, dp, ep, h;
  int low, len;

#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
  freopen("output", "w", stdout);
#endif

  scanf("%d%d%d%d%d%d", &d, &e, &f, &dp, &ep, &h);
  --dp;
  --ep;

  low = (d < e) ? d : e;
  d -= low;
  e -= low;
  dp >>= low;
  ep >>= low;

  if (dp == ep) {
    len = abs(d - e);
  } else {
    int max, i;

    for (i = 0; i < 32; ++i) {
      if ((dp & (1 << i)) != (ep & (1 << i))) {
        max = i;
      }
    }

    ++max;
    len = abs(max - d) + abs(max - e);
  }

  printf("%s\n", (len <= h) ? "YES" : "NO");

  return 0;
}
