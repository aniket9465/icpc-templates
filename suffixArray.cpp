const int MAXN = 1 << 21;
int sa[MAXN], pos[MAXN], tmp[MAXN];
int N, gap;
bool sufCmp(int i, int j)
{
    if (pos[i] != pos[j])
        return pos[i] < pos[j];
    i += gap;
    j += gap;
    return (i < N && j < N) ? pos[i] < pos[j] : i > j;
}
void buildSA(string s)
{
    N = s.length();
    memset(tmp,0,sizeof(tmp));
    for(int i=0;i<N;++i) sa[i] = i, pos[i] = s[i];
    for (gap = 1;; gap *= 2)
    {
        sort(sa, sa + N, sufCmp);
        for(int i=0;i<N-1;++i) tmp[i + 1] = tmp[i] + sufCmp(sa[i], sa[i + 1]);
        for(int i=0;i<N;++i) pos[sa[i]] = tmp[i];
        if (tmp[N - 1] == N - 1) break;
    }
}

// Usage : buildSA(string);
