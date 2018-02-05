#include <cstdio>
#include <cctype>
#include <cstring>
#include <cmath>
bool can[10];
bool chk(int a)
{
	if (!a)
		return can[0];
	while (a)
	{
		if (!can[a % 10])
			return 0;
		a /= 10;
	}
	return 1;
}
int tms;
void output(int a, int b, int c)
{
	printf("<%d>\n", ++tms);
	char o[8][8] = {0};
	int len = log10(c) + 1;
	for (int i = 0; i < len; i++)
		for (int j = 0; j < 7; j++)
			o[j][i] = ' ';
	sprintf(o[0] + len - 3, "%d", a);
	o[1][0] = 'X';
	sprintf(o[1] + len - 2, "%d", b);
	for (int i = 0; i < len; i++)
		o[2][i] = o[5][i] = '-';
	sprintf(o[3] + len - int(log10(a * (b % 10))) - 1, "%d", a * (b % 10));
	sprintf(o[4] + len - int(log10(a * (b / 10))) - 2, "%d", a * (b / 10));
	sprintf(o[6], "%d", c);
	for (int i = 0; i < 7; i++)
		printf("%s\n", o[i]);
	printf("\n");
}
int main()
{
	char c;
	while (isdigit(c = getchar()))
		can[c - '0'] = 1;
	for (int i = 100; i < 1000; i++)
		if (chk(i))
			for (int j = 10; j < 100; j++)
				if (chk(j))
					if (chk(i * j) && chk(i * (j % 10)) && chk(i * (j / 10)))
						output(i, j, i * j);
	printf("The number of solutions = %d\n", tms);
	return 0;
}
