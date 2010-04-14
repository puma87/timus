#include <cstdio>
#include <vector>

using std::vector;

const int kMaxN = 1000;
const int kMaxM = 100001;

int n, m, a, b;
vector<int> route_stations[kMaxN];
vector<int> station_routes[kMaxM];
int available_stations[kMaxM];
int queue[kMaxN], queue_low, queue_upp;
int father[kMaxN], connect[kMaxN];
int used[kMaxN];

bool element_contained(vector<int> array, int elem) {
  for (vector<int>::iterator it = array.begin(); it != array.end(); ++it) {
    if (*it == elem) {
      return true;
    }
  }

  return false;
}

void print_solution(int qi, int cnt) {
  if (qi == -1) {
    printf("%d\n", cnt);
  } else {
    print_solution(father[qi], cnt + 1);
    printf("%d ", (father[qi] == -1) ? a : connect[qi]);
  }
}

int main(void) {
  int i;

#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
  freopen("output", "w", stdout);
#endif

  scanf("%d%d", &n, &m);
  for (i = 0; i < n; ++i) {
    int kn, kv, k;

    scanf("%d", &kn);
    for (k = 0; k < kn; ++k) {
      scanf("%d", &kv);
      route_stations[i].push_back(kv);
      station_routes[kv].push_back(i);
      available_stations[kv] = 1;
    }
  }
  scanf("%d%d", &a, &b);

  for (vector<int>::iterator it = station_routes[a].begin();
       it != station_routes[a].end();
       ++it) {
    father[queue_upp] = -1;
    connect[queue_upp] = -1;
    queue[queue_upp++] = *it;
    used[*it] = 1;
  }
  available_stations[a] = 0;

  for (; queue_low < queue_upp; ++queue_low) {
    int station = queue[queue_low];

    if (element_contained(route_stations[station], b)) {
      print_solution(queue_low,
                     (element_contained(route_stations[station], a)) ? -1 : 0);
      if (connect[queue_low] != b) {
        printf("%d\n", b);
      }
      return 0;
    }

    for (vector<int>::iterator it = route_stations[station].begin();
         it != route_stations[station].end();
         ++it) {
      if (available_stations[*it]) {
        for (vector<int>::iterator itr = station_routes[*it].begin();
             itr != station_routes[*it].end();
             ++itr) {
          if (!used[*itr]) {
            connect[queue_upp] = *it;
            father[queue_upp] = queue_low;
            queue[queue_upp++] = *itr;
            used[*itr] = 1;
          }
        }
        available_stations[*it] = 0;
      }
    }
  }

  printf("-1\n");

  return 0;
}
