#include <cstdio>
#include <algorithm>
using namespace std;
int p[1010101];
int main()
{
	int n, k;
	scanf("%d%d", &n, &k);
	int t = 2 * n * k;
	for (int i = 0; i < t; i++)
		scanf("%d", p + i);
	sort(p, p + t);
	int st = 0, ed = p[t - 1] - p[0];
	while (st < ed)
	{
		int m = (st + ed) / 2;
		int o = 0;
		for (int i = 0; i < t; i++)
		{
			if (o >= n || i > o * k * 2)
				break;
			if (p[i + 1] - p[i] <= m)
				o++, i++;
		}
		if (o == n)
			ed = m;
		else
			st = m + 1;
	}
	printf("%d", ed);
}
