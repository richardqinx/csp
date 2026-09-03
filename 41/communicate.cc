#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = (1LL << 60);

struct Interface {
  ll start;
  int L;
  int pos;
};

map<ll, ll> free_by_pos = {{0, INF}};
set<pair<ll, ll>> free_by_len = {{INF + 1, 0}};

vector<vector<Interface>> procs;

void add_free(ll left, ll right) {
  free_by_pos[left] = right;
  free_by_len.insert({right - left + 1, left});
}

void remove_free(ll left, ll right) {
  free_by_pos.erase(left);
  free_by_len.erase({right - left + 1, left});
}

ll allocate(int L) {
  auto it = free_by_len.lower_bound({L, -1});

  ll len = it->first;
  ll left = it->second;
  ll right = free_by_pos[left];

  remove_free(left, right);

  if (left + L <= right) {
    add_free(left + L, right);
  }
  return left;
}

void release(ll left, ll right) {
  auto it = free_by_pos.lower_bound(left);

  if (it != free_by_pos.begin()) {
    auto pre = prev(it);

    if (pre->second + 1 == left) {
      ll new_left = pre->first;
      ll new_right = pre->second;

      remove_free(new_left, new_right);

      left = new_left;
    }
  }

  it = free_by_pos.lower_bound(left);

  if (it != free_by_pos.end() && right + 1 == it->first) {
    ll new_left = it->first;
    ll new_right = it->second;

    remove_free(new_left, new_right);

    right = new_right;
  }

  add_free(left, right);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  int q;
  cin >> n >> q;

  procs.assign(n + 1, {});

  string oprand;

  while (q--) {
    cin >> oprand;
    if (oprand == "new") {
      int p;
      int L;
      cin >> p >> L;
      ll start = allocate(L);

      procs[p].push_back({start, L, 0});

      cout << start << '\n';
    } else if (oprand == "send") {
      int p;
      cin >> p;

      ll ans = 0;

      for (auto &itf : procs[p]) {
        ll address = itf.start + itf.pos;

        ans += address;

        ++itf.pos;
        if (itf.pos == itf.L) {
          itf.pos = 0;
        }
      }

      cout << ans << '\n';
    } else {
      int p;
      int i;
      cin >> p >> i;

      --i;

      auto itf = procs[p][i];

      release(itf.start, itf.start + itf.L - 1);

      procs[p].erase(procs[p].begin() + i);
    }
  }
  return 0;
}
