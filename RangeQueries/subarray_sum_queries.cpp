#include <bits/stdc++.h>

#define ll long long int
#define pi pair<ll, ll>
#define rep(idx, start, stop) for(int idx = start; idx < stop; idx++)
#define pre(idx, start, stop) for(int idx = start; idx >= stop; idx--)

const ll mod = 1e9+7;

using namespace std;

void solve();

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    solve();
}

void segTreeUpdate(vector<pair<pi, pi>>& segTree, int idx, pair<pi, pi> value, int tl, int tr, int v)
{
    if (tl == tr)
    {
        if (tl == idx) segTree[v] = value;
        return;
    }
    int tm = ((tl + tr)/ 2);
    if (idx >= tl && idx <= tm)
    {
        segTreeUpdate(segTree, idx, value, tl, tm, 2*v+1);
    }
    if (idx <= tr && idx >= (tm +1))
    {
        segTreeUpdate(segTree, idx, value, tm+1, tr, 2*v+2);
    }
    ll sm1 = segTree[2*v+1].first.first;
    ll em1 = segTree[2*v+1].first.second;
    ll m1 = segTree[2*v+1].second.first;
    ll t1 = segTree[2*v+1].second.second;
    ll sm2 = segTree[2*v+2].first.first;
    ll em2 = segTree[2*v+2].first.second;
    ll m2 = segTree[2*v+2].second.first;
    ll t2 = segTree[2*v+2].second.second;
    segTree[v] = {{max(max(sm1, t1+sm2), t1+t2), max(max(em2, em1+t2), t1+t2)}, 
                    {max(max(m1, m2), em1+sm2), t1+t2}};
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<ll> arr(n);
    vector<pair<pi, pi>> segTree(4*n+1, {{0, 0}, {0, 0}});
    rep(i, 0, n)
    {
        cin >> arr[i];
        segTreeUpdate(segTree, i, {{arr[i], arr[i]}, {arr[i], arr[i]}}, 0, n-1, 0);
    }
    rep(i, 0, m)
    {
        int k, x;
        cin >> k >> x;
        --k;
        segTreeUpdate(segTree, k, {{x, x}, {x, x}}, 0, n-1, 0);
        cout << max(segTree[0].second.first, 0ll) << '\n';
    }
    return;
}