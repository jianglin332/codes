#include <cstdio>
#include <cstring>
int pi[1010101], f[1010101];
char a[1010101], b[1010101];
int main()
{
	scanf("%s%s", a, b);
	int la = strlen(a);
	int lb = strlen(b);
	int tmp = 0;
	for (int i = 1; i < la; i++)
	{
		while (tmp && a[i] != a[tmp])
			tmp = pi[tmp - 1];
		pi[i] = a[i] == a[tmp] ? ++tmp : 0;
	}
	f[0] = tmp = a[0] == b[0];
	for (int i = 1; i < lb; i++)
	{
		while (tmp && b[i] != a[tmp])
			tmp = pi[tmp - 1];
		f[i] = b[i] == a[tmp] ? ++tmp : 0;
	}
	for (int i = la - 1; i < lb; i++)
	{
		if (f[i] == la)
			printf("%d ", i - la + 2);
	}
}