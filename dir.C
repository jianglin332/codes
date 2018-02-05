#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct nme
{   
	char v[15];
	bool ud;
	int l;
}nn[110] = {0}, sn[110] = {0}, *dnn[26][110], *dsn[26][110];
int nnn[26], snn[26], dn[26], nws[26], pn;
struct an
{
	nme *a, *b;
}ans[110] = {0};
nme *nxtf(int a)
{
	while (1)
	{
		if (a > pn)
		{
			if (nws[pn] < snn[pn])
				return dsn[pn][nws[pn]++];
			else
				pn++;
		}
		else
		{
			return NULL;
		}
	}
}
nme *nxtb()
{
	while (1)
	{
		if (nws[pn] < dn[pn])
			return dsn[pn][nws[pn]++];
		else
			pn++;
	}
}
bool cmp(const nme &a, const nme &b)
{
	for (int i = 0; i < min(a.l, b.l); i++)
	{
		if (a.v[i] < b.v[i])
			return 1;
		if (a.v[i] > b.v[i])
			return 0;
	}
	return a.l < b.l;
}
bool cmp2(const an &a, const an &b)
{
	for (int i = 0; i < min(a.a->l, b.a->l); i++)
	{
		if (a.a->v[i] < b.a->v[i])
			return 1;
		if (a.a->v[i] > b.a->v[i])
			return 0;
	}
	return a.a->l < b.a->l;
}
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", nn[i].v);
		nn[i].l = strlen(nn[i].v);
	}
	for (int i = 0; i < n; i++)
	{
		scanf("%s", sn[i].v);
		sn[i].l = strlen(sn[i].v);
	}
	sort(nn, nn + n, cmp);
	sort(sn, sn + n, cmp);
	for (int i = 0; i < n; i++)
	{
		dnn[nn[i].v[0] - 'A'][nnn[nn[i].v[0] - 'A']++] = &nn[i];
		dsn[sn[i].v[0] - 'A'][snn[sn[i].v[0] - 'A']++] = &sn[i];
	}
	for (int i = 0; i < 26; i++)
	{
		dn[i] = nnn[i] >= snn[i] ? 0 : snn[i] - nnn[i];
	}
	int s = 0;
	for (int i = 0; i < 26; i++)
	{
		int x = 0;
		if (nnn[i] > snn[i])
		{
			while (x < nnn[i] - snn[i])
			{
				nme *tm = nxtf(i);
				if (!tm)
					break;
				ans[s].a = dnn[i][x];
				ans[s++].b = tm;
				x++;
			}
		}
		while (nws[i] < snn[i] && x < nnn[i])
		{
			ans[s].a = dnn[i][x++];
			ans[s++].b = dsn[i][nws[i]++];
		}
		while (x < nnn[i])
		{
			ans[s].a = dnn[i][x++];
			ans[s++].b = nxtb();
		}
	}
	for (int i = 0; i < n - 1; i++)
		printf("%s %s, ", ans[i].a->v, ans[i].b->v);
	printf("%s %s", ans[n - 1].a->v, ans[n - 1].b->v);
	return 0;
}
