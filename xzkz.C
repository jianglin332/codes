#include <cstdio>
#include <cstring>
int n, m, p, tmp, f, g[50], h[50], c;
int main()
{
	scanf("%d%d%d", &n, &m, &p);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &c, &tmp);
		if (tmp <= p)
		{
			for (int i = 0; i < m; i++)
			{
				g[i] += h[i];
				h[i] = 0;
			}
			f += g[c];
			g[c]++;
		}
		else
		{
			f += g[c];
			h[c]++;
		}
	}
	printf("%d", f);
}
