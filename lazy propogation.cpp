/////////////  lazy propogation for sum queries  
void update(int seg[],int lazy[],int l,int r,int lq,int rq,int val,int i)
{
    
    if(l==lq&&r==rq)
    {
        lazy[i]+=val;
    }
    else
    {
        
        seg[i]+=val*(rq-lq+1);  // apply changes to super segments

        int m=(l+r)/2;
        if(rq<=m)
        {
            update(seg,lazy,l,m,lq,rq,val,2*i);
        }
        else
        {
            if(lq>m)
            {
                update(seg,lazy,m+1,r,lq,rq,val,2*i+1);
            }
            else
            {
                update(seg,lazy,l,m,lq,m,val,2*i);
                update(seg,lazy,m+1,r,m+1,rq,val,2*i+1);
            }
        }
    }
}
int ans(int seg[],int lazy[],int l,int r,int lq,int rq,int i)
{
    if(l!=r){                   
        lazy[2*i]+=lazy[i];         // propogate lazy to sub segments
        lazy[2*i+1]+=lazy[i];
    }

    seg[i]+=lazy[i]*(r-l+1);        // apply current nodes lazy 
    lazy[i]=0;

    if(l==lq&&r==rq)
    {
        return seg[i];
    }
    else
    {
        int m=(l+r)/2;
        if(rq<=m)
        {
            return ans(seg,lazy,l,m,lq,rq,2*i);
        }
        else
        {
            if(lq>m)
            {
                return ans(seg,lazy,m+1,r,lq,rq,2*i+1);
            }
            else
            {
                return ans(seg,lazy,l,m,lq,m,2*i) + ans(seg,lazy,m+1,r,m+1,rq,2*i+1);
            }
        }
    }
}
signed main()
{
    int t;
    cin>>t;
    while(t)
    {
        --t;
        int n,q;
        cin>>n>>q;
        int seg[16*n]={},lazy[16*n]={};
        while(q)
        {
            --q;
            int ty;
            cin>>ty;
            if(ty==0)
            {
                int l,r,v;
                cin>>l>>r>>v;
                update(seg,lazy,1,n,l,r,v,1);
            }
            else
            {
                int l,r;
                cin>>l>>r;
                cout<<ans(seg,lazy,1,n,l,r,1)<<"\n";
            }
        }
    }
}