#include <cstdio>
#include <cstring>
#include <queue>
#include <cctype>
#define wt 1
#define bl 2
using namespace std;
const long long mu = 5003;
const int mod = 10007;
int pr[65][mod];
char cl[65][mod];
char mp[10][10];
char tt[65];
int n, m;
struct hash_table
{
	int hd[mod], nx[mod], st[mod], num[mod], size, col[mod];
	int hs(int a)
	{
		return (a * mu) % mod;
	}
	void clear()
	{
		memset(hd , -1, sizeof(hd));
		size = 0;
	}
	void ins(int state, int amt, int color, int pos, int par, char c)
	{
		for (int i = hd[hs(state)]; i != -1; i = nx[i])
		{
			if (state == st[i] && color == col[i])
			{
				num[i] += amt;
				return;
			}
		}
		pr[pos][size] = par;
		cl[pos][size] = c;
		st[size] = state;
		col[size] = color;
		num[size] = amt;
		nx[size] = hd[hs(state)];
		hd[hs(state)] = size++;
	}
}ht[2];
int lti(int *a)
{
	int rp[10] = {0}, nr = 0, ret = 0;
	memset(rp, -1, sizeof(rp));
	for (int i = 0; i < n; i++)
	{
		if (rp[a[i]] == -1)
			rp[a[i]] = nr++;
		ret <<= 3;
		ret |= rp[a[i]];
		a[i] = rp[a[i]];
	}
	return ret;
}
void itl(int *a, int src)
{
	for (int i = n - 1; i >= 0; i--)
		a[i] = src & 7, src >>= 3;
}
void init()
{
	scanf("%d%d", &m, &n);
	for (int i = 0; i < m; i++)
		scanf("%s", mp[i]);
}
void process(int x, int y, bool c, int rec)
{
	for (int i = 0; i < ht[rec].size; i++)
	{
		int st = ht[rec].st[i];
		int col = ht[rec].col[i];
		int cs[10];
		bool up = x ? (c == (col >> y & 1)): 0;
		bool left = y ? (c == (col >> (y - 1) & 1)) : 0;
		bool lu = (c == (col >> n & 1));
		if (up && left && lu)
			continue;
		if (x == m - 1 && y == n - 1 && lu && !(up || left))
			continue;
		itl(cs, st);
		if (x && !up)
		{
			int a = 0, b = 0;
			for (int j = 0; j < n; j++)
			{
				if (cs[j] == cs[y])
					a++;
				if (c != (col >> j & 1))
					b++;
			}
			if (a == 1)
			{
				if (b > 1 || x < m - 1 || y < n - 2)
					continue;
			}
		}
		if (up && left)
		{
			if (cs[y] != cs[y - 1])
				for (int j = 0, t = cs[y]; j < n; j++)
					if (cs[j] == t)
						cs[j] = cs[y - 1];
		}
		if ((!up) && left)
			cs[y] = cs[y - 1];
		if (!(up || left))
			cs[y] = n;
		if (col & (1 << y))
			col |= 1 << n;
		else
			col &= ~(1 << n);
		if (c)
			col |= 1 << y;
		else
			col &= ~(1 << y);
		ht[rec ^ 1].ins(lti(cs), ht[rec].num[i], col, x * n + y, i, c ? '#' : 'o');
	}
}
char ac[10][10];
void work()
{
	int rec = 0;
	ht[rec].clear();
	ht[rec].ins(0, 1, 0, 0, 0, 0);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
//			printf("%d %d : \n", i, j);
			ht[rec ^ 1].clear();
			if (mp[i][j] != '#')
				process(i, j, 0, rec);
			if (mp[i][j] != 'o')
				process(i, j, 1, rec);
			rec ^= 1;
		}
	int ans = 0, vl;
	for (int i = 0; i < ht[rec].size; i++)
	{
		int cs[10];
		bool flg = 0;
		itl(cs, ht[rec].st[i]);
		for (int j = 0; j < n; j++)
		{
			if (cs[j] > 1)
				flg = 1;
		}
		if (flg)
			continue;
		ans += ht[rec].num[i];
//		printf("%d %d\n", ht[rec].st[i], ht[rec].col[i]);
		vl = i;
	}
	printf("%d\n", ans);
	if (ans)
	{
		for (int i = m - 1, k = vl; i >= 0; i--)
		{
			for (int j = n - 1; j >= 0; j--)
			{
				ac[i][j] = cl[i * n + j][k];
				k = pr[i * n + j][k];
			}
		}
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
				printf("%c", ac[i][j]);
			printf("\n");
		}
	}
	printf("\n");
}
int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		init();
		work();
	}
	return 0;
}
