#include <bits/stdc++.h>
using namespace std;

// 无向图
struct Graph {
    int n;
    vector<vector<int>> adj;
    explicit Graph(int n) : n(n), adj(n + 1) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};

//Kruskal
struct DSU {
    vector<int> p, sz;
    explicit DSU(int n) : p(n + 1), sz(n + 1, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b];
        return true;
    }
};

struct Edge {
    int u, v, w;
};

// 深度优先
vector<int> dfs(const Graph& g, int start) {
    vector<int> order;
    vector<int> vis(g.n + 1, 0);
    function<void(int)> go = [&](int u) {
        vis[u] = 1;
        order.push_back(u);
        for (int v : g.adj[u]) if (!vis[v]) go(v);
    };
    go(start);
    return order;
}

// 广度优先
vector<int> bfs(const Graph& g, int start) {
    vector<int> order;
    vector<int> vis(g.n + 1, 0);
    queue<int> q;
    vis[start] = 1; q.push(start);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : g.adj[u]) if (!vis[v]) {
            vis[v] = 1;
            q.push(v);
        }
    }
    return order;
}

// Prim
pair<bool, long long> prim(int n, const vector<vector<pair<int, int>>>& g) {
    vector<int> vis(n + 1, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vis[1] = 1;
    for (auto [to, w] : g[1]) pq.push({w, to});
    long long total = 0;
    int cnt = 1;
    while (!pq.empty() && cnt < n) {
        auto [w, v] = pq.top(); pq.pop();
        if (vis[v]) continue;
        vis[v] = 1;
        total += w;
        ++cnt;
        for (auto [to, w2] : g[v]) if (!vis[to]) pq.push({w2, to});
    }
    return {cnt == n, cnt == n ? total : -1};
}

// Kruskal
pair<bool, long long> kruskal(int n, vector<Edge> edges) {
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    DSU dsu(n);
    long long total = 0;
    int cnt = 0;
    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            total += e.w;
            if (++cnt == n - 1) break;
        }
    }
    return {cnt == n - 1, cnt == n - 1 ? total : -1};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;

    Graph g(n);
    vector<vector<pair<int, int>>> wg(n + 1);
    vector<Edge> edges;
    edges.reserve(m);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v);
        wg[u].push_back({v, w});
        wg[v].push_back({u, w});
        edges.push_back({u, v, w});
    }

    for (int i = 1; i <= n; ++i) sort(g.adj[i].begin(), g.adj[i].end());

    int start = 1;
    auto dfs_order = dfs(g, start);
    auto bfs_order = bfs(g, start);
    auto prim_res = prim(n, wg);
    auto kruskal_res = kruskal(n, edges);

    auto print_order = [](const vector<int>& ord) {
        for (size_t i = 0; i < ord.size(); ++i) {
            if (i) cout << ' ';
            cout << ord[i];
        }
        cout << '\n';
    };

    cout << "DFS order: ";
    print_order(dfs_order);
    cout << "BFS order: ";
    print_order(bfs_order);

    cout << "Prim MST: ";
    if (prim_res.first) cout << prim_res.second << '\n';
    else cout << "Graph not connected\n";

    cout << "Kruskal MST: ";
    if (kruskal_res.first) cout << kruskal_res.second << '\n';
    else cout << "Graph not connected\n";

    return 0;
}

