#include <cstdio>
#include <cstdlib>
const int lk[10][10] =
{
	{6, 2, 4, 4, 3, 4, 5, 3, 6, 5},
	{2, 2, 1, 2, 2, 1, 1, 2, 2, 2},
	{4, 1, 5, 4, 2, 3, 4, 2, 5, 4},
	{4, 2, 4, 5, 3, 4, 4, 3, 5, 5},
	{3, 2, 2, 3, 4, 3, 3, 2, 4, 4},
	{4, 1, 3, 4, 3, 5, 5, 2, 5, 5},
	{5, 1, 4, 4, 3, 5, 6, 2, 6, 5},
	{3, 2, 2, 3, 2, 2, 2, 3, 3, 3},
	{6, 2, 5, 5, 4, 5, 6, 3, 7, 6},
	{5, 2, 4, 5, 4, 5, 5, 3, 6, 6}
};
int str[201010], l, old, nw;
inline int gt(int a)
{
	return a >= (l >> 1) ? a - (l >> 1) : a + (l >> 1);
}
void init()
{
	char c;
	while ((c = getchar()) <= '9' && c >= '0')
		str[l++] = c - '0';
	for (int i = 0; i < (l >> 1); i++)
		old += lk[str[i]][str[i + (l >> 1)]];
}
void work()
{
	int lb = -1, os;
	bool flg = 0;
	nw = old;
	for (int i = l - 1; i >= 0; i--)
	{
		if (nw - lk[str[gt(i)]][str[i]] + lk[str[gt(i)]][8] > old && str[i] < 8)
		{
			lb = i;
			os = str[i];
			nw -= lk[str[gt(i)]][str[i]] - lk[str[gt(i)]][8];
			str[i] = 8;
			break;
		}
		else if (nw - lk[str[gt(i)]][str[i]] + lk[str[gt(i)]][9] > old && str[i] == 8)
		{
			lb = i;
			os = str[i];
			nw -= lk[str[gt(i)]][str[i]] - lk[str[gt(i)]][9];
			str[i] = 9;
			break;
		}
		else
		{
			nw -= lk[str[gt(i)]][str[i]] - lk[str[gt(i)]][8];
			str[i] = 8;
		}
	}
	if (lb == -1)
	{
		printf("-1");
		exit(0);
	}
	for (int i = 8; i > os; i--)
		if (nw + lk[str[gt(lb)]][i] - lk[str[gt(lb)]][str[lb]] > old)
		{
			nw += lk[str[gt(lb)]][i] - lk[str[gt(lb)]][str[lb]];
			str[lb] = i;
		}
	for (int i = lb + 1; i < l; i++)
	{
		for (int j = 8; j >= 0; j--)
			if (nw + lk[str[gt(i)]][j] - lk[str[gt(i)]][str[i]] > old)
			{
				nw += lk[str[gt(i)]][j] - lk[str[gt(i)]][str[i]];
				str[i] = j;
			}
	}
	for (int i = 0; i < l; i++)
		printf("%01d", str[i]);
}
int main()
{
	init();
	work();
	return 0;
}
