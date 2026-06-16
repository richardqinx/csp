#include <bits/stdc++.h>
#include <cstdint>
using namespace std;

uint64_t n, k, m;

bool can_live(uint64_t robot_num) {
  uint64_t total_apple = n;
  for (int day = 1; day <= m; ++day) {
    uint64_t rot = (total_apple * k + 99) / 100;
    total_apple -= rot;
    if (total_apple < robot_num) {
      return false;
    }
    total_apple -= robot_num;
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> k >> m;

  uint64_t left = 0;
  uint64_t right = n / m;
  uint64_t res = 0;

  while (left <= right) {
    uint64_t mid = left + (right - left) / 2;
    if (can_live(mid)) {
      res = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  cout << res << "\n";
  return 0;
}
