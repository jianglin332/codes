#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
long long col[101010];
long long num[101010];
long long rk[101010];
vector<int> vs[101010];
long long rem[101010];
long long sr[101010];
int n;
const int mod = 1e9 + 7;
long long pow(long long a, int t)
{
	if (!t)
		return 1;
	long long d = pow(a, t / 2);
	d = d * d % mod;
	if (t & 1)
		d = d * a % mod;
	return d;
}
long long c(long long a)
{
	return a * (a - 1) / 2 % mod;
}
template <typename T>
void add(T &a, int b)
{
	a += b;
	if (a >= mod)
		a -= mod;
}
int bit[101010];
#define lb(x) ((x) & -(x))
void ad(int p, int x)
{
	while (p <= n)
		bit[p] += x, p += lb(p);
}
int qry(int p)
{
	int t = 0;
	while (p)
		add(t, bit[p]), p -= lb(p);
	return t;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", col + i), num[col[i]]++, vs[col[i]].push_back(i), rk[i] = vs[col[i]].size();
	int s = 0, ps = 0;
	for (int i = 1; i <= 100000; i++)
		add(s, ps * c(num[i]) % mod), add(ps, c(num[i]));
	memcpy(rem, num, sizeof(num));
	int ns = ps;
	for (int i = 1; i <= n; i++)
	{
		add(ns, mod - (rem[col[i]] - 1));
		add(s, mod - (num[col[i]] - rem[col[i]]) * 1ll * (ns + mod - c(rem[col[i]] - 1)) % mod);
		rem[col[i]]--;
	}
	long long d2 = pow(2, mod - 2);
	for (int i = 1; i <= 100000; i++)
		if (num[i] > 300)
		{
			memset(rem, 0, sizeof(rem));
			long long t = num[i];
			for (int j = 1; j <= n; j++)
				if (col[j] == i)
					t--;
				else
				{
					add(s, mod - rem[col[j]] * t % mod);
					add(rem[col[j]], num[i] - t);
				}
			memset(rem, 0, sizeof(rem));
			memset(sr, 0, sizeof(sr));
			t = num[i];
			int u = 0;
			for (int j = n; j; j--)
				if (col[j] == i)
					t--;
				else if (num[col[j]] <= 300)
				{
					add(u, mod - rem[col[j]] * (2 * t + 1) % mod);
					add(u, sr[col[j]]);
					add(u, (num[col[j]] - rk[j]) * t % mod * (t + 1) % mod);
					add(rem[col[j]], t);
					add(sr[col[j]], t * t % mod);
				}
			u = u * d2 % mod;
			add(s, mod - u);
		}
	for (int i = 1; i <= n; i++)
		if (num[col[i]] <= 300)
		{
			int u = qry(i);
			for (int j = 0; vs[col[i]][j] < i; j++)
				add(s, (mod - u + qry(vs[col[i]][j])) % mod), add(s, c(rk[i] - j - 2));
			for (int j = 0; vs[col[i]][j] < i; j++)
				ad(vs[col[i]][j], 1);
		}
	printf("%d", s);
	return 0;
}
