#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		int m, n;
		scanf("%d%d", &n, &m);
		printf("%d\n", n);
		for (int j = 1; j <= n; j++)
		{
			int ch;
			if (2 * j - n - 1 < 0)
			{
				if (2 * (2 * j - n - 1) > -(n - 1))
					ch = 2;
				else
					ch = 1;
			}
			else if (2 * j - n - 1 == 0)
				ch = 2;
			else
			{
				int t = 2 * (n - 1) / (2 * j - n - 1);
				ch = max(2, min(m, t));
			}
			printf("%d %d 1\n", j, ch);
		}
	}
}
