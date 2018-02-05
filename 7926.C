#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
struct ed
{
	int h;
	int l;
	int r;
	bool operator<(const ed a) const
	{
		if (h < a.h)
			return 1;
		if (h > a.h)
			return 0;
		if (r < a.r)
			return 1;
		return 0;
	}   
};
struct pt
{
	int x, y;
};
bool cmp(const ed a, const ed b)
{
	if (a.l < b.l)
		return 1;
	if (a.l > b.l)
		return 0;
	if (a.h <= b.h)
		return 0;
	return 1;
}
ed es[101010];
pt fn[101010];
int nf = 0;
priority_queue<ed> q;
ed pr = {0, -2000000000, -2000000000};
bool ls = 1;
void del(ed a)
{
	if (a.r <= pr.r)
		return;
	else if (ls)
	{
		fn[nf].x = a.r;
		fn[nf++].y = a.h;
		pr = a;
	}
	else
	{
		fn[nf].x = pr.r;
		fn[nf++].y = a.h;
		fn[nf].x = a.r;
		fn[nf++].y = a.h;
		pr = a;
	}
	ls = 0;
}
void ins(ed a)
{
	if (q.top().h >= a.h)
		return;
	else if ((!ls) && pr.r != a.l)
	{
		fn[nf].x = pr.r;
		fn[nf++].y = q.top().h;
		fn[nf].x = a.l;
		fn[nf++].y = q.top().h;
		fn[nf].x = a.l;
		fn[nf++].y = a.h;
	}
	else if ((!ls) && pr.h == a.h)
	{
		nf--;
	}
	else if (!ls)
	{
		fn[nf].x = pr.r;
		fn[nf++].y = a.h;
	}
	else
	{
		fn[nf].x = a.l;
		fn[nf++].y = q.top().h;
		fn[nf].x = a.l;
		fn[nf++].y = a.h;
	}
	ls = 1;
}
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d%d", &es[i].h, &es[i].l, &es[i].r);
	}
	sort(es, es + n, cmp);
	ed t;
	t.h = 0;
	t.l = -2000000000;
	t.r = 2000000000;
	q.push(t);
	for (int i = 0; i < n; i++)
	{
		while (q.top().r <= es[i].l)
		{
			del(q.top());
			q.pop();
		}
		ins(es[i]);
		q.push(es[i]);
	}
	while (!q.empty())
	{
		del(q.top());
		q.pop();
	}
	nf--;
	printf("%d\n", nf);
	for (int i = 0; i < nf; i++)
	{
		printf("%d %d\n", fn[i].x, fn[i].y);
	}
	return 0;
}
