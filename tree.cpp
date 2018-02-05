#include <cstdio>
int min;
void dfs(int l, int r)
{
	if (r >= min || l < 0)
		return;
	if (l == 0)
		min = r;
	dfs(2 * l - r - 2, r);
	dfs(2 * l - r - 1, r);
	dfs(l, 2 * r - l);
	dfs(l, 2 * r - l + 1);
}
int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		int l, r, lim;
		scanf("%d%d%d", &l, &r, &lim);
		min = lim + 1;
		dfs(l, r);
		if (min > lim)
			printf("-1\n");
		else
			printf("%d\n", min);
	}
}
