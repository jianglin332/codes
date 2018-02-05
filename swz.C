#include <cstdio>
int main()
{
	int m, s, _t;
	scanf("%d%d%d", &m, &s, &_t);
	int t = _t;
	int n = s;
	while (t)
	{
		if (m >= 10)
		{
			t -= 1;
			m -= 10;
			n -= 60;
		}
		else if (m >= 6 && t >= 2 && n > 17)
		{
			t -= 2;
			m -= 6;
			n -= 60;
		}
		else if (m >= 2 && t >= 3 && n > 34)
		{
			t -= 3;
			m -= 2;
			n -= 60;
		}
		else if (t >= 7 && n > 102)
		{
			t -= 7;
			n -= 120;
		}
		else
		{
			t -= 1;
			n -= 17;
		}
		if (n <= 0)
		{
			printf("Yes\n%d", _t - t);
			return 0;
		}
	}
	printf("No\n%d", s - n);
}
