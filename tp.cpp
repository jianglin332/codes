#include <stdio.h>
#include <list>
#include <string.h>
using namespace std;
struct pt
{
	int n, tp;
	pt(int nn, int t):n(nn), tp(t){}
};
#define left -1
#define right -2
list<pt> ps;
int nw[11];
int f[202020][11];
int n, q;
typedef list<pt>::iterator li;
void getnext(li &a, int &dir)
{
	nw[10]++;
	int flg = 0, flag = 0;
	if (!f[a->n * 2 - dir][10])
		memcpy(f[a->n * 2 - dir], nw, sizeof(nw));
	if (a->tp < 0)
		dir = a->tp;
	if (!f[a->n * 2 - dir][10])
		memcpy(f[a->n * 2 - dir], nw, sizeof(nw));
	if (a->tp >= 0)
	{
		nw[a->tp--]++;
		if (a->tp < 0)
			flg = 1;
	}
	li nx = a;
	if (a == ps.begin() && dir == left)
	{
		dir = right;
		flag = 1;
		if (a->n == 1)
			if (!f[-left][10])
				memcpy(f[-left], nw, sizeof(nw));
	}
	else if (dir == left)
		nx--;
	else
		nx++;
	int na = a->n;
	if (flg || (a->tp == left && a == ps.begin()))
		a = ps.erase(a);
	if (flag)
		return;
	if (nx == ps.end())
	{
		if (!f[(n + 1) * 2 - dir][10])
			memcpy(f[(n + 1) * 2 - dir], nw, sizeof(nw));
		a = ps.begin();
		return;
	}
	if (!flg && a->tp < 0 && nx->tp < 0)
		ps.erase(a);
	a = nx;
}
int main()
{
	scanf("%d%d\n", &n, &q);
	for (int i = 0; i < n; i++)
	{
		char t = getchar();
		if (t == '>')
			ps.push_back(pt(i + 1, right));
		else if (t == '<')
			ps.push_back(pt(i + 1, left));
		else
			ps.push_back(pt(i + 1, t - '0'));
	}
	list<pt>::iterator nw = ps.begin();
	int dir = right;
	while (!ps.empty() && !(ps.size() == 1 && ps.begin()->tp < 0))
		getnext(nw, dir);
	int *st, *ed;
	for (int i = 0; i < q; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		st = f[a * 2 - right];
		if (f[(b + 1) * 2 - right][10] < f[(a - 1) * 2 - left][10])
			ed = f[(b + 1) * 2 - right];
		else
			ed = f[(a - 1) * 2 - left];
		for (int i = 0; i < 10; i++)
			printf("%d ", ed[i] - st[i]);
		printf("\n");
	}
}
