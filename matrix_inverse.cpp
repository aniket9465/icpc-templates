
#define N 6

int m; // global variable
// m is the actual size of matrix (according to input)

void getCofactor(int A[N][N], int temp[N][N], int p, int q, int n) { 
    int i = 0, j = 0; 
    for (int row = 0; row < n; row++) 
    { 
        for (int col = 0; col < n; col++) 
        {
            if (row != p && col != q) 
            { 
                temp[i][j++] = A[row][col]; 
                if (j == n - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
} 

int determinant(int A[N][N], int n) 
{ 
    int D = 0;
    if (n == 1) {
        return A[0][0]; 
    }
  
    int temp[N][N];
    int sign = 1;
    for (int f = 0; f < n; f++) 
    { 
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1); 
        sign = -sign; 
    }
    return D; 
} 

void adjoint(int A[N][N], int adj[N][N]) { 
    if (m == 1){ 
        adj[0][0] = 1; 
        return; 
    } 
    int sign = 1, temp[N][N]; 
    for (int i=0; i<m; i++) 
    { 
        for (int j=0; j<m; j++) { 
            getCofactor(A, temp, i, j, N); 
            sign = ((i+j)%2==0)? 1: -1;
            adj[j][i] = (sign)*(determinant(temp, m-1)); 
        } 
    } 
} 

// call this function for inverse.

bool inverse(int A[N][N], double inv[N][N]) {
    int det = determinant(A, m); 
    if (det == 0) 
    {
        return false; 
    } 
    int adj[N][N]; 
    adjoint(A, adj); 
    for (int i=0; i<m; i++){
        for (int j=0; j<m; j++){ 
            inv[i][j] = adj[i][j]/double(det);
        }
    }
    return true; 
}
