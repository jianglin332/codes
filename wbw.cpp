#include <stdio.h>
#include <algorithm>
using namespace std;
int c[4040][4040];
const int mod = 1e9 + 9;
int main()
{
	for (int i = c[0][0] = c[1][0] = 1; i < 4040; c[++i][0] = 1)
		for (int j = 1; j <= i; j++)
		{
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
			if (c[i][j] >= mod)
				c[i][j] -= mod;
		}
	int n, w, b;
	scanf("%d%d%d", &n, &w, &b);
	long long ans = 0;
	for (int i = max(n - b, 1); i <= min(n - 1, w); i++)
		ans = (ans + (1ll * c[w - 1][i - 1] * c[b - 1][n - i - 1]) % mod * (i - 1)) % mod;
	for (int i = 1; i <= w; i++)
		ans = (ans * i) % mod;
	for (int i = 1; i <= b; i++)
		ans = (ans * i) % mod;
	printf("%lld", ans);
}
