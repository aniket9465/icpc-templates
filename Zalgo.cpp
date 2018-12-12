// Fills Z array for given string str[] 
void getZarr(string str, int Z[]) 
{ 
    int n = str.length(); 
    int L, R, k; 
    Z[0]=0;
    L = R = 0; 
    for (int i = 1; i < n; ++i) 
    { 
        if (i > R) 
        { 
            L = R = i; 
            while (R<n && str[R-L] == str[R]) 
                R++; 
            Z[i] = R-L; 
            R--; 
        } 
        else
        { 
            k = i-L; 
            if (Z[k] < R-i+1) 
                Z[i] = Z[k]; 
            else
            { 
                L = i; 
                while (R<n && str[R-L] == str[R]) 
                    R++; 
                Z[i] = R-L; 
                R--; 
            } 
        } 
    } 
} 
signed main()
{
    fastio;
    #ifndef ONLINE_JUDGE
        freopen("inputf.in","r",stdin);
        freopen("outputf.in","w",stdout);
    #endif
    string s;
    string t;
    s="aniket";
    t="aniketaniketaniket";
    int z[100];
    s=s+"#"+t;
    getZarr(s,z);
    for(int i=0;i<s.length();++i)
    {
        cout<<z[i]<<" ";
    }
}
