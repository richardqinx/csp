#include <bits/stdc++.h>
#include <utility>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  double num;
  int a;
  int b;

  vector<int> ans_1(n);
  vector<int> ans_2(n);

  for (int i = 0; i < n; ++i) {
    cin >> num;
    a = static_cast<int>(num);
    b = static_cast<int>(num * 10) % 10;
    if (b <= 4) {
      ans_1[i] = ans_2[i] = a;
    } else if (b == 5) {
      ans_1[i] = a + 1;
      if (a % 2 == 0) {
        ans_2[i] = a;
      } else {
        ans_2[i] = a + 1;
      }
    } else if (b >= 6 && b <= 9) {
      ans_1[i] = ans_2[i] = a + 1;
    }
  }
  for (int i = 0; i < n; ++i) {
    cout << ans_1[i] << (i != n - 1 ? " " : "\n");
  }
  for (int i = 0; i < n; ++i) {
    cout << ans_2[i] << (i != n - 1 ? " " : "\n");
  }
}
