#include <stdio.h>
#include <algorithm>
using namespace std;
int x[2020202], y[2020202];
int ux[202020], uy[202020];
typedef long long ll;
ll toleft(ll xa, ll xb, ll xc, ll ya, ll yb, ll yc)
{
	return xa * yb - xb * ya + xb * yc - xc * yb + xc * ya - xa * yc;
}
int main()
{
	int n;
	scanf("%d", &n);
	int mx = 0, my = 0;
	int mnx = 2020202, mny = 2020202, tl;
	for (int i = 0; i < n; i++)
	{
		int c, d;
		scanf("%d%d", &c, &d);
		ux[i] = c + 1010101, uy[i] = d + 1010101;
		if (ux[i] > ux[mx])
			mx = i;
		if (uy[i] > uy[my])
			my = i;
		if (ux[i] < mnx)
			mnx = ux[i];
		if (uy[i] < mny)
			mny = uy[i];
	}
	int t = 0;
	while (!toleft(ux[t], ux[(t + 1) % n], ux[(t + 2) % n], uy[t], uy[(t + 1) % n], uy[(t + 2)]))
		t = (t + 1) % n;
	tl = toleft(ux[0], ux[1], ux[2], uy[0], uy[1], uy[2]) > 0 ? 1 : -1;
	int l = mx, r = mx;
	long long tt = 0;
	for (int i = ux[mx]; i >= mnx; i--)
	{
		if (ux[(l + tl + n) % n] == i)
			l = (l + tl + n) % n;
		if (ux[(r - tl + n) % n] == i)
			r = (r + n - tl) % n;
		if (ux[l] == mnx)
		{
			y[i] = uy[l] - uy[r] + 1;
			tt += y[i];
			break;
		}
		while (ux[(l + tl + n) % n] == i)
			l = (l + tl + n) % n;
		while (ux[(r - tl + n) % n] == i)
			r = (r + n - tl) % n;
		long long x1l = ux[l], x2l = ux[(l + tl + n) % n];
		long long y1l = uy[l], y2l = uy[(l + tl + n) % n];
		long long x1r = ux[r], x2r = ux[(r - tl + n) % n];
		long long y1r = uy[r], y2r = uy[(r - tl + n) % n];
		y[i] = ((y1l * (x1l - x2l) + (x1l - i) * (y2l - y1l)) / (x1l - x2l)) - ((y1r * (x1r - x2r) + (x1r - i) * (y2r - y1r) + x1r - x2r - 1) / (x1r - x2r)) + 1;
		tt += y[i];
	}
	l = r = my;
	tl *= -1;
	int xx = 0;
	for (int i = uy[my]; i >= mny; i--)
	{
		if (uy[(l + tl + n) % n] == i)
			l = (l + tl + n) % n;
		if (uy[(r - tl + n) % n] == i)
			r = (r + n - tl) % n;
		if (uy[l] == mny)
		{
			x[i] = ux[l] - ux[r] + 1;
			xx += x[i];
			break;
		}
		while (uy[(l + tl + n) % n] == i)
			l = (l + tl + n) % n;
		while (uy[(r - tl + n) % n] == i)
			r = (r + n - tl) % n;
		long long x1l = ux[l], x2l = ux[(l + tl + n) % n];
		long long y1l = uy[l], y2l = uy[(l + tl + n) % n];
		long long x1r = ux[r], x2r = ux[(r - tl + n) % n];
		long long y1r = uy[r], y2r = uy[(r - tl + n) % n];
		x[i] = ((x1l * (y1l - y2l) + (y1l - i) * (x2l - x1l)) / (y1l - y2l)) - ((x1r * (y1r - y2r) + (y1r - i) * (x2r - x1r) + y1r - y2r - 1) / (y1r - y2r)) + 1;
		xx += x[i];
	}
	long double ans = 0;
	long double sx2 = 0, sx = 0, s1 = 0;
	long double sy2 = 0, sy = 0, s1y = 0;
	for (int i = 1; i < 2020200; i++)
	{
		sx2 = sx2 + 2 * sx + s1, sx = sx + s1;
		if (x[i])
			ans += sx2 * x[i], s1 += x[i];
		sy2 = sy2 + 2 * sy + s1y, sy = sy + s1y;
		if (y[i])
			ans += sy2 * y[i], s1y += y[i];
	}
	printf("%.8lf", double(ans / tt / (tt - 1)));
}
