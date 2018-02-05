#include <cstdio>
int m[1001], p, a, b, t, c;
bool n[1002];
int main()
{
	scanf("%d%d", &b, &a);
	for (int i = 0; i < b; i++)
		m[i] = 1001;
	for (int i = 0; i < a; i++)
	{
		scanf("%d", &t);
		if (!n[t])
		{
			n[m[p]] = 0;
			n[t] = 1;
			m[p] = t;
			p++;
			if (p == b)
				p = 0;
			c++;
		}
	}
	printf("%d", c);
}
