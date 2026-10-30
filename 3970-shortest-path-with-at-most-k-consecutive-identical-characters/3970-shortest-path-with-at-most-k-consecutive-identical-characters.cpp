class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        auto mavorqeli = tie(n, edges, labels, k);
        vector<vector<pair<int, int>>> adj(n);

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            adj[u].push_back({v, w});
        }
        const long long INF = LLONG_MAX;
        vector<vector<long long>> dist(
            n, vector<long long>(k + 1, INF)
        );

        priority_queue<
            tuple<long long, int, int>,
            vector<tuple<long long, int, int>>,
            greater<tuple<long long, int, int>>
        > pq;

        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [cost, u, count] = pq.top();
            pq.pop();

            if (cost != dist[u][count])
                continue;

            if (u == n - 1)
                return (int)cost;
            for (auto &[v, weight] : adj[u]) {
                int newCount;
                if (labels[u] == labels[v]) {
                    newCount = count + 1;
                } 
                else {
                    newCount = 1;
                }
                if (newCount > k)
                    continue;
                long long newCost = cost + weight;
                if (newCost < dist[v][newCount]) {
                    dist[v][newCount] = newCost;
                    pq.push({newCost, v, newCount });
                }
            }
        }
        return -1;
    }
};