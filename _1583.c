#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef M_PI
long double M_PI;
#define SET_M_PI_VALUE
#endif

#define MAX_N 100
#define PIECE_WEIGHT 500
#define EPS 1e-10

struct sphere {
  long double x, y, z, r;
};

int n;
struct sphere spheres[MAX_N];

long double slice(long double r, long double y) {
  return M_PI * (r * r * y - y * y * y / 3);
}

long double contained_volume(struct sphere s, long double y) {
  if ((s.y + s.r) < y) {
    return 4 * M_PI * s.r * s.r * s.r / 3;
  } else if (s.y > y) {
    return 2 * M_PI * s.r * s.r * s.r / 3 - slice(s.r, s.y + s.r - y);
  } else {
    return 2 * M_PI * s.r * s.r * s.r / 3 + slice(s.r, y - s.y);
  }
}

long double total_weight(long double y) {
  long double weight = 10 * 10 * y;
  int i;

  if (y < EPS) {
    return 0;
  }

  for (i = 0; i < n; ++i) {
    if ((spheres[i].y - spheres[i].r) < y) {
      weight -= contained_volume(spheres[i], y);
    }
  }

  return weight;
}

int main(void) {
  int i, pieces, cuts;
  long double weight = 10 * 10 * 100;
  long double factor = 4 * M_PI / 3;
  long double low = 0, last_low;
  long double upp = 0;
  long double left_over;
  long double u, l, l0;

#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
  freopen("output", "w", stdout);
#endif

#ifdef SET_M_PI_VALUE
  M_PI = 2.0 * acos(0.0);
#endif

  scanf("%d", &n);
  for (i = 0; i < n; ++i) {
    scanf("%Lf%Lf%Lf%Lf",
          &spheres[i].x,
          &spheres[i].y,
          &spheres[i].z,
          &spheres[i].r);
    weight -= factor * spheres[i].r * spheres[i].r * spheres[i].r;
  }

  pieces = weight / PIECE_WEIGHT;
  left_over = weight - PIECE_WEIGHT * pieces; 
  if (abs(left_over) < EPS) {
    cuts = pieces - 1;
  } else {
    cuts = pieces;
  }

  printf("%d\n", cuts);

  for (i = 0; i < cuts; ++i) {
    upp = 100;
    last_low = low;
    while (fabs(upp - low) > EPS) {
      long double mid = (low + upp) / 2;

      if ((total_weight(mid) - total_weight(last_low)) <= PIECE_WEIGHT) {
        low = mid;
      } else {
        upp = mid;
      }
    }

    l0 = low * 10000;
    l = floor(l0);
    u = ceil(l0);

    if (fabs(u - l0) <= 0.5) {
      printf("%d\n", (int) u);
    } else {
      printf("%d\n", (int) l);
    }
  }


  return 0;
}
