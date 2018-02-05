#include <cstdio>
#include <cstring>
const long long maxn = 1e8;
inline int max(int a, int b)
{
	return a > b ? a : b;
}
inline int min(int a, int b)
{
	return a < b ? a : b;
}
class vint
{
	long long num[130];
	int len;
public:
	vint()
	{
		memset(num, 0, sizeof(num));
		len = 1;
	}
	vint(const char *str)
	{
		memset(num, 0, sizeof(num));
		int slen = strlen(str);
		len = (slen + 7) / 8;
		for (int i = 0; i < len; i++)
		{
			long long d = 1;
			for (int j = 0; j < 8; j++)
			{
				if (slen - 1 - i * 8 - j < 0)
					break;
				num[i] += d * (str[slen - 1 - i * 8 - j] - '0');
				d *= 10;
			}
		}
	}
	vint(const int _a)
	{
		len = 1;
		num[0] = _a % maxn;
		int a = _a;
		a /= maxn;
		while(a)
		{
			num[len++] = a % maxn;
			a /= maxn;
		}
	}
	void disp()
	{
		printf("%d", num[len - 1]);
		for (int i = len - 2; i >= 0; i--)
		{
			printf("%08d", num[i]);
		}
		printf("\n");
	}
	vint operator+(const vint &a) const
	{
		vint ans;
		ans.len = max(a.len, len);
		for (int i = 0; i < ans.len; i++)
		{
			ans.num[i] = a.num[i] + num[i];
		}
		for (int i = 0; i < ans.len; i++)
		{
			if (ans.num[i] >= maxn)
			{
				ans.num[i] -= maxn;
				ans.num[i + 1] += 1;
			}
		}
		if (ans.num[ans.len])
			ans.len++;
		return ans;
	}
	vint operator*(const vint &a) const
	{
		vint ans;
		ans.len = len + a.len;
		for (int i = 0; i < len; i++)
			for (int j = 0; j < a.len; j++)
			{
				ans.num[i + j] += num [i] * a.num[j];
			}
		for (int i = 0; i < ans.len; i++)
			if (ans.num[i] >= maxn)
			{
				ans.num[i + 1] += ans.num[i] / maxn;
				ans.num[i] %= maxn;
			}
		while ((!ans.num[ans.len-1]) && ans.len >= 2)
			ans.len--;
		return ans;
	}
	vint div2() const
	{
		vint ans = (*this);
		for (int i = len - 1; i > 0; i--)
		{
			ans.num[i - 1] += (ans.num[i] & 1) * maxn;
			ans.num[i] >>= 1;
		}
		ans.num[0] >>= 1;
		if (!ans.num[len - 1])ans.len--;
		return ans;
	}
	bool operator<(const vint &a) const
	{
		if (len < a.len)
			return true;
		if (len > a.len)
			return false;
		for (int i = len - 1; i >= 0; i--)
		{
			if (num[i] < a.num[i])
				return true;
			if (num[i] > a.num[i])
				return false;
		}
		return false;
	}
	vint operator/(const vint &a) const
	{
		if ((*this) < a)
			return 0;
		vint st = 0, ed = (*this);
		while ((st + 1) < ed)
		{
			vint mid = (st + ed + 1).div2();
			if ((*this) < mid * a)
				ed = mid;
			else
				st = mid;
		}
		return st;
	}
};
vint f[5566][5566];
int main()
{
	f[0][0] = 1;
	for (int i = 1; i < 5556; i++)
	{
		for (int j = 0; j <= i; j++)
			f[i][j] = f[i][j] + f[i - j][min(j, i - j)];
		for (int j = 1; j <= i; j++)
			f[i][j] = f[i][j] + f[i][j - 1];
	}
	f[5555][5555].disp();
}
