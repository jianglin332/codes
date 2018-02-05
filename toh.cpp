#include <stdio.h>
int w[101010];
int s[101010];
int q[101010], st = 0, ed = 0;
int f[101010];
int h[101010];
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", w + i);
	for (int i = 1; i <= n; i++)
		s[i] = s[i  - 1] + w[i];
	f[n + 1] = 0;
	q[ed] = n + 1; 
	for (int i = n; i; i--)
	{
		while (st <= ed && f[q[st]] <= s[q[st] - 1] - s[i - 1])
			st++;
		f[i] = s[q[st - 1] - 1] - s[i - 1];
		h[i] = h[q[st - 1]] + 1;
		while (st <= ed && f[i] + s[q[ed] - 1] < f[q[ed]] + s[i - 1])
			ed--;
		q[++ed] = i;
	}
	printf("%d", h[1]);
}
