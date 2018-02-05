#include <stdio.h>
int a[111], c[111];
long long p[22];
int exist[111];
int main()
{
	p[0] = 1;
	for (int i = 1; i <= 20; i++)
		p[i] = p[i - 1] * i;
	int n;
	long long k;
	scanf("%d%lld", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	for (int i = 1; i <= n; i++)
	{
		c[i] = a[i] - 1;
		for (int j = a[i]; j; j--)
			c[i] -= exist[j];
		exist[a[i]] = 1;
	}
	for (int i = 20; i; i--)
		while (k - p[i] >= 0)
		{
			k -= p[i];
			c[n - i]++;
		}
	for (int i = 1; i < n; i++)
		if (c[n - i] > i)
			c[n - i - 1]++, c[n - i] -= i + 1;
	if (c[0])
	{
		printf("-1");
		return 0;
	}
	for (int i = 1; i <= n; i++)
		exist[i] = 0;
	for (int i = 1; i <= n; i++)
	{
		int nw = 1;
		while (exist[nw])
			nw++;
		for (int j = 0; j < c[i]; j++)
		{
			nw++;
			while (exist[nw])
				nw++;
		}
		printf("%d ", nw);
		exist[nw] = 1;
	}
}
