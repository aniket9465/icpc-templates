std::vector<std::vector<int> > matrix_mult(std::vector<std::vector<int> >& a, std::vector<std::vector<int> >& b, int mod)
{
	std::vector<std::vector<int> > gr(a.size(), std::vector<int> (a.size(), 0));
	for (int i = 0; i < a.size(); ++i)
		for (int j = 0; j < a.size(); ++j)
			for (int k = 0; k < a.size(); ++k)
				gr[i][j] = (gr[i][j] + a[i][k] * b[k][j]) % mod;
	return gr;
}

std::vector<std::vector<int> > matrix_expo(std::vector<std::vector<int> >& a, int n, int mod)
{
	std::vector<std::vector<int> > res(a.size(), std::vector<int> (a.size(), 0));
	for (int i = 0; i < a.size(); ++i)
		res[i][i] = 1;
	while (n) {
		if (n & 1ll)
			res = matrix_mult(res, a, mod);
		a = matrix_mult(a, a, mod);
		n >>= 1;
	}
	return res;
}