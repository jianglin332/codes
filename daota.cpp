#include <cstdio>
#include <algorithm>
using namespace std;
const long long mod = 998244353;
long long pow(long long a, long long p)
{
	if (!p)
		return 1;
	long long t = pow(a, p / 2);
	return ((t * t) % mod * (p % 2 ? a : 1)) % mod;
}
struct ll
{
	long long a;
	ll():a(0){}
	ll(const long long b)
	{
		a = b % mod;
	}
	ll operator+(const ll b) const
	{
		return b.a + a;
	}
	ll operator-(const ll b) const
	{
		return a + mod - b.a;
	}
	ll operator*(const ll b) const
	{
		return b.a * a;
	}
	ll operator/(const ll b) const
	{
		return a * pow(b.a, mod - 2);
	}
	ll operator-()
	{
		return mod - a;
	}
};
int v[101010], d[101010], w[101010];
bool vd[101010];
bool in[101010];
void dfs(int a)
{
	vd[a] = 1;
	in[a] = 1;
	if (!vd[d[a]])
		dfs(d[a]);
	else if (in[d[a]])
	{
		int nw = d[a], mn = w[a];
		while (a != nw)
		{
			mn = min(w[nw], mn);
			nw = d[nw];
		}
		while (w[nw] != mn)
		{
			nw = d[nw];
		}
		w[nw] = 0;
	}
	in[a] = 0;
}
long long n, c, r1, r2, m, p1, p2, b, q1, q2;
struct matrix
{
	ll v[11][11];
	matrix operator*(const matrix &a) const
	{
		matrix ret = {0};
		for (int i = 0; i <= c; i++)
			for (int j = 0; j <= c; j++)
				for (int k = 0; k <= c; k++)
					ret.v[i][j] = ret.v[i][j] + v[k][j] * a.v[i][k];
		return ret;
	}
}mu[64], org;
int main()
{
	freopen("daota.in", "r", stdin);
	freopen("daota.out", "w", stdout);
	scanf("%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld", &n, &c, &r1, &r2, &m, &p1, &p2, &b, &q1, &q2);
	ll r = r1;
	r = r / r2;
	ll p = p1;
	p = p / p2;
	ll q = q1;
	q = q / q2;
	for (int i = 1; i <= m; i++)
		scanf("%d", v + i);
	for (int i = 1; i <= m; i++)
		scanf("%d", d + i);
	for (int i = 1; i <= m; i++)
		scanf("%d", w + i);
	for (int i = 1; i <= m; i++)
		if (!vd[i])
			dfs(i);
	long long t = 0;
	for (int i = 1; i <= m; i++)
		t += v[i] + w[i];
	t %= mod;
	ll a = p / (-p + 1) * b + 1;
	mu[0].v[0][0] = -r + 1;
	mu[0].v[0][c - 1] = r;
	mu[0].v[0][c] = 1;
	for (int i = 1; i < c; i++)
		mu[0].v[i][i - 1] = 1;
	mu[0].v[c][c] = 1;
	for (int i = 1; i < 64; i++)
		mu[i] = mu[i - 1] * mu[i - 1];
	for (int i = 1; i < c; i++)
		org.v[c - i - 1][0] = r * (a * i + t) + (-r + 1) * (org.v[c - i][0] + ll(1) / (-q + 1) * a);
	if (n < c)
	{
		printf("%lld", (org.v[c - n][0] + ll(1) / (-q + 1) * a).a);
		return 0;
	}
	org.v[c][0] = r * c * a + r * t + (-r + 1) / (-q + 1) * a;
	n -= c;
	for (int i = 0; i < 64; i++)
		if (n & (1ll << i))
			org = org * mu[i];
	printf("%lld", (org.v[0][0] + ll(1) / (-q + 1) * a).a);
	return 0;
}
