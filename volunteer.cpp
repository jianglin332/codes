#include <stdio.h>
#include <string.h>
#include <math.h>
#include <set>
#include <algorithm>
using namespace std;
double lg2, lg3, lg5;
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
		return lg2 * m2 + lg3 * m3 + lg5 * m5 < lg2 * a.m2 + lg3 * a.m3 + lg5 * a.m5;
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
const int maxm = 202020;
int f[maxn];
int l2[maxm], r2[maxm], l3[maxm], r3[maxm], l5[maxm], r5[maxm];
int lch2[maxm], rch2[maxm], lch3[maxm], rch3[maxm], lch5[maxm], rch5[maxm], par2[maxm], par3[maxm], par5[maxm];
int m2, m3, m5, s2, s3, s5, s35;
int mt(int *l, int *r, int *lch, int *rch, int *par, int m)
{
	int nw = m + 1, ll = m + 1;
	for (int i = 0; i <= m; i++)
		l[i] = r[i] = i;
	while (ll > 1)
	{
		int ls = nw - ll;
		for (int i = 0; i < ll; i += 2)
		{
			par[ls + i] = par[ls + i + 1] = nw;
			l[nw] = l[ls + i];
			if (i != ll - 1)
				r[nw] = r[ls + i + 1];
			else
				r[nw] = r[ls + i] + r[ls + i] - l[ls + i] + 1;
			lch[nw] = ls + i;
			if (i != ll - 1)
				rch[nw] = ls + i + 1;
			else
				rch[nw] = -1;
			nw++;
		}
		ll = nw - ls - ll;
	}
	return nw;
}
int calc(int a, int b, int c)
{
	return a * s35 + b * s5 + c;
}
int combine(long long a, long long b)
{
	return ((a * b) % p * q + a + b) % p;
}
void update()
{
	for (int i = 0; i < s2; i++)
	{
		int le2 = l2[i], ri2 = r2[i];
		for (int j = 0; j < s3; j++)
		{
			int le3 = l3[j], ri3 = r3[j];
			for (int k = 0; k < s5; k++)
			{
				int le5 = l5[k], ri5 = r5[k];
				if (par5[k] != -1)
					f[calc(i, j, par5[k])] = combine(f[calc(i, j, par5[k])], f[calc(i, j, k)]);
				if (le5 == ri5 && par3[j] != -1)
					f[calc(i, par3[j], k)] = combine(f[calc(i, par3[j], k)], f[calc(i, j, k)]);
				if (le5 == ri5 && le3 == ri3 && par2[i] != -1)
					f[calc(par2[i], j, k)] = combine(f[calc(par2[i], j, k)], f[calc(i, j, k)]);
			}
		}
	}
}

int a2, b2, a3, b3, a5, b5;
int q3(int nw2, int nw3, int nw5)
{
	if (a5 <= l5[nw5] && r5[nw5] <= b5)
		return f[calc(nw2, nw3, nw5)];
	int rt = 0;
	if (lch5[nw5] != -1 && a5 <= r5[lch5[nw5]])
		rt = q3(nw2, nw3, lch5[nw5]);
	if (rch5[nw5] != -1 && b5 >= l5[rch5[nw5]])
		rt = combine(rt, q3(nw2, nw3, rch5[nw5]));
	return rt;
}
int q2(int nw2, int nw3, int nw5)
{
	if (a3 <= l3[nw3] && r3[nw3] <= b3)
		return q3(nw2, nw3, nw5);
	int rt = 0;
	if (lch3[nw3] != -1 && a3 <= r3[lch3[nw3]])
		rt = q2(nw2, lch3[nw3], nw5);
	if (rch3[nw3] != -1 && b3 >= l3[rch3[nw3]])
		rt = combine(rt, q2(nw2, rch3[nw3], nw5));
	return rt;
}
int q1(int nw2, int nw3, int nw5)
{
	if (a2 <= l2[nw2] && r2[nw2] <= b2)
		return q2(nw2, nw3, nw5);
	int rt = 0;
	if (lch2[nw2] != -1 && a2 <= r2[lch2[nw2]])
		rt = q1(lch2[nw2], nw3, nw5);
	if (rch2[nw2] != -1 && b2 >= l2[rch2[nw2]])
		rt = combine(rt, q1(rch2[nw2], nw3, nw5));
	return rt;
}
int main()
{
	freopen("volunteer.in", "r", stdin);
	freopen("volunteer.out", "w", stdout);
	int t, u = 0;
	scanf("%d", &t);
	u = t;
	memset(lch2, -1, sizeof(lch2));
	memset(lch3, -1, sizeof(lch3));
	memset(lch5, -1, sizeof(lch5));
	memset(rch2, -1, sizeof(rch2));
	memset(rch3, -1, sizeof(rch3));
	memset(rch5, -1, sizeof(rch5));
	memset(par2, -1, sizeof(par2));
	memset(par3, -1, sizeof(par3));
	memset(par5, -1, sizeof(par5));
	lg2 = log(2), lg3 = log(3), lg5 = log(5);
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
	s2 = mt(l2, r2, lch2, rch2, par2, m2);
	s3 = mt(l3, r3, lch3, rch3, par3, m3 * t3);
	s5 = mt(l5, r5, lch5, rch5, par5, m5);
	s35 = s3 * s5;
	for (int i = 1; i < nl; i++)
		f[calc(lu[i].m2, lu[i].m3 * t3, lu[i].m5)] = lu[i].real;
	update();
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		a2 = lu[a].m2, a3 = lu[a].m3 * t3, a5 = lu[a].m5;
		b2 = lu[b].m2, b3 = lu[b].m3 * t3, b5 = lu[b].m5;
		printf("%d\n", q1(s2 - 1, s3 - 1, s5 - 1));
	}
	return 0;
}
