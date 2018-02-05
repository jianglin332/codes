#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char a[2020], b[2020];
int f[2][2020];
int main()
{
	scanf("%s%s", a + 1, b + 1);
	int la = strlen(a + 1);
	int lb = strlen(b + 1);
	int ml = max(la, lb);
	for (int i = 0; i <= ml; i++)
		f[0][i] = i;
	bool r = 1;
	f[1][0] = 1;
	for (int i = 1; i <= la; i++, r ^= 1, f[r][0] = i)
		for (int j = 1; j <= lb; j++)
			if (a[i] == b[j])
				f[r][j] = f[!r][j - 1];
			else
				f[r][j] = min(min(f[!r][j - 1], f[!r][j]), f[!r][j - 1]) + 1;
	printf("%d", f[!r][lb]);
	return 0;
}
