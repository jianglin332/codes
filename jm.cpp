#include <stdio.h>
int n, x, t, a;
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x);
		if (t > x)
			a += t - x;
		t = x;
	}
	a += t;
	printf("%d", a);
}
