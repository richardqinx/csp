#include <bits/stdc++.h>
using namespace std;

int64_t K;


class KarySegmentTree {
private:
    struct Node
    {
        int64_t s1;
        int64_t s2;
        int64_t s3;
        int64_t s4;
        int64_t len;
        int64_t tag;
    };

    int64_t K;
    int n;
    vector<Node> tree;

    int64_t add_k(int64_t a, int64_t b)
    {
        int64_t res = 0, p = 1;
        while (a > 0 || b > 0)
        {
            int64_t d1 = a % K;
            int64_t d2 = b % K;
            res += ((d1 + d2) % K) * p;
            a /= K;
            b /= K;
            p *= K;
        }
        return res;
    }

    int64_t mul_k(int64_t a, int64_t c)
    {
        c = (c % K + K) % K;
        if (c == 0){
            return 0;
        }
        int64_t res = 0, p = 1;
        while (a > 0)
        {
            int64_t d = a % K;
            res += ((d * c) % K) * p;
            a /= K;
            p *= K;
        }
        return res;
    }

    void pushUp(int p) {
        tree[p].s1 = add_k(tree[2 * p].s1, tree[2 * p + 1].s1);
        tree[p].s2 = add_k(tree[2 * p].s2, tree[2 * p + 1].s2);
        tree[p].s3 = (tree[2 * p].s3 + tree[2 * p + 1].s3) % K;
        tree[p].s4 = (tree[2 * p].s4 + tree[2 * p + 1].s4) % K;
    }

    void applyTag(int p, int64_t v) {
        int64_t v0 = v % K;
        int64_t vhi = v - v0;
        int64_t len = tree[p].len % K;

        int64_t P1 = mul_k(tree[p].s2, v0);
        int64_t P2 = mul_k(vhi, tree[p].s3);
        int64_t P3 = mul_k(vhi, (len * v0) % K);
        tree[p].s1 = add_k(tree[p].s1, add_k(P1, add_k(P2, P3)));
        tree[p].s2 = add_k(tree[p].s2, mul_k(vhi, len));
        int64_t term1 = (tree[p].s3 * v0) % K;
        int64_t term2 = (len * ((v0 * (v0 + 1) / 2) % K)) % K;
        tree[p].s4 = (tree[p].s4 + term1 + term2) % K;
        tree[p].s3 = (tree[p].s3 + len * v0) % K;
        tree[p].tag = add_k(tree[p].tag, v);
    }

    void pushDown(int p) {
        if (tree[p].tag != 0)
        {
            applyTag(2 * p, tree[p].tag);
            applyTag(2 * p + 1, tree[p].tag);
            tree[p].tag = 0;
        }
    }

    void build(int p, int l, int r, const vector<int64_t> &arr)
    {
        tree[p].len = r - l + 1;
        tree[p].tag = 0;
        if (l == r)
        {
            int64_t a0 = arr[l] % K;
            int64_t ahi = arr[l] - a0;
            tree[p].s1 = mul_k(ahi, a0);
            tree[p].s2 = ahi;
            tree[p].s3 = a0;
            tree[p].s4 = (a0 * (a0 + 1) / 2) % K;
            return;
        }
        int mid = l + (r - l) / 2;
        build(2 * p, l, mid, arr);
        build(2 * p + 1, mid + 1, r, arr);
        pushUp(p);
    }

    void updateInternal(int p, int l, int r, int ql, int qr, int64_t v)
    {
        if (ql <= l && r <= qr)
        {
            applyTag(p, v);
            return;
        }
        pushDown(p);
        int mid = l + (r - l) / 2;
        if (ql <= mid){
            updateInternal(2 * p, l, mid, ql, qr, v);
        }
        if (qr > mid){
            updateInternal(2 * p + 1, mid + 1, r, ql, qr, v);
        }
        pushUp(p);
    }

    Node queryInternal(int p, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr){
            return tree[p];
        }
        pushDown(p);
        int mid = l + (r - l) / 2;
        if (qr <= mid){
            return queryInternal(2 * p, l, mid, ql, qr);
        }
        if (ql > mid){
            return queryInternal(2 * p + 1, mid + 1, r, ql, qr);
        }

        Node leftNode = queryInternal(2 * p, l, mid, ql, qr);
        Node rightNode = queryInternal(2 * p + 1, mid + 1, r, ql, qr);

        Node res;
        res.s1 = add_k(leftNode.s1, rightNode.s1);
        res.s2 = add_k(leftNode.s2, rightNode.s2);
        res.s3 = (leftNode.s3 + rightNode.s3) % K;
        res.s4 = (leftNode.s4 + rightNode.s4) % K;
        return res;
    }

public:
    KarySegmentTree(int size, int64_t k_val, const vector<int64_t> &arr)
    {
        n = size;
        K = k_val;
        tree.resize(4 * n + 1);
        build(1, 1, n, arr);
    }

    void modify(int l, int r, int64_t v)
    {
        updateInternal(1, 1, n, l, r, v);
    }

    int64_t query(int l, int r)
    {
        Node ans_node = queryInternal(1, 1, n, l, r);
        return add_k(add_k(ans_node.s1, ans_node.s2), ans_node.s4);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int64_t n;
    int64_t m;
    int64_t K;
    cin >> n >> m >> K;
    vector<int64_t> arr(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }

    KarySegmentTree KSTree(n, K, arr);
    int t;
    while (m--)
    {
        cin >> t;
        if (t == 1) {
            int64_t l, r, v;
            cin >> l >> r >> v;
            KSTree.modify(l, r, v);
        } else if (t == 2) {
            int l, r;
            cin >> l >> r;
            int64_t res = KSTree.query(l ,r);
            cout << res << "\n";
        }
    }
    return 0;
}