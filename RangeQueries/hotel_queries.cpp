#include <bits/stdc++.h>

#define ll long long int
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

void segTreeUpdate(vector<int>& segTree, int idx, int value, int tl, int tr, int v)
{
    if ((tl == tr))
    {
        if (tl == idx) segTree[v] = value;
        return;
    }
    int tm = (tl + tr) / 2;
    if (idx >= tl && idx <= tm)
    {
        segTreeUpdate(segTree, idx, value, tl, tm, 2*v+1);
    }
    if (idx <= tr && idx >= (tm+1))
    {
        segTreeUpdate(segTree, idx, value, tm+1, tr, 2*v+2);
    }
    if (tl < tr) segTree[v] = max(segTree[2*v+1], segTree[2*v+2]);
}

int segTreeQuery(vector<int>& segTree, int tl, int tr, int v, int group)
{
    if (segTree[v] < group) return 0;
    if ((tl == tr)) return tl+1;
    int tm = (tl + tr)/2;
    if (segTree[2*v+1] >= group) return segTreeQuery(segTree, tl, tm, 2*v+1, group);
    return segTreeQuery(segTree, tm+1, tr, 2*v+2, group);
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> freeRooms(n);
    vector<int> segTree(4*n+1, 0);
    rep(i, 0, n)
    {
        cin >> freeRooms[i];
        segTreeUpdate(segTree, i, freeRooms[i], 0, n-1, 0);
    }
    rep(i, 0, m)
    {
        int group;
        cin >> group;
        int idx = segTreeQuery(segTree, 0, n-1, 0, group);
        cout << idx << ' ';
        if (idx > 0) segTreeUpdate(segTree, idx-1, freeRooms[idx-1] -= group, 0, n-1, 0);
    }
}