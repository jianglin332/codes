#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long f[1010][1010], g[1010][1010];
long long s[1010];
int n;
int vd[1010];
int ay[1010];
int by[1010];
int ar[1010];
int br[1010];
long long sd[1010][1010];
int nb[1010][1010];
long long m1[1010];
long long m2[1010];
int p1[1010];
int p2[1010];
bool cmp1(const int a, const int b)
{
	return ay[a] < ay[b];
}
bool cmp2(const int a, const int b)
{
	return by[a] < by[b];
}
int main()
{
	freopen("poker.in", "r", stdin);
	freopen("poker.out", "w", stdout);
	scanf("%d", &n);
	memset(f, 0xFE, sizeof(f));
	memset(g, 1, sizeof(g));
	memset(m1, 0xFE, sizeof(m1));
	memset(m2, 1, sizeof(m2));
	for (int i = 1; i <= n; i++)
		scanf("%lld", s + i);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", ay + i, by + i);
	for (int i = 1; i <= n; i++)
		ar[i] = br[i] = i;
	for (int i = 0; i <= n; i++)
		g[n][i] = f[i][n] = 0;
	sort(ar + 1, ar + n + 1, cmp1);
	sort(br + 1, br + n + 1, cmp2);
	for (int i = 1; i <= n; i++)
	{
		sd[i][0] = sd[i - 1][0] + s[ar[i]];
		nb[i][0] = nb[i - 1][0] + 1;
	}
	for (int i = 0; i <= n; i++)
	{
		for (int j = 1; j <= i; j++)
			vd[ar[j]]++;
		for (int j = 1; j <= n; j++)
		{
			sd[i][j] = sd[i][j - 1] + (vd[br[j]] ? 0 : s[br[j]]);
			nb[i][j] = nb[i][j - 1] + !vd[br[j]];
		}
		for (int j = 1; j <= i; j++)
			vd[ar[j]]--;
	}
	for (int i = 0; i <= n; i++)
		p1[i] = p2[i] = n;
	for (int i = n - 1; i >= 0; i--)
		for (int j = n - 1; j >= 0; j--)
		{
			while (nb[i][j] != nb[p1[j]][j] && i < p1[j])
			{
				if (ay[ar[p1[j]]] != ay[ar[p1[j] + 1]] && m1[j] < g[p1[j]][j] + sd[p1[j]][j])
				{
					m1[j] = g[p1[j]][j] + sd[p1[j]][j];
				}
				p1[j]--;
			}
			f[i][j] = m1[j] - sd[i][j];
			if (m1[j] == 0xFEFEFEFEFEFEFEFEll)
				f[i][j] = 0;
			while (nb[i][j] != nb[i][p2[i]] && p2[i] > j)
			{
				if (by[br[p2[i]]] != by[br[p2[i] + 1]] && m2[i] > f[i][p2[i]])
				{
					m2[i] = f[i][p2[i]];
				}
				p2[i]--;
			}
			g[i][j] = m2[i];
			if (m2[i] == 0x0101010101010101ll)
				g[i][j] = 0;
		}
	printf("%lld", f[0][0]);
	return 0;
}
