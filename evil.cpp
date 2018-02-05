#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int x[101010], y[101010], cx[101010], cy[101010], s[2][2];
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d%d", x + i, y + i), cx[i] = x[i], cy[i] = y[i];
	sort(x, x + n);
	sort(y, y + n);
	int m = (n - 1) / 2;
	int mx = x[m], my = y[m];
	int d = min(x[m + 1] - x[m], y[m + 1] - y[m]);
	if (n & 1)
		d = min(d, min(x[m] - x[m - 1], y[m] - y[m - 1]));
	long long ans = 0;
	int md = 0;
	for (int i = 0; i < n; i++)
	{
		ans += abs(x[i] - x[m]) + abs(y[i] - y[m]);
		s[cx[i] <= mx][cy[i] <= my] = 1;
		md |= cx[i] == mx && cy[i] == my;
	}
	if ((n % 2 == 0 || md) && s[0][0] && s[0][1])
		ans -= d;
	printf("%lld", ans * 2);
}

