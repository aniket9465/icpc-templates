///////////// cut Edges
vector<pair<int,int>> cutEdges;
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
            if(mdepr>dep[i])
            {
                cutEdges.push_back({min(i,r),max(i,r)});
            }
        }
    }
    return mdep[i];
}
