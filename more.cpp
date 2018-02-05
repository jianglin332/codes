#include <stdio.h>
int d[55][55];
int np[55];
int m[55];
int nw[55];
int t;
long long n;
long long gcd(long long a, long long b)
{
	if (!b)
		return a;
	return gcd(b, a % b);
}
struct num
{
	long long a, b, c;
	num(long long t)
	{
		c = t;
		b = c / n;
		c %= n;
		a = b / n;
		b %= n;
	}
	num operator+(const num &k) const
	{
		num t = k;
		t.a += a;
		t.b += b;
		t.c += c;
		if (t.c >= n)
			t.c -= n, t.b++;
		while (t.b >= n)
			t.b -= n, t.a++;
		return t;
	}
	num operator*(const long long k)
	{
		num t = *this;
		t.a *= k;
		t.b *= k;
		t.c *= k;
		t.b += t.c / n;
		t.c %= n;
		t.a += t.b / n;
		t.b %= n;
		return t;
	}
	void disp()
	{
		printf("%lld+", a);
		c += b * n;
		if (c == 0)
			printf("0/1");
		else
		{
			long long t = gcd(c, n * n);
			printf("%lld/%lld", c / t, n * n / t);
		}
	}
};
int main()
{
	scanf("%lld%d", &n, &t);
	int mx = 0;
	for (int i = 0; i < t; i++)
	{
		scanf("%d", m + i);
		d[i][0] = 1;
		for (int j = 1; j < m[i]; j++)
			scanf("%d", d[i] + j);
		if (mx < d[i][m[i] - 1])
			mx = d[i][m[i] - 1];
	}
	num ans = 0, now = 0;
	long long all = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < t; j++)
			if (nw[j] < m[j] && i == d[j][nw[j]])
			{
				now = now + (n + (all - np[j]) * 2);
				np[j]++, nw[j]++, all++;
			}
		if (i == mx)
		{
			now = now * (n - mx + 1);
			ans = ans + now;
			break;
		}
		ans = ans + now;
	}
	ans.disp();
}
