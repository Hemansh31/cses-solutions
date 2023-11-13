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

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n, vector<int> (0));
    vector<vector<int>> Adj(n, vector<int> (0));
    vector<int> outdegree(n, 0);
    rep(i, 0, m)
    {
        int a, b;
        cin >> a >> b;
        outdegree[a-1]++;
        adj[b-1].push_back(a-1);
        Adj[a-1].push_back(b-1);
    }
    vector<int> level(n, n);
    vector<ll> dp(n, 0);
    dp[n-1] = 1;
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
        rep(i, 0, Adj[node].size())
        {
            dp[node] += dp[Adj[node][i]];
            dp[node] %= mod;
        }
    }
    cout << dp[0] << '\n';
}