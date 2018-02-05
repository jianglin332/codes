#include <stdio.h>
#include <string.h>
#include <math.h>
#include <set>
#include <algorithm>
using namespace std;
double l2, l3, l5;
long long p, q;
struct num
{
	int m2, m3, m5;
	long long real;
	num(int a = 0, int b = 0, int c = 0, long long r = 1):m2(a), m3(b), m5(c), real(r){}
	bool operator<(const num &a) const
	{
		if (m2 == a.m2 && m3 == a.m3 && m5 == a.m5)
			return 0;
		return l2 * m2 + l3 * m3 + l5 * m5 < l2 * a.m2 + l3 * a.m3 + l5 * a.m5;
	}
	num operator*(const num &a) const
	{
		return num(m2 + a.m2, m3 + a.m3, m5 + a.m5, real * a.real % p);
	}
	bool cand(const num &a) const
	{
		return m2 >= a.m2 && m3 >= a.m3 && m5 >= a.m5;
	}
}lu[101010];
int nl;
set<num> st;
num mu[5];
int nm;
const int maxn = 10101010;
int f[maxn];
int l[maxn], r[maxn], lch[maxn], rch[maxn], dn[maxn], nn = 1;
int mt3(int fr, int to)
{
	int nw = nn++;
	l[nw] = fr;
	r[nw] = to;
	if (fr != to)
	{
		lch[nw] = mt3(fr, (fr + to) / 2);
		rch[nw] = mt3((fr + to) / 2 + 1, to);
	}
	return nw;
}
int mt2(int fr, int to, int m3)
{
	int nw = nn++;
	l[nw] = fr;
	r[nw] = to;
	if (fr != to)
	{
		lch[nw] = mt2(fr, (fr + to) / 2, m3);
		rch[nw] = mt2((fr + to) / 2 + 1, to, m3);
	}
	dn[nw] = mt3(0, m3);
	return nw;
}
int mt1(int fr, int to, int m2, int m3)
{
	int nw = nn++;
	l[nw] = fr;
	r[nw] = to;
	dn[nw] = mt2(0, m2, m3);
	if (fr != to)
	{
		lch[nw] = mt1(fr, (fr + to) / 2, m2, m3);
		rch[nw] = mt1((fr + to) / 2 + 1, to, m2, m3);
	}
	return nw;
}


int combine(long long a, long long b)
{
	return ((a * b) % p * q + a + b) % p;
}
void ins3(int nw, int t5, int d)
{
	f[nw] = combine(f[nw], d);
	if (l[nw] != r[nw])
	{
		if (l[rch[nw]] > t5)
			ins3(lch[nw], t5, d);
		else
			ins3(rch[nw], t5, d);
	}
}
void ins2(int nw, int t3, int t5, int d)
{
	if (l[nw] != r[nw])
	{
		if (l[rch[nw]] > t3)
			ins2(lch[nw], t3, t5, d);
		else
			ins2(rch[nw], t3, t5, d);
	}
	ins3(dn[nw], t5, d);
}
void ins1(int nw, int t2, int t3, int t5, int d)
{
	if (l[nw] != r[nw])
	{
		if (l[rch[nw]] > t2)
			ins1(lch[nw], t2, t3, t5, d);
		else
			ins1(rch[nw], t2, t3, t5, d);
	}
	ins2(dn[nw], t3, t5, d);
}
int a2, b2, a3, b3, a5, b5;
int q3(int nw, int fl = 0)
{
	if (a5 <= l[nw] && r[nw] <= b5)
	{
		if (fl)
			printf("\t\t(%d %d)\n\t\t\t%d\n", l[nw], r[nw], f[nw]);
		return f[nw];
	}
	int rt = 0;
	if (a5 < l[rch[nw]])
		rt = q3(lch[nw], fl);
	if (b5 >= l[rch[nw]])
		rt = combine(rt, q3(rch[nw], fl));
	return rt;
}
int q2(int nw, int fl = 0)
{
	if (a3 <= l[nw] && r[nw] <= b3)
	{
		if (fl)
			printf("\t(%d %d)\n", l[nw], r[nw]);
		return q3(dn[nw], fl);
	}
	int rt = 0;
	if (a3 < l[rch[nw]])
		rt = q2(lch[nw], fl);
	if (b3 >= l[rch[nw]])
		rt = combine(rt, q2(rch[nw], fl));
	return rt;
}
int q1(int nw, int fl = 0)
{
	if (a2 <= l[nw] && r[nw] <= b2)
	{
		if (fl)
			printf("(%d %d)\n", l[nw], r[nw]);
		return q2(dn[nw], fl);
	}
	int rt = 0;
	if (a2 < l[rch[nw]])
		rt = q1(lch[nw], fl);
	if (b2 >= l[rch[nw]])
		rt = combine(rt, q1(rch[nw], fl));
	return rt;
}
int main()
{
	freopen("volunteer.in", "r", stdin);
	freopen("volunteer.out", "w", stdout);
	int t, u = 0;
	scanf("%d", &t);
	u = t;
	l2 = log(2), l3 = log(3), l5 = log(5);
	if (t)
		mu[nm++] = num(1, 0, 0, 2);
	scanf("%d", &t);
	u = u * 2 + t;
	if (t)
		mu[nm++] = num(0, 1, 0, 3);
	scanf("%d", &t);
	u = u * 2 + t;
	if (t)
		mu[nm++] = num(2, 0, 0, 4);
	scanf("%d", &t);
	u = u * 2 + t;
	if (t)
		mu[nm++] = num(0, 0, 1, 5);
	scanf("%d", &t);
	u = u * 2 + t;
	if (t)
		mu[nm++] = num(1, 1, 0, 6);
	scanf("%lld%lld", &p, &q);
	st.insert(num());
	int m2 = 0, m3 = 0, m5 = 0;
	while (!st.empty())
	{
		num t = *(st.begin());
		st.erase(t);
		lu[nl++] = t;
		m2 = max(m2, t.m2);
		m3 = max(m3, t.m3);
		m5 = max(m5, t.m5);
		for (int i = 0; i < nm; i++)
			st.insert(t * mu[i]);
		if (nl > 100000)
			break;
	}
	set<num>().swap(st);
	int t3 = 1;
	if (u == 1 || u == 3)
		t3 = 0;
	mt1(0, m2, m3 * t3, m5);
	for (int i = 1; i < nl; i++)
		ins1(1, lu[i].m2, lu[i].m3 * t3, lu[i].m5, lu[i].real);
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int a, b;
	scanf("%d%d", &a, &b);
		a2 = lu[a].m2, a3 = lu[a].m3 * t3, a5 = lu[a].m5;
		b2 = lu[b].m2, b3 = lu[b].m3 * t3, b5 = lu[b].m5;
/*		int t = q1(1);
		if (t == 3233084)
		{
			a2 = 0, b2 = 1, a3 = 354, b3 = 354, a5 = 0, b5 = 0;
			printf("%d", q1(1));
		}
*/		printf("%d\n", q1(1));
	}
	return 0;
}

