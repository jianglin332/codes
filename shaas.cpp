#include <stdio.h>
#include <algorithm>
using namespace std;
#include <stdlib.h>
int pd[101010][4];
char s[5];
int n, m, rem;
#define sgn(x) ((x) >> 31)
void paint(int x, int y, int tx, int ty)
{
	int f = sgn(tx) + 2 * sgn(ty);
	int t;
	int tt;
	if (x == 1)
		t = 0, tt = y;
	else if (x == n)
		t = 1, tt = y;
	else if (y == 1)
		t = 2, tt = x;
	else
		t = 3, tt = x;
	if (rem && ((pd[tt][t] >> f) & 1))
	{
		printf("-1");
		exit(0);
	}
	if (!pd[tt][t])
		rem--;
	pd[tt][t] |= 1 << f;
}
int main()
{
	int x, y;
	scanf("%d%d%d%d%s", &n, &m, &x, &y, s);
	int ty = (s[1] == 'R' ? 1 : -1), tx = (s[0] == 'D' ? 1 : -1);
	long long ans = 0;
	rem = m + n - 2;
	if ((x == 1 && tx == -1) || (x == n && tx == 1))
		tx *= -1;
	if ((y == 1 && ty == -1) || (y == m && ty == 1))
		ty *= -1;
	paint(x, y, tx, ty);
	while (rem)
	{
		int mxd = 101010;
		if (tx == 1)
			mxd = min(mxd, n - x);
		else
			mxd = min(mxd, x - 1);
		if (ty == 1)
			mxd = min(mxd, m - y);
		else
			mxd = min(mxd, y - 1);
		x += mxd * tx;
		y += mxd * ty;
		if ((x == 1 && tx == -1) || (x == n && tx == 1))
			tx *= -1;
		if ((y == 1 && ty == -1) || (y == m && ty == 1))
			ty *= -1;
		ans += mxd;
		paint(x, y, tx, ty);
	}
	printf("%I64d", ans + 1);
}
