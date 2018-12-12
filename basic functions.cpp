//////  power function ////
long long power (long long  a, long long  b) {
    long long ans=1ll;
    while(b) {
        if(b&1)ans=(ans*a);
        a=(a*a);
        b=b/2;
    }
    return ans;
    }
///// power mod /////
long long powerm(long long x, unsigned long long y, long long p) 
{ 
    long long res = 1;
    x = x % p;
    while (y > 0) 
    { 
        if (y & 1) 
            res = (res*x) % p; 
        y = y>>1;
        x = (x*x) % p;   
    } 
    return res; 
} 
//// modular inverse  ////////
long long modinverse(long long a, long long b)
{
    long long b0 = b, t, q;
    long long x0 = 0, x1 = 1;
    if (b == 1) return 1;
    while (a > 1) {
        q = a / b;
        t = b, b = a % b, a = t;
        t = x0, x0 = x1 - q * x0, x1 = t;
    }
    if (x1 < 0) x1 += b0;
    return x1;
}
////// convolute O(n^2)
vector<int> convule(vector<int> v1,vector<int> v2)
{
    vector<int> res;
    reverse(v2.begin(),v2.end());
    int j=1;
    for(int i=0;i<v1.size()+v2.size()-1;++i)
    {
        int v=0;
        for(int k=0;k<v1.size();++k)
        {
            if(k-j+v2.size()>=0&&k-j+v2.size()<v2.size())
            {
                v+=v1[k]*v2[k-j+v2.size()];
            }
        }
        res.push_back(v);
        ++j;
    }
    return (res);
}
