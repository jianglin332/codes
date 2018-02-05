#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <ctype.h>
#include <math.h>
using namespace std;
char buf[10101010];
int g()
{
	static char *n = buf;
	int r = 0;
	while (!isdigit(*n))
		n++;
	while (isdigit(*n))
		r = r * 10 + *(n++) - '0';
	return r;
}
const int maxn = 101010;
int tl[maxn], tr[maxn];
int l[maxn], r[maxn];
int nc[maxn], num[maxn], nn, nnc;
int last[maxn];
int dif[maxn];
int b[maxn];
struct sec
{
	int fr, to, n, ans;
	bool operator<(const sec &a) const
	{
		return to < a.to;
	}
}sss[maxn], ss[maxn];
int c[maxn];
bool cmp(const sec &a, const sec &b)
{
	return a.n < b.n;
}
int main()
{
	fread(buf, 10101010, 1, stdin);
	int m = g();
	for (int i = 1; i <= m; i++)
		b[i] = g();
	for (int i = 1; i <= m; i++)
		if (!last[b[i]])
			l[i] = tl[i] = 0, last[b[i]] = i;
		else if (!dif[b[i]])
			tl[i] = 0, dif[b[i]] = i - (l[i] = last[b[i]]), last[b[i]] = i;
		else if (i - last[b[i]] != dif[b[i]])
			tl[i] = (l[i] = last[b[i]]) - dif[b[i]], dif[b[i]] = i - last[b[i]], last[b[i]] = i;
		else
			tl[i] = tl[l[i] = last[b[i]]], last[b[i]] = i;
	memset(last, 0, sizeof(last));
	memset(dif, 0, sizeof(dif));
	r[m + 1] = tr[m + 1] = m + 1;
	for (int i = m; i >= 1; i--)
		if (!last[b[i]])
			r[i] = tr[i] = m + 1, last[b[i]] = i;
		else if (!dif[b[i]])
			tr[i] = m + 1, dif[b[i]] = (r[i] = last[b[i]]) - i, last[b[i]] = i;
		else if (i - last[b[i]] != dif[b[i]])
			tr[i] = (r[i] = last[b[i]]) + dif[b[i]], dif[b[i]] = last[b[i]] - i, last[b[i]] = i;
		else
			tr[i] = tr[r[i] = last[b[i]]], last[b[i]] = i;
	int nb = sqrt(m);
	int q = g();
	for (int i = 0; i < q; i++)
		sss[i].n = i, c[(sss[i].fr = g()) / nb]++, sss[i].to = g();
	sort(sss, sss + q);
	for (int i = 1; i <= m; i++)
		c[i] += c[i - 1];
	for (int i = q - 1; i >= 0; i--)
		ss[--c[sss[i].fr / nb]] = sss[i];
	int ln = 1, rn = 1;
	num[b[1]]++, nc[b[1]] = 1, nn = 1, nnc = 1;
	for (int i = 0; i < q; i++)
	{
		while (rn < ss[i].to)
		{
			if (!num[b[++rn]]++)
				nn++, nnc++, nc[b[rn]] = 1;
			else if (nc[b[rn]] && tl[rn] >= ln)
				nnc--, nc[b[rn]] = 0;
		}
		while (ln > ss[i].fr)
		{
			if (!num[b[--ln]]++)
				nn++, nnc++, nc[b[ln]] = 1;
			else if (nc[b[ln]] && tr[ln] <= rn)
				nnc--, nc[b[ln]]--;
		}
		while (rn > ss[i].to)
		{
			if (!--num[b[rn]])
				nn--, nnc -= nc[b[rn]], nc[b[rn]] = 0;
			else if (!nc[b[rn]])
				nnc += (nc[b[rn]] = tl[l[rn]] < ln);
			rn--;
		}
		while (ln < ss[i].fr)
		{
			if (!--num[b[ln]])
				nn--, nnc -= nc[b[ln]], nc[b[ln]] = 0;
			else if (!nc[b[ln]])
				nnc += (nc[b[ln]] = tr[r[ln]] > rn);
			ln++;
		}
		ss[i].ans = nn + !nnc;
	}
	sort(ss, ss + q, cmp);
	for (int i = 0; i < q; i++)
		printf("%d\n",ss[i].ans);
}
