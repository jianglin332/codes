#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define ms(x) memset(x, 0, sizeof(x))
#define g(x) scanf("%d", &x)
struct ed
{
	int to;
	ed *nx;
	ed(int t, ed *n):to(t), nx(n){}
} *hd[110];
struct node
{
	int rq, bk;
	bool operator < (const node &a) const
	{
		return bk < a.bk;
	}
}ns[110];
int n, ls;
node dfs(int nd, int pr)
{
	priority_queue<node> q;
	for (ed *i = hd[nd]; i; i = i->nx)
		if (i->to != pr)
			q.push(dfs(i->to, nd));
	node rt = ns[nd];
	while (!q.empty())
	{
		rt.rq += max(0, q.top().rq - rt.bk);
		rt.bk = max(0, rt.bk - q.top().rq) + q.top().bk;
		q.pop();
	}
	return rt;
}
int main()
{
	g(n);
	for (int i = 1; i <= n; i++)
	{
		int a, b, c;
		g(a), g(b), g(c);
		ns[i].rq = max(a, b + c);
		ns[i].bk = ns[i].rq - b - c;
	}
	for (int i = 1; i < n; i++)
	{
		int a, b;
		g(a), g(b);
		hd[a] = new ed(b, hd[a]);
		hd[b] = new ed(a, hd[b]);
	}
	int m = 100000000;
	for (int i = 1; i <= n; i++)
	{
		int t = dfs(i, 0).rq;
		if (t < m)
			m = t;
	}
	printf("%d", m);
	return 0;
}
