#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int mod = 314159;
long long pow(long long x, int t)
{
	if (t == 0)
		return 1;
	if (t == 1)
		return x;
	long long a = pow(x, t / 2);
	if (t & 1)
		return a * a % mod * x % mod;
	else
		return a * a % mod;
}
long long nf = 1;
long long tn = 1;
int a[1010101], b[1010101], c[1010101];
int r[1010101], nr;
int pl[1010101];
int n;
long long work()
{
/*	for (int i = 1; i <= n; i++)
		pl[b[i]] = i;
	for (int i = 1; i <= n; i++)
		printf("%d ", pl[i]);
*/	int p = 0;
	for (int i = 2; i <= n; i++)
		p += (b[i] > b[i - 1]);
	printf("\n%d\n", p);
	long long ans = 1;
	for (int i = 0; i < n; i++)
		ans = ans * (tn + p - i + mod) % mod;
	ans = ans * nf % mod;
	return ans;
}
int main()
{
	//freopen("card.in", "r", stdin);
	//freopen("card.out", "w", stdout);
	long long k;
	scanf("%d%lld", &n, &k);
	for (int i = 1; i <= n; i++)
		nf = nf * i % mod;
	nf = pow(nf, mod - 2);
	tn = pow(2, k);
	for (int i = 1; i <= n; i++)
		scanf("%d", b + i);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	for (int i = 1; i <= n; i++)
		if (!r[a[i]])
			r[a[i]] = ++nr;
	for (int i = 1; i <= n; i++)
		b[i] = r[b[i]];
	if (nr == n)
		printf("%lld", work());
	else
	{
		for (int i = 1; i <= n; i++)
			a[i] = r[a[i]];
		sort(a + 1, a + n + 1);
		memcpy(c, b, sizeof(b));
		int ans = 0;
		for (int i = 1; i <= n; i++)
			b[i] = i;
		do
		{
			int flg = 1;
			for (int i = 1; i <= n && flg; i++)
				if (a[b[i]] != c[i])
					flg = 0;
			if (flg)
				ans = (ans + work()) % mod;
		}
		while (next_permutation(b + 1, b + 1 + n));
		printf("%d", ans);
	}
}
