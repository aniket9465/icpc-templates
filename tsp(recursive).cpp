////// tsp recursive ( path starting from node 0 and ending at node 0 )//////////
////// 0 indexed graph 
int dp[10000][20]={}; // dp[mask][i] holds answer for path starting for 0 and ending at index i with mask m 
int gr[20][20]={};    // adjacency matrix of graph
int n;
int re(int i,int mask)
{
    if(dp[mask][i]!=0)
        return dp[mask][i];
    int mi=inf;
    for(int j=1;j<n;++j)
    {
        if(j!=i&&((mask&(1<<j))!=0))
        {
            mi=min(mi,re(j,mask^(1<<i))+gr[j][i]);
        }
    }
    dp[mask][i]=mi;
    return mi;
}
signed main()
{
    int t;
    cin>>t;
    while(t)
    {
        --t;
        cin>>n;
        ++n;
        memset(dp,0,sizeof(dp));
        memset(gr,0,sizeof(gr));
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                if(i!=j)
                cin>>gr[i][j];
        for(int i=1;i<n;++i)
        {
            dp[1+(1<<i)][i]=gr[0][i];
        }
        int ans=inf;
        int t=(1<<(n))-1;
        for(int i=1;i<n;++i)
        {
            ans=min(ans,re(i,t)+gr[i][0]);
        }
        cout<<ans<<endl;
    }
}
