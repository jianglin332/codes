#include <stdio.h>
#include <string.h>
char s[50505];
char nw[50505];
int main()
{
	scanf("%s", s);
	int l = strlen(s), m, n;
	for (int i = 1; i <= l / 2; i++)
	{
		n = m = 0;
		for (int j = i; j < l; j++)
		{
			if (s[j] == s[j - i])
				m++;
			else
				m = 0;
			nw[n++] = s[j];
			if (m == i)
				m = 0, n -= i;
		}
		for (int j = 0; j < n; j++)
			s[i + j] = nw[j];
		l = n + i;
	}
	s[l] = 0;
	printf("%s", s);
}
