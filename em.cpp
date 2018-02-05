#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const long long mod = 1e8;
struct vint
{
	long long t[10];
	int l;
	vint(long long b)
	{
		memset(t, 0, sizeof(t));
		l = 0;
		while (b)
			t[l++] = b % mod, b /= mod;
		if (!l)
			l++;
	}
	vint()
	{
		memset(t, 0, sizeof(t));
		l = 1;
	}
	vint operator+(const vint &b) const
	{
		vint nw;
		nw.l = max(l, b.l);
		for (int i = 0; i < nw.l; i++)
		{
			nw.t[i] += t[i] + b.t[i];
			if (nw.t[i] >= mod)
				nw.t[i] -= mod, nw.t[i + 1]++;
		}
		if (nw.t[nw.l])
			nw.l++;
		return nw;
	}
	vint operator-(const vint &b) const
	{
		vint nw;
		nw.l = max(l, b.l);
		for (int i = 0; i < nw.l; i++)
		{
			nw.t[i] += t[i] - b.t[i];
			if (nw.t[i] < 0)
				nw.t[i] += mod, nw.t[i + 1]--;
		}
		while (nw.l > 1 && !nw.t[nw.l - 1])
			nw.l--;
		return nw;
	}
	vint operator*(const vint &b) const
	{
		vint nw;
		nw.l = l + b.l;
		for (int i = 0; i < l; i++)
			for (int j = 0; j < b.l; j++)
				nw.t[i + j] += t[i] * b.t[j];
		for (int i = 0; i < nw.l; i++)
			nw.t[i + 1] += nw.t[i] / mod, nw.t[i] %= mod;
		while (nw.l > 1 && !nw.t[nw.l - 1])
			nw.l--;
		return nw;
	}
	vint operator/(const long long b) const
	{
		vint nw = *this;
		for (int i = nw.l - 1; i; i--)
			nw.t[i - 1] += mod * (nw.t[i] % b), nw.t[i] /= b;
		nw.t[0] /= b;
		return nw;
	}
	void disp() const
	{
		if (l >= 2)
		{
			if (l > 2 || t[1] >= 100)
				printf("...%02d", t[1] % 100);
			else
				printf("%d", t[1]);
			printf("%08d", (int)t[0]);
		}
		else
			printf("%d", (int)t[0]);
		printf("\n");
	}
};
inline vint a(long long b)
{
	if (b <= 0)
		return 0;
	return vint(b) * (b + 1) * (2 * b + 1) / 6;
}
inline vint b(long long t)
{
	if (t <= 0)
		return 0;
	return a(t - 1) + t;
}
vint up(long long x1, long long y1, long long x2, long long y2)
{
	if (x2 < x1 || y2 < y1)
		return 0;
	return (b(x2) - b(x1 - 1) + (y1 - 1) * (x2 - x1 + 1)) * (y2 - y1 + 1) + vint(y2 - y1) * (y2 - y1 + 1) / 2 * (x2 - x1 + 1);
}
vint down(long long x1, long long y1, long long x2, long long y2)
{
	if (x2 < x1 || y2 < y1)
		return 0;
	return (a(y2) - a(y1 - 1) - (x1 - 1) * (y2 - y1 + 1)) * (x2 - x1 + 1) - vint(x2 - x1) * (x2 - x1 + 1) / 2 * (y2 - y1 + 1);
}
vint mid(long long fr, long long to)
{
	return vint(to * to) * (to * to + 1) / 2 - vint((fr - 1) * (fr - 1)) * ((fr - 1) * (fr - 1) + 1) / 2 - up(fr, 1, to, fr - 1) - down(1, fr, fr - 1, to);
}
int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &y1, &x1, &y2, &x2);
		vint ans;
		if (x1 > y2)
			ans = up(x1, y1, x2, y2);
		else if (x2 < y1)
			ans = down(x1, y1, x2, y2);
		else
		{
			ans = mid(max(x1, y1), min(x2, y2));
			if (x1 > y1)
				ans = ans + up(x1, y1, x2, x1 - 1);
			if (x1 < y1)
				ans = ans + down(x1, y1, y1 - 1, y2);
			if (x2 > y2)
				ans = ans + up(min(x2, y2) + 1, max(x1, y1), x2, y2);
			if (x2 < y2)
				ans = ans + down(max(x1, y1), min(x2, y2) + 1, x2, y2);
		}
		ans.disp();
	}
}
