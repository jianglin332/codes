#include <cstdio>
#include <algorithm>
using namespace std;
typedef unsigned long long vint;
vint f[10000][10000];
int main()
{
	f[0][0] = 1;
	for (int i = 1; i < 10000; i++)
	{
		for (int j = 0; j <= i; j++)
			f[i][j] += f[i - j][min(j, i - j)];
		for (int j = 1; j <= i; j++)
			f[i][j] += f[i][j - 1];
	}
	printf("%llu", f[416][416]);
}
