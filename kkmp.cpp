#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int pi[1010101];
char s[1010101], t[1010101];
int main()
{
	scanf("%s%s", t, s);
	int ls = strlen(s), lt = strlen(t);
	int nn = 0, ans = 0;
	for (int i = 1; i < lt; i++)
	{
		while (nn && t[nn] != t[i])
			nn = pi[nn - 1];
		if (t[nn] == t[i])
			pi[i] = ++nn;
	}
	nn = 0;
	for (int i = 0; i < ls; i++)
	{
		while (nn && t[nn] != s[i])
			nn = pi[nn - 1];
		if (t[nn] == s[i])
			nn++;
		if (nn == lt)
			printf("%d ", i - lt + 2);
	}
}
