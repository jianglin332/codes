/*
URAL 1519
Formula 1
http://acm.timus.ru/problem.aspx?space=1&num=1519
*/

#include <cstdio>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <cstdlib>
#include <cstring>
#define bts(x, y) ((x) >> ((y) << 1) & 3)
#define chg(x, y, z) x = ((x & (~(3 << ((y) << 1)))) | ((z) << ((y) << 1)))
#define stat(x, y, z) (((x) << 43) | ((y) << 37) | (z))
#define gx(x) (((x) >> 43) & 15)
#define gy(x) (((x) >> 37) & 15)
#define gl(x) ((x) & 2147483647)
#define bk(x, y) (((x) << 4) | (y))
#define LP 1
#define RP 2
using namespace std;
int n, m, p;
bool block[256];
typedef int line;
typedef long long state;
typedef long long ll;
void disp(line a)
{
	for (int i = 0; i <= 10; i++)
		printf("%d ", bts(a, i));
	printf("\n");
}
queue<state> q;
unordered_map<line, ll> mp;
unordered_map<line, ll> omp;
//#define mp (*imp)
//#define omp (*iomp)
inline void refresh()
{
	unordered_map<line, ll> tmp;
	omp.swap(tmp);
	mp.swap(omp);
}
inline void insState(state fr, state to)
{
	if (!mp[to])
		q.push(to);
	mp[to] += omp[fr];
}
inline void mkbstate(state a)
{
	if (bts(a, gy(a)) || bts(a, gy(a) + 1))
		return;
	insState(a, stat(gx(a), gy(a) + 1, gl(a)));
}
inline void genOtherLine(state a)
{
	line ln = a;
	ln <<= 2;
	chg(ln, 0, 0);
	chg(ln, m + 1, 0);
	insState(a, stat(gx(a) + 1, (ll)0, ln));
}
int lx, ly;
inline void mkstate(state a)
{
	line ln = a;
	ll x = gx(a), y = gy(a) + 1;
	int left = bts(ln, y - 1);
	int up = bts(ln, y);
	if (left == 0 && up == 0)
	{
		if (block[bk(x, y + 1)] || block[bk(x + 1, y)])
			return;
		chg(ln, y - 1, LP);
		chg(ln, y, RP);
		insState(a, stat(x, y, ln));
		return;
	}
	if (left == LP && up == RP)
	{
		if (x != lx || y != ly)
			return;
		chg(ln, y - 1, 0);
		chg(ln, y, 0);
		insState(a, stat(x, y, ln));
		return;
	}
	if (left == RP && up == LP)
	{
		chg(ln, y - 1, 0);
		chg(ln, y, 0);
		insState(a, stat(x, y, ln));
		return;
	}
	if (up == 0)
	{
		if (!block[bk(x + 1, y)])
		{
			chg(ln, y, 0);
			insState(a, stat(x, y, ln));
		}
		if (!block[bk(x, y + 1)])
		{
			chg(ln, y - 1, 0);
			chg(ln, y, left);
			insState(a, stat(x, y, ln));
		}
		return;
	}
	if (left == 0)
	{
		if (!block[bk(x, y + 1)])
		{
			chg(ln, y - 1, 0);
			insState(a, stat(x, y, ln));
		}
		if (!block[bk(x + 1, y)])
		{
			chg(ln, y, 0);
			chg(ln, y - 1, up);
			insState(a, stat(x, y, ln));
		}
		return;
	}
	if (left == LP && up == LP)
	{
		int d = 1, ps = y;
		while (d)
		{
			ps++;
			if (bts(ln, ps) == LP)
				d++;
			if (bts(ln, ps) == RP)
				d--;
		}
		chg(ln, ps, LP);
		chg(ln, y - 1, 0);
		chg(ln, y, 0);
		insState(a, stat(x, y, ln));
		return;
	}
	if (left == RP && up == RP)
	{
		int d = 1, ps = y - 1;
		while (d)
		{
			ps--;
			if (bts(ln, ps) == LP)
				d--;
			if (bts(ln, ps) == RP)
				d++;
		}
		chg(ln, ps, RP);
		chg(ln, y - 1, 0);
		chg(ln, y, 0);
		insState(a, stat(x, y, ln));
		return;
	}
}
void bfs()
{
	q.push(stat((ll)1, (ll)0, 0));
	omp[0] = 1;
	int ox = 1, oy = 0;
	while (!q.empty())
	{
		int x = gx(q.front()), y = gy(q.front());
		if (x != ox || y != oy)
		{
			refresh();
			ox = x;
			oy = y;
		}
		if (x == lx && y == ly && gl(q.front()) == 0)
		{
			cout<<omp[q.front()]<<endl;
			exit(0);
		}
		else if (x > n)
		{
		}
		else if (y == m)
			genOtherLine(q.front());
		else if (block[bk(x, y + 1)])
			mkbstate(q.front());
		else
			mkstate(q.front());
		q.pop();
	}
}
void init()
{
	cin>>n>>m;
	for (int i = 0; i <= max(n, m) + 1; i++)
		block[bk(0, i)] = block[bk(i, 0)] = block[bk(n + 1, i)] = block[bk(i, m + 1)] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			char c;
			cin>>c;
			if (c == '*')
				block[bk(i, j)] = 1;
			else
			{
				lx = i;
				ly = j;
			}
		}
	}
}
int main()
{
	init();
	bfs();
	cout<<"0"<<endl;
	return 0;
}
