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

void fUpdate(vector<ll>& ftree, int idx, int value)
{
    for(; idx < ftree.size(); idx = (idx | (idx + 1)))
    {
        ftree[idx] += value;
    }
}

ll fSum(vector<ll>& ftree, int r)
{
    ll answer = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
    {
        answer += ftree[r];
    }
    return answer;
}

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    rep(i, 0, n) cin >> arr[i];
    vector<ll> ftree(n, 0);
    rep(i, 0, q)
    {
        int code, a, b, u, k;
        cin >> code;
        switch (code)
        {
        case 1:
            cin >> a >> b >> u;
            fUpdate(ftree, a-1, u);
            fUpdate(ftree, b, -u);
            break;        
        case 2:
            cin >> k;
            cout << arr[k-1] + fSum(ftree, k-1) << '\n';
            break;
        }
    }
    
}