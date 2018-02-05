#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long d[1010];
long long f[2][1010];
int main()
{
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++)
		scanf("%I64d", d + i);
	sort(d, d + n);
	for (int i = 0; i < n; i++)
		f[0][i] = d[i] * d[i];
	for (int i = 1, cur = 1; i < k; i++, cur ^= 1)
	{
		memset(f[cur], 0x33, sizeof(f[cur]));
		long long * src = f[cur ^ 1];
		long long * dst = f[cur];
		for (int i = 0; i < n; i++)
		{
			long long mn = 0x3333333333333333l;
			for (int j = 0; j < i; j++)
				mn = min(mn, src[j] + (d[i] - d[j]) * (d[i] - d[j]));
			dst[i] = mn;
		}
	}
	printf("%I64d", f[(k - 1) & 1][n - 1]);
}
