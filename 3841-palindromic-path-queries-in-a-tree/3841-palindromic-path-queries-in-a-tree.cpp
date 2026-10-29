
#include <bits/stdc++.h>
using namespace std;

class Solution {
    vector<vector<int>> adj;
    vector<int> parent, depth, sz, heavy;
    vector<int> head, pos;
    vector<int> seg;
    int timer = 0;

    // XOR segment tree
    void build(int node, int l, int r, vector<int>& arr) {
        if (l == r) {
            seg[node] = arr[l];
            return;
        }

        int mid = (l + r) / 2;
        build(node * 2, l, mid, arr);
        build(node * 2 + 1, mid + 1, r, arr);

        seg[node] = seg[node * 2] ^ seg[node * 2 + 1];
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            seg[node] = val;
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, val);
        else
            update(node * 2 + 1, mid + 1, r, idx, val);

        seg[node] = seg[node * 2] ^ seg[node * 2 + 1];
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return 0;

        if (ql <= l && r <= qr)
            return seg[node];

        int mid = (l + r) / 2;

        return query(node * 2, l, mid, ql, qr) ^
               query(node * 2 + 1, mid + 1, r, ql, qr);
    }

    // Character to 26-bit mask
    int getMask(char c) {
        return 1 << (c - 'a');
    }

    // XOR mask of all characters on path u -> v
    int pathQuery(int u, int v, int n) {
        int mask = 0;

        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);

            mask ^= query(
                1, 0, n - 1,
                pos[head[u]], pos[u]
            );

            u = parent[head[u]];
        }

        if (depth[u] > depth[v])
            swap(u, v);

        mask ^= query(
            1, 0, n - 1,
            pos[u], pos[v]
        );

        return mask;
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        adj.assign(n, {});

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        parent.assign(n, -1);
        depth.assign(n, 0);
        sz.assign(n, 1);
        heavy.assign(n, -1);

        // 1. Build parent, depth and traversal order iteratively
        vector<int> order = {0};

        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];

            for (int v : adj[u]) {
                if (v == parent[u])
                    continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                order.push_back(v);
            }
        }

        // 2. Calculate subtree sizes and heavy child
        for (int i = n - 1; i >= 0; i--) {
            int u = order[i];
            int maxSize = 0;

            for (int v : adj[u]) {
                if (parent[v] != u)
                    continue;

                sz[u] += sz[v];

                if (sz[v] > maxSize) {
                    maxSize = sz[v];
                    heavy[u] = v;
                }
            }
        }

        // 3. Heavy-Light Decomposition
        head.assign(n, 0);
        pos.assign(n, 0);

        vector<pair<int, int>> st = {{0, 0}};
        vector<int> arr(n);
        timer = 0;

        while (!st.empty()) {
            auto [start, h] = st.back();
            st.pop_back();

            for (int u = start; u != -1; u = heavy[u]) {
                head[u] = h;
                pos[u] = timer;
                arr[timer++] = getMask(s[u]);

                for (int v : adj[u]) {
                    if (parent[v] == u && v != heavy[u])
                        st.push_back({v, v});
                }
            }
        }

        // 4. Build segment tree
        seg.assign(4 * n, 0);
        build(1, 0, n - 1, arr);

        vector<bool> ans;

        // 5. Process queries
        for (string& q : queries) {
            string type;
            int u, v;
            char c;

            stringstream ss(q);
            ss >> type;

            if (type == "update") {
                ss >> u >> c;

                s[u] = c;

                update(
                    1, 0, n - 1,
                    pos[u],
                    getMask(c)
                );
            } else {
                ss >> u >> v;

                int mask = pathQuery(u, v, n);

                // True if at most one bit is set
                ans.push_back(
                    (mask & (mask - 1)) == 0
                );
            }
        }

        return ans;
    }
};
