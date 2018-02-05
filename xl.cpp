#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int f[101010];
struct node
{
	int to[2];
} ns[101010 * 32];
int nn, root;
#define to(x, y) ns[x].to[y]
struct ed
{
	int to, nx, l;
}es[202020];
int hd[101010], ne;
void ae(int f, int t, int l)
{
	es[ne].to = t;
	es[ne].l = l;
	es[ne].nx = hd[f];
	hd[f] = ne++;
}
#define bit(a, b) (((a) >> (b)) & 1)
void add(int a)
{
	if (!root)
		root = ++nn;
	int nw = root;
	for (int i = 31; i >= 0; i--)
	{
		int bt = bit(a, i);
		if (!to(nw, bt))
			to(nw, bt) = ++nn;
		nw = to(nw, bt);
	}
}
void dfs(int a, int fa)
{
	for (int i = hd[a]; i != -1; i = es[i].nx)
		if (es[i].to != fa)
			add(f[es[i].to] = f[a] ^ es[i].l), dfs(es[i].to, a);
}
#define s1(x, y) x |= (1 << (y))
#define s0(x, y) x &= ~(1 << (y))
int work()
{
	memset(hd, -1, sizeof(hd));
	memset(ns, 0, sizeof(ns));
	memset(es, 0, sizeof(es));
	memset(f, 0, sizeof(f));
	ne = 0;
	nn = 0;
	root = 0;
	int n;
	if (scanf("%d", &n) <= 0)
		return 0;
	for (int i = 1; i < n; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		ae(a, b, c), ae(b, a, c);
	}
	dfs(0, -1);
	int mx = 0;
	add(0);
	for (int i = 0; i < n; i++)
	{
		int nw = root;
		int nb = f[i];
		for (int j = 31; j >= 0; j--)
		{
			if (to(nw, !bit(nb, j)))
				nw = to(nw, !bit(nb, j)), s1(nb, j);
			else
				nw = to(nw, bit(nb, j)), s0(nb, j);
		}
		mx = max(mx, nb);
	}
	printf("%d\n", mx);
	return 1;
}
int main()
{
	while (work());
}
