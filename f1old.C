/*
URAL 1519
Formula 1
http://acm.timus.ru/problem.aspx?space=1&num=1519
*/

#ifndef ONLINE_JUDGE
#define ll long long
#endif
#ifdef ONLINE_JUDGE
#define ll __int64
#endif
#include <cstdio>
#include <iostream>
#include <queue>
#include <map>
#include <cstdlib>
#include <cstring>
using namespace std;
int n, m, p;
bool block[15][15];
struct line
{
	int l[15];
	line()
	{
		memset(l, 0, sizeof(l));
	}
};
ll lineToLL(line a)
{
	ll ans = 0;
	for (int i = 0, d = 0; i <= m; i++, d += 4)
	{
		ans += (ll)(a.l[i]) << d;
	}
	return ans;
}
line llToLine(ll a)
{
	line ans;
	for (int i = 0; i <= m; i++)
	{
		ans.l[i] = a & 15;
		a >>= 4;
	}
	return ans;
}
struct state
{
	int x, y;
	ll l;
	state(){x = y = l = 0;}
	state(int _x, int _y, ll st):x(_x), y(_y), l(st){}
	bool operator<(const state a)const
	{
		if (x < a.x)
			return 1;
		if (x > a.x)
			return 0;
		if (y < a.y)
			return 1;
		if (y > a.y)
			return 0;
		if (l < a.l)
			return 1;
		return 0;
	}
};
queue<state> q;
map<state, ll> mp;
inline void insState(state fr, state to)
{
	if (!mp[to])
		q.push(to);
	mp[to] += mp[fr];
}
inline void mkbstate(state a)
{
	line ln = llToLine(a.l);
	if (ln.l[a.y] || ln.l[a.y + 1])
		return;
	insState(a, state(a.x, a.y + 1, a.l));
}
inline void genOtherLine(state a)
{
	line ln = llToLine(a.l);
	for (int i = m; i > 0; i--)
	{
		ln.l[i] = ln.l[i - 1];
	}
	ln.l[0] = 0;
	insState(a, state(a.x + 1, 0, lineToLL(ln)));
}
inline line connect(line od, int l, int r)
{
	line ret;
	if (l == r)
		return ret;
	if (l > r)
		swap(l, r);
	for (int i = 0; i <= m; i++)
	{
		if (od.l[i] == r)
			ret.l[i] = l;
		else if (od.l[i] > r)
			ret.l[i] = od.l[i] - 1;
		else
			ret.l[i] = od.l[i];
	}
}
inline line news(line od, int pos)
{
	line ret;
	int mx = 0;
	for (int i = 0; i <= m; i++)
	{
		if (i == pos)
		{
			ret.l[i] = ret.l[i + 1] = mx + 1;
			for (int j = i + 2; j <= m; j++)
			{
				if (od.l[j] > mx)
					ret.l[j] = od.l[j] + 1;
				else
					ret.l[j] = od.l[j];
			}
			break;
		}
		if (mx < od.l[i])
			mx = od.l[i];
		ret.l[i] = od.l[i];
	}
	return ret;
}
int lx, ly;
inline void mkstate(state a)
{
	line ln = llToLine(a.l);
	int left = ln.l[a.y];
	int up = ln.l[a.y + 1];
	int x = a.x, y = a.y + 1;
	if (left && up && (left != up || (left == up && a.x == lx && a.y == ly - 1)))
	{
		line nw = connect(ln, left, up);
		nw.l[y] = nw.l[y - 1] = 0;
		insState(a, state(x, y, lineToLL(nw)));
	}
	else if (!(left || up))
	{
		line nw = news(ln, a.y);
		if (!(block[x + 1][y] || block[x][y + 1]))insState(a, state(x, y, lineToLL(nw)));
	}
	else if (left && !up)
	{
		line nw = ln;
		nw.l[a.y + 1] = 0;
		if (!block[x + 1][y])insState(a, state(a.x, a.y + 1, lineToLL(nw)));
		nw.l[a.y + 1] = left;
		nw.l[a.y] = 0;
		if (!block[x][y + 1])insState(a, state(a.x, a.y + 1, lineToLL(nw)));
	}
	else if (up && !left)
	{
		line nw = ln;
		nw.l[a.y] = 0;
		if (!block[x][y + 1])insState(a, state(a.x, a.y + 1, lineToLL(nw)));
		nw.l[a.y] = up;
		nw.l[a.y + 1] = 0;
		if (!block[x + 1][y])insState(a, state(a.x, a.y + 1, lineToLL(nw)));
	}
}
void disp(line a)
{
	for (int i = 0; i <= m; i++)
		printf("%d ", a.l[i]);
	printf("\n");
}
ll bfs()
{
	q.push(state(1, 0, 0));
	mp[state(1, 0, 0)] = 1;
	while (!q.empty())
	{
		int x = q.front().x, y = q.front().y;
		if (x == n && y == m && q.front().l == 0)
		{
			return mp[q.front()];
		}
		else if (x > n)
		{
		}
		else if (y == m)
			genOtherLine(q.front());
		else if (block[x][y + 1])
			mkbstate(q.front());
		else
			mkstate(q.front());
		q.pop();
	}
	return 0;
}
void init()
{
	cin>>n>>m;
	for (int i = 0; i <= max(n, m) + 1; i++)
		block[0][i] = block[i][0] = block[n + 1][i] = block[i][m + 1] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			char c;
			cin>>c;
			if (c == '*')
				block[i][j] = 1;
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
	cout<<bfs()<<endl;
	return 0;
}

