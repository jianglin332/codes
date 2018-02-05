#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;
ll nx[101010], ny[101010], mx[101010], my[101010];
ll x[101010 * 2], y[101010 * 2], np;
double ang[101010 * 2];
int rk[101010 * 2];
int st[101010 * 2], ns;
ll cros(ll xa, ll ya, ll xb, ll yb)
{
	return xa * yb - xb * ya;
}
ll cross(int a, int b)
{
	return cros(x[a], y[a], x[b], y[b]);
}
ll toleft(int a, int b, int c)
{
	return cross(a, b) + cross(b, c) + cross(c, a);
}
bool cmp(int a, int b)
{
	return ang[a] < ang[b];
}
void graham()
{
	for (int i = 1; i < np; i++)
		if (x[i] < x[0] || (x[i] == x[0] && y[i] < y[0]))
			swap(x[i], x[0]), swap(y[i], y[0]);
	for (int i = 1; i < np; i++)
		ang[i] = atan2(y[i] - y[0], x[i] - x[0]);
	for (int i = 1; i < np; i++)
		rk[i] = i;
	sort(rk + 1, rk + np, cmp);
	rk[np++] = 0;
	ns = 0;
	st[++ns] = rk[1];
	for (int i = 2; i < np; i++)
	{
		while (ns && toleft(st[ns - 1], st[ns], rk[i]) <= 0)
			ns--;
		st[++ns] = rk[i];
	}
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%lld%lld", nx + i, ny + i);
	memcpy(x, nx, sizeof(nx)), memcpy(y, ny, sizeof(ny));
	np = n;
	graham();
	n = ns;
	for (int i = 0; i <= ns; i++)
		nx[i] = x[st[i]], ny[i] = y[st[i]];
	for (int i = 0; i < m; i++)
		scanf("%lld%lld", mx + i, my + i);
	np = m;
	memcpy(x, mx, sizeof(mx)), memcpy(y, my, sizeof(my));
	graham();
	m = ns;
	for (int i = 0; i <= ns; i++)
		mx[i] = x[st[i]], my[i] = y[st[i]];
	int nn = 0, nm = 0;
	int na = 0;
	x[0] = nx[0] + mx[0], y[0] = ny[0] + my[0];
	while (nn < n || nm < m)
	{
		if (nm == m || (nn < n && cros(nx[nn + 1] - nx[nn], ny[nn + 1] - ny[nn], mx[nm + 1] - mx[nm], my[nm + 1] - my[nm]) > 0))
			nn++;
		else
			nm++;
		x[++na] = nx[nn] + mx[nm], y[na] = ny[nn] + my[nm];
	}
	ll ans = 0;
	for (int i = 0; i < na; i++)
		ans += cross(i, i + 1);
	printf("%lld", abs(ans));
	return 0;
}
