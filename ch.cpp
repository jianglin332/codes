#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cmath>
using namespace std;
int s[101010], t[101010], ns = -1, nt = -1;
typedef long long ll;
char buf[2020202];
int g()
{
	int ret = 0, mt = 1;
	static char *nw = buf;
	while (*nw != '-' && !isdigit(*nw))
		nw++;
	if (*nw == '-')
		mt = -1, nw++;
	while (isdigit(*nw))
		ret = ret * 10 + *(nw++) - '0';
	return ret * mt;
}
struct pt
{
	ll x, y;
	pt(){}
	pt(ll a, ll b):x(a), y(b){}
}ps[101010];
typedef const pt & vt;
int ltl;
inline ll det(vt a, vt b)
{
	return a.x * b.y - a.y * b.x;
}
inline ll toleft(vt a, vt b, vt c)
{
	return det(a, b) + det(b, c) + det(c, a);
}
inline bool cl(vt a, vt b)
{
	if (a.y == b.y)
		return a.x < b.x;
	return a.y < b.y;
}
inline long long dist(vt a, vt b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
inline bool cmp(const int a, const int b)
{
	ll t = toleft(ps[ltl], ps[b], ps[a]);
	if (t == 0)
		return dist(ps[ltl], ps[a]) > dist(ps[ltl], ps[b]);
	return t > 0;
}
#define pushs(a) s[++ns] = a
#define pusht(a) t[++nt] = a
#define pops() ns--
#define popt() nt--
int main()
{
	fread(buf, 2000000, 1, stdin);
	int n = g();
	for (int i = 0; i < n; i++)
		ps[i].x = g(), ps[i].y = g();
	for (int i = 0; i < n; i++)
	{
		if (cl(ps[i], ps[ltl]))
		{
			ltl = i;
		}
	}
	for (int i = 0; i < n; i++)
		if (i != ltl)
			pusht(i);
	sort(t, t + nt + 1, cmp);
	pushs(ltl);
	pushs(t[nt]);
	popt();
	while (nt >= 0)
	{
		int nw = t[nt];
		popt();
		while (toleft(ps[s[ns - 1]], ps[s[ns]], ps[nw]) <= 0)
			ns--;
		pushs(nw);
	}
	double ans = 0;
	for (int i = 0; i <= ns; i++)
	{
		printf("%lld %lld\n", ps[s[i]].x, ps[s[i]].y);
		ans += sqrt(dist(ps[s[i]], ps[s[(i + 1) % (ns + 1)]]));
	}
	printf("LENGTH=%.2lf", ans);
	return 0;
}
