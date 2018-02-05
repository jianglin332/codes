#include <cstdio>
#include <cstring>
char f[31700][32];
int n;
char dp(int a, int b)
{
	if (f[a][b] != -1)
		return f[a][b];
	long long tmp = 1;
	for (int i = 0; i < b; i++)
		tmp *= a;
	if (b == 1 && a * a >= n)
	{
		f[a][b] = ((n - a) & 1);
		return f[a][b];
	}
	if (tmp >= n)
	{
		f[a][b] = 0;
		return 0;
	}
	f[a][b] = !(dp(a + 1, b) | dp(a, b + 1));
	return f[a][b];
}
int main()
{
	memset(f, -1, sizeof(f));
	int a, b;
	scanf("%d%d%d", &a, &b, &n);
	long long tmp = 1;
	for (int i = 0; i < b; i++)
		tmp *= 2;
	if (a == 1 && tmp >= n)
		printf("Missing");
	else if (a == 1)
	{
		if (dp(a + 1, b))
	}
	else if (b == 1 && a * a >= n)
	{
		if ((n - a) & 1)
			printf("Stas");
		else
			printf("Masha");
	}
	else if (dp(a, b))
		printf("Stas");
	else
		printf("Masha");
}
