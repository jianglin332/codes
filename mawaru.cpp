#include <stdio.h>
int n, m, k, x;
long long pow(long long a, int t)
{
	if (!t)
		return 1;
	long long b = pow(a, t / 2);
	if (t & 1)
		return b * b % n * a % n;
	return b * b % n;
}
int main()
{
	scanf("%d%d%d%d", &n, &m, &k, &x);
	printf("%d", (m * pow(10, k) % n + x) % n);
	return 0;
}
