#include <cstdio>
int f[11];
int main()
{
	f[0] = f[1] = 1;
	for (int i = 2; i <= 8; i++)
		f[i] = f[i - 2] * 2 + f[i - 1];
	printf("%d", f[8]);
}
