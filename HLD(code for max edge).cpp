///////////// code for max edge on path from node u to v with update of edge weight using HLD
vector<int> chains[100001];     // stores edge weigth from current node to child in the same chain 
int chain[100001];              // stores chain number
int parent[100001][25];         // stores parent 
int depth[100001];              // depth of node in tree
int size[100001];               // size of subtree
int ind[100001];                // index of node in its chain 
int chaintop[100001];           // top node of a chain
map<pair<int,int>,int> we;      // edge to weight map
int tchains;                    // total chains
vector<int> seg[100001];        // segment tree of chain i 
int dfs(int i,int pr,vector<pair<int,int>> gr[],int d) 
{
    parent[i][0]=pr;
    depth[i]=d;
    int s=1;
    for(auto r:gr[i])
    {
        if(r.first!=pr)
        {
            size[r.first]=dfs(r.first,i,gr,d+1);
            s+=size[r.first];
        }
    }
    return s;
}
int lca(int u,int v)
{
    if(u==v)
    {
        return v;
    }
    if(depth[u]<depth[v])
        swap(u,v);
    int d=depth[u]-depth[v];
    int ii=0;
    while(d)
    {
        if(d%2==1)
        {
            u=parent[u][ii];
        }
        d/=2;
        ++ii;
    }
    if(u==v)
        return u;
    for(int i=24;i>=0;--i)
    {
        if(parent[v][i]!=parent[u][i])
        {
            u=parent[u][i];
            v=parent[v][i];
        }
    }
    return parent[u][0];
}
void HLD(int chainNo,vector<pair<int,int>> gr[],int i)
{
    tchains=max(tchains,chainNo+1);
    ind[i]=chains[chainNo].size();
    vector<pair<pair<int,int>,int>> v;
    chain[i]=chainNo;
    if(chaintop[chainNo]==0)
    {
        chaintop[chainNo]=i;
    }
    for(auto r:gr[i])
    {
        if(r.first!=parent[i][0])
        {
            v.push_back({{size[r.first],r.second},r.first});
        }
    }
    sort(v.begin(),v.end(),greater<pair<pair<int,int>,int>>());
    if(v.size()!=0)                                                 //
        chains[chainNo].push_back(v[0].first.second);               //  setting the chain to store the 
    else                                                            //  weigth of edge from current node
        chains[chainNo].push_back(0);                               //  to the child on same chain
    int f=1;
    for(auto r:v)
    {
        if(f==1){
            HLD(chainNo,gr,r.second);
            f=0;
        }
        else
        {
            HLD(tchains,gr,r.second);
        }
    }
}
int createseg(vector<int> &seg,int l,int r,int i,vector<int>& arr)
{
    if(r<l)
        return 0;
    if(l==r)
    {
        seg[i]=arr[l];
        return arr[l];
    }
    else
    {
        int m=(l+r)/2;
        seg[i]=max(createseg(seg,l,m,2*i,arr),createseg(seg,m+1,r,2*i+1,arr));
        return seg[i];
    }
}
int update(vector<int> &seg,int in,int l,int r,int i,int val)
{
    if(r<l)
        return 0;
    if(l==r)
    {
        seg[i]=val;
        return val;
    }
    else
    {
        int m=(l+r)/2;
        if(in>m)
        {
            seg[i]=max(seg[2*i],update(seg,in,m+1,r,2*i+1,val));
        }
        else
        {
            seg[i]=max(seg[2*i+1],update(seg,in,l,m,2*i,val));
        }
        return seg[i];
    }
}
int ansseg(vector<int>& seg,int lq,int rq,int l,int r,int i)
{
    if(r<l)
        return 0;
    if(l==lq&&r==rq)
    {
        return seg[i];
    }
    else
    {
        int m=(l+r)/2;
        if(lq>m)
        {
            return ansseg(seg,lq,rq,m+1,r,2*i+1);
        }
        else
        {
            if(rq<=m)
            {
                return ansseg(seg,lq,rq,l,m,2*i);
            }
            else
            {
                return max(ansseg(seg,m+1,rq,m+1,r,2*i+1),ansseg(seg,lq,m,l,m,2*i));
            }
        }
    }
}
int solve(int x,int lc)
{
    if(x==lc)
        return 0;
    if(chain[x]==chain[lc])
    {
        return ansseg(seg[chain[x]],ind[lc],ind[parent[x][0]],0,chains[chain[x]].size()-1,1);
    }
    else
    {
        return max(solve(x,chaintop[chain[x]]),max(we[{parent[chaintop[chain[x]]][0],chaintop[chain[x]]}],solve(parent[chaintop[chain[x]]][0],lc)));
    }
}
signed main()
{
    fastio;
    #ifndef ONLINE_JUDGE
        freopen("inputf.in","r",stdin);
        freopen("outputf.in","w",stdout);
    #endif
    int t;
    cin>>t;
    while(t)
    {
        --t;
        int n;
        cin>>n;
        tchains=0;
        memset(parent,0,sizeof(parent));
        memset(depth,0,sizeof(depth));
        memset(size,0,sizeof(size));
        memset(chaintop,0,sizeof(chaintop));
        for(int i=0;i<100001;++i)
        {
            chains[i].clear();
            seg[i].clear();
        }
        vector<pair<int,int>> gr[n+1];
        int ed[n][2];
        we.clear();
        for(int i=0;i<n-1;++i)
        {
            int x,y,w;
            cin>>x>>y>>w;
            we[{x,y}]=w;
            we[{y,x}]=w;
            ed[i+1][0]=x;
            ed[i+1][1]=y;
            gr[x].push_back({y,w});
            gr[y].push_back({x,w});
        }
        size[1]=dfs(1,0,gr,1);
        for(int i=1;i<25;++i)
        {
            for(int j=1;j<=n;++j)
            {
                parent[j][i]=parent[parent[j][i-1]][i-1];
            }
        }
        HLD(0,gr,1);
        for(int i=0;i<tchains;++i)
        {
            seg[i].resize(16*chains[i].size(),0);
            createseg(seg[i],0,((int)chains[i].size()-1),1,chains[i]);
        }
        int q;
        cin>>q;
        while(q)
        {
            --q;
            int ty,x,y;
            cin>>ty>>x>>y;
            if(ty==1)    // update query
            {
                int v=y;
                y=ed[x][1];
                x=ed[x][0];
                we[{x,y}]=v;
                we[{y,x}]=v;
                if(chain[x]==chain[y])
                {
                    if(depth[x]>depth[y])
                        swap(x,y);
                    update(seg[chain[x]],ind[x],0,chains[chain[x]].size()-1,1,v);
                }
            }
            else // answer query 
            {
                int lc=lca(x,y);
                cout<<max(solve(x,lc),solve(y,lc))<<"\n";
            }
        }
    }
}