#include <bits/stdc++.h>

#define rep(idx, start, stop) for(int idx = start; idx < stop; ++idx)
#define pre(idx, start, stop) for(int idx = start; idx >= stop; --idx)

typedef long long int ll;

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

void fenwickAdd(vector<ll>& bit, int idx, int incrmt)
{
    for(; idx < bit.size(); idx |= (idx + 1))
    {
        bit[idx] += incrmt;
    }
}

ll fenwickSum(vector<ll>& bit, int idx)
{
    ll answer = 0;
    for(; idx >= 0; (idx &= (idx + 1))--)
    {
        answer += bit[idx];
    }
    return answer;
}

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<ll> arr(n);
    rep(i, 0, n) cin >> arr[i];
    vector<ll> bit(n, 0);
    rep(i, 0, n) fenwickAdd(bit, i, arr[i]);
    rep(i, 0, q)
    {
        ll code, a, b;
        cin >> code >> a >> b;
        switch (code)
        {
        case 1:
            fenwickAdd(bit, a-1, b - arr[a-1]);
            arr[a-1] = b;
            break;
        case 2:
            cout << fenwickSum(bit, b-1) - fenwickSum(bit, a-2) << '\n';
            break;
        }
    }
}