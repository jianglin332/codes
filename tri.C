#include <cstdio>
#include <cstdlib>
char f[1010][1010];
char an[1010][1010];
int n, m;
void init()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			an[i][j] = '.';
			char ch = getchar();
			while (ch != '.' && ch != 'b' && ch != 'w')
				ch = getchar();
			f[i][j] = ch;
		}
}
void ex()
{
	printf("NO");
	exit(0);
}
void paintf(int a, int b)
{
	for (char i = 'a'; i < 'e'; i++)
	{
		bool flg = 1;
		for (int j = -1; j < 2; j++)
		{
			if (an[a + j][b - 1] == i || an[a + j][b + 1] == i)
				flg = 0;
		}
		if (an[a - 2][b] == i || an[a + 2][b] == i)
			flg = 0;
		if (!flg)
			continue;
		an[a - 1][b] = an[a][b] = an[a + 1][b] = i;
		f[a - 1][b] = f[a][b] = f[a + 1][b] = '.';
		break;
	}
}
void paintb(int a, int b)
{
	for (char i = 'a'; i < 'z'; i++)
	{
		bool flg = 1;
		for (int j = -1; j < 2; j++)
		{
			if (an[a - 1][b + j] == i || an[a + 1][b + j] == i)
				flg = 0;
		}
		if (an[a][b - 2] == i || an[a][b + 2] == i)
			flg = 0;
		if (!flg)
			continue;
		an[a][b - 1] = an[a][b] = an[a][b + 1] = i;
		f[a][b - 1] = f[a][b] = f[a][b + 1] = '.';
		break;
	}
}
void disp()
{
	puts("YES");
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			putchar(an[i][j]);
		putchar('\n');
	}
}
void work()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			if (f[i][j] == 'b')
			{
				if (f[i][j - 1] == 'w' && f[i][j + 1] == 'w')
					paintb(i, j);
				else
					ex();
			}
		for (int j = 1; j <= m; j++)
			if (f[i][j] == 'w')
			{
				if (f[i + 1][j] == 'b' && f[i + 2][j] == 'w')
					paintf(i + 1, j);
				else
					ex();
			}
	}
}
int main()
{
	init();
	work();
	disp();
}
