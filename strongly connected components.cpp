///// strongly connected components ////

void dfs(int i,stack<int> &s,int vis[],vector<int> gr[])
{
    if(vis[i]==0)
    {
        vis[i]=2;
        for(auto r:gr[i])
        {
            dfs(r,s,vis,gr);
        }
        s.push(i);
    }
}
void dfs2(int i,stack<int> &s,int vis[],vector<int> gr[])
{
    if(vis[i]==2)
    {
        vis[i]=1;
        s.push(i);
        for(auto r:gr[i])
        {
            dfs2(r,s,vis,gr);
        }
    }
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
    int a[n+1];
    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
    }
    vector<int> gr[n+1],grr[n+1];
    int m;
    cin>>m;
    ll ans=0,c=1;
    for(int i=0;i<m;++i)
    {
        int a,b;
        cin>>a>>b;
        gr[a].push_back(b);
        grr[b].push_back(a);
    }
    int vis[n+1]={};
    for(int i=1;i<=n;++i)
    {
        if(vis[i]==0)
        {
            stack<int> s;
            dfs(i,s,vis,gr);
            while(!s.empty())
            {
                int j=s.top();
                s.pop();
                if(vis[j]==2)
                {
                    stack<int> s1;
                    dfs2(j,s1,vis,grr);
                    map<int,int> m;
                    while(!s1.empty())
                    {
                        cout<<s1.top()<<" " ; //strongly connected components
                        s1.pop(); 
                    }
                    cout<<"\n";
                }
            }
        }
    }
}
