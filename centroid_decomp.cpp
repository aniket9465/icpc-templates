////// centroid decomposition 
#define int long long 
#define MAXN 1000001
int size[MAXN];
int depth[MAXN];
set<int> gr[MAXN];
set<int> dtree[MAXN];
char ans[MAXN];
int dfs(int i,int pr,int d)
{
    depth[i]=d;
    int si=0;
    for(auto r:gr[i])
    {
        if(r!=pr)
        {
            si+=dfs(r,i,d+1);
        }
    }
    size[i]=si+1;
    return si+1;
}
int findCentre(int i,int pr,int m)
{
    int f=1;
    for(auto r:gr[i])
    {
        if(r!=pr)
        {
            if(size[r]>m)
                f=0;
        }
    }
    if(f)
        return i;
    for(auto r:gr[i])
    {
        if(r!=pr)
        {
            if(size[r]>m)
                return findCentre(r,i,m);
        }
    }
}
int decompose(int i)
{
    dfs(i,-1,0);
    int centre=findCentre(i,-1,(size[i])/2);
    vector<int> v;
    for(auto r:gr[centre])
    {
        v.push_back(r);
        gr[r].erase(centre);
    }
    gr[centre].clear();
    for(auto r:v)
    {
        int sub=decompose(r);
        dtree[centre].insert(sub);
        dtree[sub].insert(centre);
    }
    return centre;
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
        freopen("inputf.in","r",stdin);
        freopen("outputf.in","w",stdout);
    #endif
    int n;
    cin>>n;
    for(int i=0;i<=n;++i)
        gr[i].clear();
    for(int i=0;i<n-1;++i)
    {
        int a,b;
        cin>>a>>b;
        gr[a].insert(b);
        gr[b].insert(a);
    }
    int root_decomposed_tree=decompose(1);
}

