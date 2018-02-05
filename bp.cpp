#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
char s[202020];
int ml[202020];
char bf[101010];
int lt[202020], rt[202020];
int lr[202020], rr[202020], nr;
bool cl(int a, int b)
{
	return lt[a] < lt[b];
}
bool cr(int a, int b)
{
	return rt[a] < rt[b];
}
int main()
{
	scanf("%s", bf);
	int le = strlen(bf);
	int l = 0;
	s[l++] = '@';
	s[l++] = '#';
	for (int i = 0; i < le; i++)
		s[l++] = bf[i], s[l++] = '#';
	s[l] = '!';
	int mx = 1, tg = 1;
	for (int i = 2; i < l; i++)
	{
		if (i > mx)
		{
			mx = tg = i;
			int t = i;
			while (s[t - 1] == s[mx + 1])
				t--, mx++;
			ml[i] = mx - i;
		}
		else
		{
			int u = tg - (i - tg);
			ml[i] = min(ml[u], mx - i);
			if (ml[i] == mx - i)
			{
				tg = i;
				int t = i - ml[i];
				while (s[t - 1] == s[mx + 1])
					t--, mx++;
				ml[i] = mx - i;
			}
		}
	}
	for (int i = 2; i < l; i++)
		if (ml[i])
			lr[nr] = rr[nr] = i, nr++, lt[i] = i - ml[i], rt[i] = i + ml[i];
	sort(lr, lr + nr, cl), sort(rr, rr + nr, cr);
	int rm = 0, nw = 0;
	mx = 0;
	for (int i = 0; i < nr; i++)
	{
		int lm = rt[rr[i]];
		while (nw < nr && lt[lr[nw]] <= lm)
			rm = max(rm, lr[nw++]);
		mx = max(mx, rm - rr[i]);
	}
	printf("%d", mx);
	return 0;
}
