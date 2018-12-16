#define F first
#define int long long 
#define S second
/////////////
const int maxn=100001;
int colour[maxn];
void colourGraph(int n,vector<int> gr[])
{
    int s=0;
    set<pair<int,int>> v;
    int deg[n+1]={};
    for(int i=1;i<=n;++i){
        deg[i]=gr[i].size();
        v.insert({-deg[i],i});
    }
    int c=1;
    while(s<n)
    {
        multiset<int> ad;
        vector<pair<int,int>> rm;
        for(auto r:v)
        {
            if(ad.find(r.S)==ad.end())
            {
                rm.push_back({r.first,r.S});
                
                for(auto u:gr[r.second])
                {
                    ad.insert(u);
                }
            }
        }
        for(auto r:rm)
        {
            colour[r.S]=c;
            v.erase(v.find(r));
            ++s;
        }
        for(auto r:ad)
        {
            if(v.find({-deg[r],r})!=v.end()){
                v.erase(v.find({-deg[r],r}));
                v.insert({-deg[r]+1,r});
                deg[r]--;
            }
        }
        ++c;
    }
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
    vector<int> gr[n+1];
    for(int i=0;i<m;++i)
    {
        int x,y;
        cin>>x>>y;
        gr[x].push_back(y);
        gr[y].push_back(x);
    }
    colourGraph(n,gr);
    for(int i=1;i<=n;++i)
    {
        cout<<colour[i]<<"\n";
    }
}
