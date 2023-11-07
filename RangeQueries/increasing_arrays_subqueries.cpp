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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    solve();
}

void segTreeCreate(vector<vector<pi>>& segTree, int tl, int tr, int v, vector<ll>& arr)
{
    if (tr < tl) return;
    if (tl == tr)
    {
        segTree[v] = {{0, 0}, {arr[tl], arr[tl]}};
        return;
    }
    int tm = (tl + tr)/2;
    segTreeCreate(segTree, tl, tm, 2*v+1, arr);
    segTreeCreate(segTree, tm+1, tr, 2*v+2, arr);
    segTree[v] = vector<pi> (tr - tl + 2);
    segTree[v][0] = {segTree[2*v+1][0].first + segTree[2*v+2][0].first, 0};
    int idx = 1;
    int idx2 = 1;
    while(idx < segTree[2*v+1].size())
    {
        segTree[v][idx2++] = segTree[2*v+1][idx++]; 
    }
    idx = 1;
    while(idx < segTree[2*v+2].size())
    {
        if (segTree[2*v+2][idx].first < segTree[v][idx2-1].first)
        {
            segTree[v][0].first += (segTree[v][idx2-1].first - segTree[2*v+2][idx].first);
            segTree[v][idx2] = {segTree[v][idx2-1].first, segTree[v][idx2-1].second + segTree[v][idx2-1].first}; 
        }   
        else
        {
            segTree[v][idx2] = {segTree[2*v+2][idx].first, segTree[v][idx2-1].second + segTree[2*v+2][idx].first}; 
        }
        idx++;
        idx2++;
    }
}

pi segTreeQuery(vector<vector<pi>>& segTree, int tl, int tr, int v, int l, int r)
{
    if ((l > r) || (tl > tr)) return {0, 0};
    if ((l > tr) || (r < tl)) return {0, 0};
    if ((tl == tr))
    {
        return {segTree[v][0].first, segTree[v][1].second};
    }
    if ((l <= tl) && (r >= tr))
    {
        return {segTree[v][0].first, segTree[v][segTree[v].size()-1].first};
    }
    int tm = (tl + tr)/2;
    pi leftResult = segTreeQuery(segTree, tl, tm, 2*v+1, l, r);
    pi rightResult = segTreeQuery(segTree, tm+1, tr, 2*v+2, l, r);
    if (rightResult.second == 0) return leftResult;
    if (leftResult.second == 0) return rightResult;
    pi srch = {leftResult.second, segTree[0][segTree[0].size()-1].second};
    int tmp = lower_bound(segTree[2*v+2].begin()+1, segTree[2*v+2].end(), srch) - segTree[2*v+2].begin();
    if (tmp == 1) return {leftResult.first + rightResult.first, rightResult.second};
    else if (tmp > (min(r, tr) - tm)) 
    {
        ll maxi = leftResult.second;
        ll steps = leftResult.first + rightResult.first + (maxi * (min(r, tr) - tm)) - segTree[2*v+2][(min(r, tr) - tm)].second;
        return {steps, maxi};
    }
    else
    {
        ll maxi = max(leftResult.second, rightResult.second);
        ll steps = leftResult.first + rightResult.first + (leftResult.second * (tmp-1)) - segTree[2*v+2][(tmp-1)].second;
        return {steps, maxi};
    }
}

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<ll> arr(n);
    rep(i, 0, n) cin >> arr[i];
    vector<vector<pi>> segTree(4*n+4);
    segTreeCreate(segTree, 0, n-1, 0, arr);
    rep(i, 0, q)
    {
        int a, b;
        cin >> a >> b;
        cout << segTreeQuery(segTree, 0, n-1, 0, a-1, b-1).first << '\n';
    }
}