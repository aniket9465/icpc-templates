#define maxn 1000001
int n;
int pa[maxn];
int depth[maxn];
int parent[maxn][25];
vector<int> gr[maxn];
// 1 indexed graph 
// call dfs(rootindex,0,0)
// call preprocess()
//for each test case clear the global data
void dfs(int i,int pr,int d)
{
    pa[i]=pr;
    depth[i]=d;
    for(int j=0;j<gr[i].size();++j)
    {
        if(gr[i][j]!=pr)
        {
            dfs(gr[i][j],i,d+1);
        }
    }
}
void precom()
{
    for(int i=0;i<25;++i)
        parent[0][i]=0;
    for(int i=1;i<=n;++i)
    {
        parent[i][0]=pa[i];
    }
    for(int i=1;i<25;++i){
        for(int j=1;j<=n;++j)
        {
            parent[j][i]=parent[parent[j][i-1]][i-1];
        }
    }
}
int lca(int u,int v)
{
    if(u==v)
        return u;
    if(depth[u]>depth[v])
    {
        swap(u,v);
    }
    int d=depth[v]-depth[u];
    int in=0;
    while(d!=0)
    {
        if(d%2==1)
        {
            v=parent[v][in];
        }
        ++in;
        d/=2;
    }
    if(u==v)
        return v;

    for(int i=24;i>=0;--i)
    {
        if(parent[u][i]!=parent[v][i])
        {
            u=parent[u][i];
            v=parent[v][i];
        }
    }
    return parent[u][0];
}