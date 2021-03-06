#include <stdio.h>
int pow(int a, int b, int p)
{
	if (!b)
		return 1;
	int t = pow(a, b / 2, p);
	if (b & 1)
		return 1ll * t * t % p * a % p;
	return 1ll * t * t % p;
}
int main()
{
	int n, x;
	scanf("%d%d", &n, &x);
	if (n == 1)
		return printf("%d", x > 2 ? x - 1 : -1), 0;
	for (int i = 2; i * i <= n + 1; i++)
		if ((n + 1) % i == 0)
			return puts("-1"), 0;
	for (int i = x - 1; i > 1; i--)
		if (i % (n + 1))
		{
			int flg = 1;
			for (int j = 2; j * j <= n; j++)
				if (n % j == 0 && pow(i, n / j, n + 1) == 1)
				{
					flg = 0;
					break;
				}
			if (flg)
				return printf("%d", i), 0;
		}
	puts("-1");
}
