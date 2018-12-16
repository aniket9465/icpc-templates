///////////// cut vertex
vector<int> articulation_points;
int dfs(int i,int pr,int dep[],int mdep[],int d,vector<int> gr[])
{
    dep[i]=d;
    mdep[i]=d;
    int fl=0;
    int ch=0;
    for(auto r:gr[i])
    {
        if(r!=pr)
        {
            if(mdep[r]!=0)
            {
                mdep[i]=min(mdep[i],dep[r]); 
                continue;
            }
            int mdepr=dfs(r,i,dep,mdep,d+1,gr);
            mdep[i]=min(mdep[i],mdepr);
            if(mdepr>=dep[i])
            {
                ++ch;
                if(ch>1||i!=1)//i is not root
                {
                    if(fl==0){
                        fl=1;
                        articulation_points.push_back(i);
                    }
                }
            }
        }
    }
    return mdep[i];
}
signed main()
{
    fastio;
    #ifndef ONLINE_JUDGE
        freopen("inputf.in","r",stdin);
        freopen("outputf.in","w",stdout);
    #endif
    int n,m;
    cin>>n>>m;
    while(n)
    {
        vector<int> gr[n+1];
        for(int i=0;i<m;++i)
        {
            int x,y;
            cin>>x>>y;
            gr[y].push_back(x);
            gr[x].push_back(y);
        }
        articulation_points.clear();
        int dep[n+1]={},mdep[n+1]={};
        dfs(1,-1,dep,mdep,1,gr);
        cout<<articulation_points.size()<<"\n";
        for(auto r:articulation_points)
        {
            cout<<r<<" ";
        }
        cout<<"\n";
        cin>>n>>m;
    }
}
