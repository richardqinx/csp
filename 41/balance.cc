#include <bits/stdc++.h>
using namespace std;

bool is_balance(int a) {
    int one_num = 0;
    int zero_num = 0;
    while (a != 0)
    {
        if ((a & 1) == 0) {
            zero_num++;
        } else {
            one_num++;
        }
        a = a >> 1;
    }
    if (one_num == zero_num) {
        return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (is_balance(a[i])) {
            cnt++;
        }
    }
    cout << cnt << endl;
    return 0;
}