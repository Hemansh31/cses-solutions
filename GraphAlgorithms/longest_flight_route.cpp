#include <bits/stdc++.h>

#define ll long long int
#define pi pair<int, int>
#define pl pair<ll, ll>
#define rep(idx, start, stop) for(int idx = start; idx < stop; idx++)
#define pre(idx, start, stop) for(int idx = start; idx >= stop; idx--)

const ll mod = 1e9+7;

using namespace std;

void solve();

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    solve();
}

void dfs(int node, vector<vector<pi>>& Adj, vector<int>& dist, vector<bool>& visited, vector<int>& parent)
{
    visited[node] = true;
    rep(i, 0, Adj[node].size())
    {
        if (!visited[Adj[node][i].second])
        {
            parent[Adj[node][i].second] = node;
            dist[Adj[node][i].second] = dist[node] + 1;
            dfs(Adj[node][i].second, Adj, dist, visited, parent);
        }
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n, vector<int> (0));
    vector<int> outdegree(n, 0);
    rep(i, 0, m)
    {
        int a, b;
        cin >> a >> b;
        adj[--b].push_back(--a);
        outdegree[a]++;
    }
    vector<int> level(n, n);
    queue<int> Queue;
    rep(i, 0, n)
    {
        if (outdegree[i] == 0)
        {
            Queue.push(i);
        }
    }
    while(!Queue.empty())
    {
        int node = Queue.front();
        Queue.pop();
        rep(i, 0, adj[node].size())
        {
            outdegree[adj[node][i]]--;
            if (outdegree[adj[node][i]] == 0)
            {
                level[adj[node][i]] = level[node] - 1;
                Queue.push(adj[node][i]);
            }
        }
    }
    vector<int> dist(n, 0);
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    vector<vector<pi>> Adj(n, vector<pi> (0));
    rep(i, 0, n)
    {
        rep(j, 0, adj[i].size())
        {
            Adj[adj[i][j]].push_back({level[i], i});
        }
    }
    rep(i, 0, n)
    {
        sort(Adj[i].begin(), Adj[i].end());
    }
    dfs(0, Adj, dist, visited, parent);
    if (!visited[n-1])
    {
        cout << "IMPOSSIBLE\n";
    }
    else
    {
        vector<int> path;
        int node = n-1;
        while(node != -1)
        {
            path.push_back(node);
            node = parent[node];
        }
        reverse(path.begin(), path.end());
        cout << path.size() << '\n';
        rep(i, 0, path.size()) cout << path[i] + 1 << ' ';
        cout << '\n';
    }
}