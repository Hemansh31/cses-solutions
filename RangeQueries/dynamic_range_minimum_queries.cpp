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

void streeUpdate(vector<int>& stree, int idx, int value, int tl, int tr, int v)
{
    if ((tl == tr) && (idx == tl))
    {
        stree[v] = value;
        return;
    }
    int tm = (tl + tr) / 2;
    if (idx >= tl && idx <= tm)
    {
        streeUpdate(stree, idx, value, tl, tm, 2*v+1);
    }
    if (idx <= tr && idx >= (tm + 1))
    {
        streeUpdate(stree, idx, value, tm+1, tr, 2*v+2);
    }
    stree[v] = min(stree[2*v+1], stree[2*v+2]);
}

int streeQuery(vector<int>& stree, int l, int r, int tl, int tr, int v)
{
    if ((l <= tl) && (r >= tr))
    {
        return stree[v];
    }
    int tm = (tl + tr) / 2;
    int answer = -1;
    if (!((l > tm) || (r < tl)))
    {
        answer = streeQuery(stree, l, r, tl, tm, 2*v+1);
    }
    if (!((tm+1 > tr) || (r < tm+1) || (l > tr)))
    {
        int tmp = streeQuery(stree, l, r, tm+1, tr, 2*v+2);
        answer = (answer == -1) ? tmp : min(answer, tmp);
    }
    return answer;
}

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    rep(i, 0, n) cin >> arr[i];
    vector<int> stree(4*n+4, 0);
    rep(i, 0, n)
    {
        streeUpdate(stree, i, arr[i], 0, n-1, 0);
    }

    rep(i, 0, q)
    {
        int code, a, b;
        cin >> code >> a >> b;
        switch (code)
        {
        case 1:
            streeUpdate(stree, a-1, b, 0, n-1, 0);
            arr[a-1] = b;
            break;
        case 2:
            cout << streeQuery(stree, a-1, b-1, 0, n-1, 0) << '\n';
            break;
        }
    }
}