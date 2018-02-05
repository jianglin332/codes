#include <cstdio>
#include <cstdlib>
bool vd[10101][10101];
char ifl[55];
char cmd[111];
char dir[55] = "gsgl";
void gen(int a)
{
	sprintf(ifl, "%s/input%d.txt", dir, a);
	sprintf(cmd, "./express %s %s/output%d.txt", ifl, dir, a);
}
void gn(int n, int m, int nb)
{
	gen(nb);
	freopen(ifl, "w", stdout);
	printf("%d %d\n", n, m);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		while (vd[a = rand() % n + 1][b = rand() % n + 1] || a == b);
		vd[a][b] = 1;
		printf("%d %d\n", a, b);
	}
	fclose(stdout);
	system(cmd);
}
int main()
{
	srand(54188);
	gn(100, 100, 1);
	gn(100, 300, 2);
	gn(100, 1000, 3);
	gn(1000, 2000, 4);
	gn(1000, 5000, 5);
	gn(1000, 10000, 6);
	gn(10000, 10000, 7);
	gn(10000, 30000, 8);
	gn(10000, 60000, 9);
	gn(10000, 100000, 10);
}

