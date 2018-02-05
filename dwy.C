#include <cstdio>
#include <cstring>
#define ms(x) memset(x, 0, sizeof(x))
int next[1010101], num[1010101], ans[1010101];
char str[1010101];
void work()
{
	ms(next), ms(num), ms(str), ms(ans);
	scanf("%s", str);
	int l = strlen(str), now = 0;
	for (int i = 1; i < l; i++)
	{
		while (now && str[now] != str[i])
			now = next[now - 1];
		if (str[now] == str[i])
		{
			num[i] = num[now] + 1;
			now++;
		}
		next[i] = now;
	}
	now = 0;
	for (int i = 1; i < l; i++)
	{
		while (now && (str[now] != str[i] || now + 1 > ((i + 1) >> 1)))
			now = next[now - 1];
		if (str[now] == str[i])
		{
			ans[i] = num[now] + 1;
			now++;
		}
	}
	long long an = 1;
	for (int i = 0; i < l; i++)
	{
		an *= ans[i] + 1;
		an %= 1000000007;
	}
	printf("%lld\n", an);
}
int main()
{
	int q;
	for (scanf("%d", &q); q; q--)
		work();
}
