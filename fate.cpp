#include <stdio.h>
#include <string.h>
#include <ctype.h>
char buf[1 << 16];
char gc()
{
	static char *s = buf, *t = buf;
	if (s == t)
		t = (s = buf) + fread(buf, 1, 1 << 16, stdin);
	return *(s++);
}
int g()
{
	char c;
	while (!isdigit(c = gc()));
	int r = c - '0';
	while (isdigit(c = gc()))
		r = r * 10 + c - '0';
	return r;
}
int h[1010101], l[1010101], r[1010101];
long long f[1010101];
const int mod = 998244353;
int main()
{
	int n = g();
	for (int i = 1; i <= n; i++)
		h[i] = g();
	h[0] = h[n + 1] = 1e9 + 7;
	for (int i = 1; i <= n; i++)
		for (l[i] = i - 1; h[i] >= h[l[i]]; l[i] = l[l[i]]);
	for (int i = n; i; i--)
		for (r[i] = i + 1; h[i] > h[r[i]]; r[i] = r[r[i]]);
	for (int i = 1; i <= n; i++)
	{
		f[1] += h[i];
		f[i - l[i] + 1] += mod + mod - h[i];
		f[r[i] - i + 1] += mod + mod - h[i];
		f[r[i] - l[i] + 1] += h[i];
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		f[i] += f[i - 1];
	for (int i = 1; i <= n; i++)
		ans ^= f[i] = (f[i] + f[i - 1]) % mod;
	printf("%d", ans);
	return 0;
}
