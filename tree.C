#include <cstdio>
#include <cstring>
#define ms(x, y) memset(x, y, sizeof(x))
const int md = 1e8;
struct vint
{
	int l;
	long long num[20];
	vint()
	{
		l = 1;
		ms(num, 0);
		num[0] = 1;
	}
	vint(int a)
	{
		l = 1;
		ms(num, 0);
		num[0] = a;
	}
	vint operator * (const vint &a)
	{
		vint ans = 0;
		ans.l = l + a.l;
		for (int i = 0; i < l; i++)
			for (int j = 0; j < a.l; j++)
			{
				ans.num[i + j] += num[i] * a.num[j];
				ans.num[i + j + 1] += ans.num[i + j] / md;
				ans.num[i + j] %= md;
			}
		while (!ans.num[ans.l - 1])
			ans.l--;
		return ans;
	}
	void disp()
	{
		printf("%d", num[l - 1]);
		for (int i = l - 2; i >= 0; i--)
			printf("%08d", num[i]);
	}
	const vint &max(const vint &a) const
	{
		if (l > a.l)
			return *this;
		if (l < a.l)
			return a;
		for (int i = l - 1; i >= 0; i--)
		{
			if (num[i] > a.num[i])
				return *this;
			if (num[i] < a.num[i])
				return a;
		}
		return a;
	}
};
struct ed
{
	int to;
	ed *nx;
	ed(){}
	ed(int t, ed *n):to(t), nx(n){}
} *hd[707];
int n;
vint f[707][707];
int size[707];
int fnd(int nd, int pr)
{
	size[nd] = 1;
	for (ed *i = hd[nd]; i; i = i->nx)
		if (i->to != pr)
		{
			int sz = fnd(i->to, nd);
			for (int j = size[nd]; j; j--)
				for (int k = sz; k >= 0; k--)
					f[nd][j + k] = f[nd][j + k].max(f[nd][j] * f[i->to][k]);
			size[nd] += sz;
		}
	for (int i = 1; i <= size[nd]; i++)
		f[nd][0] = f[nd][0].max(f[nd][i] * i);
	return size[nd];
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		hd[a] = new ed(b, hd[a]);
		hd[b] = new ed(a, hd[b]);
	}
	fnd(1, 0);
	f[1][0].disp();
}
