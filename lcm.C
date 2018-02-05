#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
#include <openssl/bn.h>
const int ET=10000;
int nl;
inline int max(int a, int b)
{
	return (a > b) ? a : b;
}
class vint
{
	long long number[4000];
	int length;
public:
	vint();
	vint(const char*);
	vint(long long);
	vint& operator*=(const vint&);
	vint& operator+=(const vint&);
	vint& operator-=(const vint&);
	vint operator+(const vint&);
	vint operator*(const vint&);
	long long operator%=(const long long);
	void disp();
};
long long vint::operator%=(const long long a)
{
	for (int i = length - 1; i; i--)
	{
		number[i] %= a;
		number[i - 1] += number[i] * ET;
	}
	number[0] %= a;
	return number[0];
}
vint::vint()
{
	memset(number,0,sizeof(number));
	length = 1;
}
vint::vint(const char* str)
{
	memset(number, 0, sizeof(number));
	length = (strlen(str)+3)/4;
	int slen = strlen(str);
	for (int i = 0; i < length; i++)
	{
		int ans=0;
		int d = 1;
		for (int j = 0; j <= 3; j++)
		{
			if (slen - 1 - i * 4 - j >= 0)
			{
				ans += (str[slen - 1 - i * 4 - j]-'0') * d;
			}
			d *= 10;
		}
		number[i] = ans;
	}
}
vint::vint(long long a)
{
	number[0] = a % ET;
	a /= ET;
	length = 1;
	int i = 1;
	while (a)
	{
		number[i++] = a % ET;
		a /= ET;
		length++;
	}
}
vint vint::operator+(const vint& a)
{
	vint ans;
	ans.length = max(length, a.length);
	for (int i = 0; i < ans.length; i++)
	{
		ans.number[i] += a.number[i] + number[i];
	}
	for (int i = 0; i < ans.length;i++)
	if (ans.number[i] >= ET)
	{
		ans.number[i + 1]++;
		ans.number[i] -= ET;
	}
	if (ans.number[ans.length])ans.length++;
	return ans;
}
vint& vint::operator+=(const vint& a)
{
	length = max(length, a.length);
	for (int i = 0; i < length; i++)
	{
		number[i] += a.number[i];
	}
	for (int i = 0; i < length; i++)
	if (number[i] >= ET)
	{
		number[i + 1]++;
		number[i] -= ET;
	}
	if (number[length])length++;
	return (*this);
}
vint vint::operator*(const vint& a)
{
	vint ans;
	ans.length = a.length + length;
	for (int i = 0; i < a.length; i++)
	for (int j = 0; j < length; j++)
		ans.number[i + j] += number[j] * a.number[i];
	for (int i = 0; i < ans.length; i++)
	if (ans.number[i] >= ET)
	{
		ans.number[i + 1] += ans.number[i] / ET;
		ans.number[i] %= ET;
	}
	while ((!ans.number[ans.length - 1])&&ans.length>=2)ans.length--;
	return ans;
}
void vint::disp()
{
	printf("%d", number[length - 1]);
	for (int i = length - 2; i >= 0; i--)
	{
		printf("%04d", number[i]);
	}
}
long long gcd(vint a, long long b)
{
	long long ans = (a %= b);
	while (b != 0)
	{
		int tmp = b;
		b = ans % b;
		ans = tmp;
	}
	return ans;
}
int main()
{
	int n;
	scanf("%d", &n);
	long long t;
	vint c = 1;
	for (int i = 0; i < n; i++)
	{
		scanf("%I64d", &t);
		c = c * (t / gcd(c, t));
	}
	c.disp();
}
