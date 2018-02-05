#include <cstdio>
#include <cstring>
int s[1010101], t[1010101];
int l[1010101], r[1010101], f[1010101];
int n, m;
bool work(int a)
{
	static int ls = 0;
	if (a < ls)
	{
		for (int i = a + 1; i <= ls; i++)
		{
			t[l[i]] -= f[i];
			t[r[i] + 1] += f[i];
		}
		ls = a;
		int d = 0;
		for (int i = 1; i <= n; i++)
		{
			d += t[i];
			if (d > s[i])
				return 0;
		}
		return 1;
	}
	else
	{
		for (int i = ls + 1; i <= a; i++)
		{
			t[l[i]] += f[i];
			t[r[i] + 1] -= f[i];
		}
		ls = a;
		int d = 0;
		for (int i = 1; i <= n; i++)
		{
			d += t[i];
			if (d > s[i])
				return 0;
		}
		return 1;
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", s + i);
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", f + i, l + i, r + i);
	int st = 1, ed = m + 1;
	while (st != ed)
	{
		int mid = ((st + ed) >> 1);
		if (work(mid))
			st = mid + 1;
		else
			ed = mid;
	}
	if (st == m + 1)
		printf("0");
	else
		printf("-1\n%d", st);
}
