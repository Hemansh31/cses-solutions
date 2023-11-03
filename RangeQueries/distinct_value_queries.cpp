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

void segTreeCreate(vector<int>& endings, vector<vector<int>>& segTree, int tl, int tr, int v)
{
    if (tr < tl) return;
    if (tl == tr)
    {
        segTree[v] = {endings[tl]};
        return;
    }
    int tm = (tl + tr)/2;
    segTreeCreate(endings, segTree, tl, tm, 2*v+1);
    segTreeCreate(endings, segTree, tm+1, tr, 2*v+2);
    segTree[v] = vector<int> (tr - tl + 1);
    int idx1 = 0;
    int idx2 = 0;
    int idx3 = 0;
    auto& leftChild = segTree[2*v+1];
    auto& rightChild = segTree[2*v+2];
    int leftSize = leftChild.size();
    int rightSize = rightChild.size();
    while((idx1 < leftSize) && (idx2 < rightSize))
    {
        if (leftChild[idx1] < rightChild[idx2])
        {
            segTree[v][idx3++] = leftChild[idx1++];
        }
        else
        {
            segTree[v][idx3++] = rightChild[idx2++];
        }
    }
    while(idx1 < leftSize)
    {
        segTree[v][idx3++] = (leftChild[idx1++]);
    }
    while(idx2 < rightSize)
    {
        segTree[v][idx3++] = (rightChild[idx2++]);
    }
}

int segTreeQuery(int l, int r, vector<vector<int>>& segTree, int tl, int tr, int v)
{
    if ((tr < l) || (r < tl)) return 0;
    if (tl >= l && tr <= r)
    {
        return (segTree[v].size() - (lower_bound(segTree[v].begin(), segTree[v].end(), r) - segTree[v].begin()));
    }
    int tm = (tl + tr)/2;
    return segTreeQuery(l, r, segTree, tl, tm, 2*v+1) + segTreeQuery(l, r, segTree, tm+1, tr, 2*v+2);
}

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    rep(i, 0, n) cin >> arr[i];
    vector<int> endings(n, 0);
    map<int, int> idxMap;
    pre(i, n-1, 0)
    {
        if (idxMap.find(arr[i]) != idxMap.end())
        {
            endings[i] = idxMap[arr[i]];
        }
        else
        {
            endings[i] = n-1;
        }
        idxMap[arr[i]] = i-1;
    }
    vector<vector<int>> segTree(4*n + 1);
    segTreeCreate(endings, segTree, 0, n-1, 0);
    rep(i, 0, q)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << segTreeQuery(a, b, segTree, 0, n-1, 0) << '\n';
    }
    return;
}