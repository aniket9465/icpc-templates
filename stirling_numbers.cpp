// Stirling numbers of the first kind
// Number of permutations of n objects with k disjoint cycles. s[4][2]=11
// coefficient of the rising factorial x(x+1)...(x+n-1)
// summation c(n, k) = n!
int dp[1003][1003];
void stirling_first_kind(){
    dp[0][0]=1;
    for(int i=1; i<=1000; i++){
        dp[i][0]=0;
        dp[0][i]=0;
    }
    for(int i=1; i<=1000; i++){
        for(int j=1; j<=i; j++){
            dp[i][j]=(i-1)*dp[i-1][j]+dp[i-1][j-1];
            dp[i][j]=dp[i][j]%1000000007;
        }
    }
}
// Stirling numbers of the second kind
// number of ways to partition n objects into k non-empty subsets.
int dp1[1003][1003];
void stirling_second_kind(){
    dp1[0][0]=1;
    for(int i=1; i<=1000; i++){
        dp1[i][0]=0;
        dp1[0][i]=0;
    }
    for(int i=1; i<=1000; i++){
        for(int j=1; j<=i; j++){
            dp1[i][j]=j*dp1[i-1][j]+dp1[i-1][j-1];
            dp1[i][j]=dp1[i][j]%1000000007;
        }
    }
}
// Bell Number
// total no. of ways to partition n in non empty subsets
// summation of stirling numbers of second kind for k=0 to n
// cards if shuffled by putting top card into anywhere in the deck (n times)
int dp2[1003][1003];
int bell[1003];
void bell_numbers(){
    dp2[0][0]=1;
    bell[0]=1;
    for(int i=1; i<=1000; i++){
        dp2[i][0]=dp2[i-1][i-1];
        bell[i]=dp2[i][0];
        for(int j=1; j<=i; j++){
            dp2[i][j]=dp2[i-1][j-1]+dp2[i][j-1];
            dp2[i][j]=dp2[i][j]%1000000007;
        }
    }
}



