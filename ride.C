/*
ID: jiangli16
LANG: C++
PROG: ride
*/
#include <cstdio>
#include <cstring>
char a[10];
char b[10];
int main()
{
	freopen("ride.in", "r", stdin);
	freopen("ride.out", "w", stdout);
	scanf("%s%s", a, b);
	int la = strlen(a);
	int lb = strlen(b);
	int s = 1, t = 1;
	for (int i = 0; i < la; i++)
		s *= a[i] - 'A' + 1;
	for (int i = 0; i < lb; i++)
		t *= b[i] - 'A' + 1;
	if (s % 47 == t %47)
		printf("GO\n");
	else
		printf("STAY\n");
	return 0;
}
