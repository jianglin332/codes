#include <cstdio>
#include <cstring>
int c[10][10];
char ac[10][10];
int m, n;
int mx[3], my[3];
int ans;
typedef long long state;
#define stat(x, y, z) ((x << 38) | (y << 33) | z)
#define gx(x) ((x >> 38) & 15)
#define gy(x) ((x >> 33) & 15)
#define gs(x) (int(x))
struct stt
{
	int v[8];
};
int sti(stt a)
{
	int ret = 0;
	for (int i = 0; i <= n; i++)
}
stt its(int a)
{
}
const long long mu = 70001;
struct node
{
	long long n;
	int v;
	node *nx;
	node(){}
	node(long long nn, int vv, node *xx):n(nn), v(vv), nx(xx){}
}
struct hash_table
{
	node *ns[150001];
	hash_table()
	{
		memset(ns, 0, sizeof(ns));
	}
	int hash(long long a)
	{
		return (a * mu) % 150001;
	}
	void insert(long long n, int v)
	{
		int hs = hash(n);
		for (node *i = ns[hs]; i; i = i->nx)
		{
			if (i->n == n)
			{
				i->v += v;
				return;
			}
		}
		ns[hs] = new node(n, v, ns[hs]);
	}
	int operator[](int n)
	{
		for (node *i = ns[hash(n)]; i; i = i->nx)
			if (i->n == n)
				return i->v;
		return 0;
	}
}ht, pr;
void init()
{
	memset(c, 0, sizeof(c));
	memset(ac, 0, sizeof(ac));
	memset(mx, -1, sizeof(mx));
	memset(my, -1, sizeof(my));
	ans = 0;
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			char ch;
			while (ch != '.' && ch != '#' && ch != 'o')
				scanf("%c", &ch);
			if (ch == '#')
				c[i][j] = 1;
			if (ch == 'o')
				c[i][j] = 2;
			if (c[i][j])
				mx[c[i][j]] = i, my[c[i][j]] = j;
		}
}
void disp()
{
	printf("%d", ans);
	if (!ans)
	{
		printf("\n");
		return;
	}
	for (int i = 0; i < n; i++)
		puts(ac[i]);
	printf("\n");
}
void src()
{
	queue<state> q;
	q.push(stat(1, 0, 0));
	while (!q.empty())
	{
		int x = gx(q.front()), y = gy(q.front()), st = gs(q.front());
		if ()
	}
}
void work()
{
	init();
	src();
	disp();
}
int main()
{
	int t;
	for (scanf("%d", &t); t; t--)
		work();
	return 0;
}
