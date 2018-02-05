#include <cstdio>
#include <cmath>
#include <cstring>
typedef long long ll;
int maxn = 1e7;
class vint
{
	ll num[160];
public:
	vint()
	{
		memset(num, 0, sizeof(num));
	}
	vint(int a)
	{
		memset(num, 0, sizeof(num));
		num[0] = a;
	}
	vint operator*(vint &a)
	{
		vint ans;
		for (int i = 0; i < 72; i++)
			for (int j = 0; j < 72; j++)
				ans.num[i + j] += num[i] * a.num[j];
		for (int i = 0; i < 72; i++)
		{
			ans.num[i + 1] += ans.num[i] / maxn;
			ans.num[i] %= maxn;
		}
		return ans;
	}
	vint &m1()
	{
		num[0]--;
		return (*this);
	}
	void disp(char *a)
	{
		a += sprintf(a, "%03d", num[71]);
		for (int i = 70; i >= 0; i--)
			a += sprintf(a, "%07d", num[i]);
	}
}ms[22], f;
char _c[500];
char *c = _c;
int main()
{
	f = 1;
	ms[0] = 2;
	for (int i = 1; i < 22; i++)
		ms[i] = ms[i - 1] * ms[i - 1];
	int n;
	scanf("%d", &n);
	for (int i = 0; i < 22; i++)
		if (n & (1 << i))
			f = f * ms[i];
	f.m1();
	f.disp(c);
	printf("%d\n", int(log(2) / log(10) * n));
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 50; j++)
			c += printf("%c", *c);
		printf("\n");
	}
}
