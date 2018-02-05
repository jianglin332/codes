#include <cstdio>
#include <stack>
#include <iostream>
using namespace std;
#include <cstring>
#define LR 0
#define L 1
#define R 2
#define RL 3
int sst;
int k;
const int maxn = 100007;
const long long mu = 3001;
char t[10][7];
void dec(int *a, int b, int f)
{
	int d = 0;
/*	printf("DEC:\n\t");
	for (int i = 0; i < 10; i++)
		printf("%d ", a[i]);
	printf("\n");
*/	stack<int> sk;
//	printf("DEC:\n\t");
	for (int i = 0; i < 10; i++)
	{
		int n = b & 3;
//		printf("%d ", n);
		if (n == LR)
			a[i] = (f >> i) & 1 ? ++d : 0;
		else if (n == L)
		{
			a[i] = ++d;
			sk.push(d);
		}
		else if (n == R)
		{
			a[i] = sk.top();
			sk.pop();
		}
		else if (n == RL)
		{
			a[i] = sk.top();
		}
		b >>= 2;
	}
/*	printf("NOW:\n\t");
	for (int i = 0; i < 10; i++)
		printf("%d ", a[i]);
	printf("\nFIRE:\n\t");
	for (int i = 0; i < 10; i++)
		printf("%d ", f >> i & 1);
	printf("\n");
*/}
int enc(const int *oa)
{
	int a[10];
	memcpy(a, oa, sizeof(a));
	int ret = 0;
	int al[12] = {0};
	bool vd[12] = {0};
	for (int i = 0; i < 10; i++)
	{
		al[a[i]]++;
	}
/*	printf("ORIG:\n\t");
	for (int i = 0; i < 10; i++)printf("%d ", a[i]);
	printf("\n");
*/	for (int i = 0; i < 10; i++)
	{
		al[a[i]]--;
//		printf("\t\t%d %d\n", a[i], al[a[i]]);
		if (((!vd[a[i]]) && !al[a[i]]) || !a[i])
			a[i] = LR;
		else if (!vd[a[i]])
			vd[a[i]] = 1, a[i] = L;
		else if (al[a[i]])
			a[i] = RL;
		else
			a[i] = R;
	}
	for (int i = 9; i >= 0; i--)
	{
		ret <<= 2;
		ret |= a[i];
	}
	return ret;
}
struct h_t
{
	int hd[maxn], nx[maxn], sz, fire[maxn], state[maxn];
	void clear()
	{
		memset(hd, -1, sizeof(hd));
//		printf("%d\n", sz);
//		sst += sz;
		sz = 0;
	}
	int h(int a)
	{
		return ((a * mu) ^ 0xDEADBEEF) % maxn;
	}
	void push(int stat, int fir)
	{
		int hs = h(stat);
		for (int i = hd[hs]; i != -1; i = nx[i])
		{
			if (stat == state[i] && fir == fire[i])
			{
				return;
			}
		}
		state[sz] = stat;
		fire[sz] = fir;
		nx[sz] = hd[hs];
		hd[hs] = sz++;
	}
	/*void del(int stat, int fir)
	{
		int t[10];
		dec(t, stat);
		for (int i = 0; i < sz; i++)
		{
			int u[10];
			dec(u, state[i]);
			if (t)
		}
	}*/
}ht[2];
void init()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 6; j++)
			cin >> t[i][j];
}
void proc(int x, int y, bool cur)
{
	ht[!cur].clear();
	for (int i = 0; i < ht[cur].sz; i++)
	{
		int st[10] = {0};
		if (y && x == 0)
		{
			ht[cur].state[i] <<= 2;
			ht[cur].state[i] &= 0xFFFFF;
			ht[cur].fire[i] <<= 1;
			ht[cur].fire[i] &= 0x3FF;
		}
		dec(st, ht[cur].state[i], ht[cur].fire[i]);
		int u = st[x];
		int l = st[x + 1];
		int fire = ht[cur].fire[i];
		bool fu = fire & (1 << x);
		bool fl = fire & (1 << x + 1);
		if (t[x][y] == '.')
		{
			st[x] = st[x + 1] = 0;
			fire &= ~(3 << x);
			if (fire)
				ht[!cur].push(enc(st), fire);
		}
		else if (t[x][y] == '+')
		{
			int fd = fu || fl;
			if (l && u && l != u)
				for (int i = 0; i < 10; i++)
					if (st[i] == l || st[i] == u)
					{
						st[i] = l;
						fire |= fd << i;
					}
			if (!u && !l)
				st[x] = st[x + 1] = 11;
			else
				st[x] = st[x + 1] = l ? l : u;
			fire |= fd * 3 << x;
			if (fire)
				ht[!cur].push(enc(st), fire);
		}
		else if (t[x][y] == '-')
		{
			if (u)
			{
				st[x + 1] = u;
				st[x] = 0;
				fire &= ~(1 << x);
				if (fu)
					fire |= 1 << x + 1;
				else
					fire &= ~(1 << x + 1);
				if (fire)
					ht[!cur].push(enc(st), fire);
			}
			if (l)
			{
				st[x + 1] = 0;
				st[x] = l;
				fire &= ~(1 << x + 1);
				if (fl)
					fire |= 1 << x;
				else
					fire &= ~(1 << x);
				if (fire)
					ht[!cur].push(enc(st), fire);
			}
			else if (!u)
			{
				ht[!cur].push(enc(st), fire);
			}
		}
		else if (t[x][y] == 'L')
		{
			int fd = fu || fl;
			st[x + 1] = l;
			st[x] = 0;
			fire &= ~(1 << x);
			if (fl)
				fire |= 1 << x + 1;
			else
				fire &= ~(1 << x + 1);
			if (fire)
				ht[!cur].push(enc(st), fire);
			st[x + 1] = 0;
			st[x] = u;
			fire &= ~(1 << x + 1);
			if (fu)
				fire |= 1 << x;
			else
				fire &= ~(1 << x);
			if (fire)
				ht[!cur].push(enc(st), fire);
			st[x] = st[x + 1] = 11;
			fire &= ~(3 << x);
			if (fire)
				ht[!cur].push(enc(st), fire);
			if (l && u && l != u)
				for (int i = 0; i < 10; i++)
					if (st[i] == l || st[i] == u)
					{
						st[i] = l;
						fire |= fd << i;
					}
			st[x] = st[x + 1] = 0;
			fire &= ~(3 << x);
			if (fire)
				ht[!cur].push(enc(st), fire);
		}
		else if (t[x][y] == 'T')
		{
			int fd = fu || fl;
			if (l)
			{
				st[x + 1] = l;
				st[x] = l;
				if (fl)
					fire |= 3 << x;
				else
					fire &= ~(3 << x);
				if (fire)
					ht[!cur].push(enc(st), fire);
			}
			if (u)
			{
				st[x + 1] = u;
				st[x] = u;
				if (fu)
					fire |= 3 << x;
				else
					fire &= ~(3 << x);
				if (fire)
					ht[!cur].push(enc(st), fire);
			}
			else if (!l)
			{
				st[x] = st[x + 1] = 11;
				fire &= ~(3 << x);
				ht[!cur].push(enc(st), fire);
			}
			if (l && u && l != u)
				for (int i = 0; i < 10; i++)
					if (st[i] == l || st[i] == u)
					{
						st[i] = l;
						fire |= fd << i;
					}
			if (fd)
			{
				st[x] = 0;
				fire &= ~(1 << x);
				int tt = l ? l : u;
				st[x + 1] = tt;
				fire |= 1 << x + 1;
				ht[!cur].push(enc(st), fire);
				st[x + 1] = 0;
				fire &= ~(1 << x + 1);
				st[x] = tt;
				fire |= 1 << x;
				ht[!cur].push(enc(st), fire);
			}
			else
			{
				st[x] = st[x + 1] = 0;
				fire &= ~(3 << x);
				ht[!cur].push(enc(st), fire);
			}
		}
	}
}
void work()
{
	bool cur;
	ht[cur].clear();
	ht[cur].push(0, 1 << k);
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 9; j++)
		{
			proc(j, i, cur), cur = !cur;
		}
	int mx = 0, tmp = 0;
	for (int i = 0; i < ht[cur].sz; i++, mx = mx > tmp ? mx : tmp, tmp = 0)
	{
/*		for (int j = 0; j < 9; j++)
			printf("%d", ht[cur].fire[i] >> j & 1);
		printf("\n");
*/		for (int j = 0; j < 9; j++)
			tmp += (ht[cur].fire[i] >> j) & 1;
	}
	printf("%d\n", mx);
}
int main()
{
	while (scanf("%d\n", &k) != EOF)
	{
		init();
		work();
	}
	return 0;
}
