#include <cstdio>
#include <cstdlib>
#include <queue>
#include <set>
#include <map>
#define setb(x, y, z) (x = ((x & ~(7 << ((y) << 2))) | ((z) << ((y) << 2))))
#define bts(x, y) ((x >> ((y) << 2)) & 7)
using namespace std;
long long n;
int k;
typedef int state;
typedef long long ll;
queue<state> q;
map<state, int> mp;
int nm = 1;
int dest;
int c[6] = {1, 1, 1, 3, 16, 125};
struct mat
{
	ll v[60][60];
	mat operator*(const mat &a)
	{
		mat ans = {0};
		for (int k = 0; k <= nm; k++)
		{
			const ll *ak = v[k];
			for (int i = 0; i <= nm; i++)
				if (a.v[i][k])
				{
					ll *iv = ans.v[i];
					ll vi = a.v[i][k];
					for (int j = 0; j <= nm; j++)
						if (ak[j])
						{
							iv[j] += vi * ak[j];
						}
				}
		}
		for (int i = 0; i <= nm; i++)
		{
			ll *av = ans.v[i];
			for (int j = 0; j <= nm; j++)
				if (av[j] >= 65521)
					av[j] %= 65521;
		}
		return ans;
	}
}bz[50], &orig = bz[0], a;
void mks(state o, state a, int tm)
{
	int conv[7] = {0}, nc = 1;
	state ins = 0;
	for (int i = k - 1; i >= 0; i--)
	{
		ins <<= 4;
		if (bts(a, i) && !conv[bts(a, i)])
			conv[bts(a, i)] = nc++;
		ins |= conv[bts(a, i)];
	}
	if (!mp[ins])
	{
		q.push(ins);
		mp[ins] = nm++;
//		for (int i = 0; i < k; i++)
//			printf("%d ", bts(ins, i));
//		printf("\n");
	}
	orig.v[mp[ins]][mp[o]] = tm;
}
void dfs(state o, state st, int to, int tm, int *cnt)
{
	if (to == k + 1)
	{
		mks(o, st, tm);
		return;
	}
	dfs(o, st, to + 1, tm, cnt);
	if (cnt[to])
	{
		for (int i = 1; i < k; i++)
		{
			if (bts(st, i) == to)
				setb(st, i, 6);
		}
		dfs(o, st, to + 1, tm * cnt[to], cnt);
	}
}
void search()
{
	q.push(dest);
	mp[dest] = nm++;
	while (!q.empty())
	{
		state st = q.front();
		int cnt[6] = {0};
		for (int i = 0; i < k; i++)
		{
			cnt[bts(st, i)]++;
		}
		a.v[mp[st]][1] = 1;
		for (int i = 1; i <= k; i++)
			a.v[mp[st]][1] *= c[cnt[i]];
		dfs(st, ((st << 4) | 6), 1, 1, cnt);
		q.pop();
	}
//	printf("%d\n", nm);
//	exit(0);
}
int main()
{
	scanf("%d%lld", &k, &n);
	for (int i = 0; i < k; i++)
	{
		dest <<= 4;
		dest |= 1;
	}
	search();
	n -= k;
	for (int i = 1; i < 50; i++)
		bz[i] = bz[i - 1] * bz[i - 1];
	for (int i = 0; i < 50; i++)
		if (n & ((long long)1 << i))
			a = a * bz[i];
/*	for (int i = 0; i <= nm; i++)
	{
		for (int j = 0; j <= nm; j++)
			printf("%d ", bz[0].v[i][j]);
		printf("\n");
	}*/
	printf("%d", a.v[mp[dest]][1]);
}
