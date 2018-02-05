#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
const long long mod = 998244353;
const long long vod = 1e16;
char buf[10101];
struct vint
{
	long long t[1010];
	int l;
	void init()
	{
		memset(t, 0, sizeof(t));
		int len = strlen(buf);
		l = len / 16 + 1;
		for (int i = 0; i < len / 2; i++)
			swap(buf[i], buf[len - 1 - i]);
		for (int i = 0; i < l; i++)
		{
			long long d = 1;
			for (int j = 0; j < 16; j++)
			{
				if (i * 16 + j >= len)
					break;
				t[i] += (buf[i * 16 + j] - '0') * d;
				d *= 10;
			}
		}
		if (t[0] == 0 && l == 1)
		{
			printf("1");
			exit(0);
		}
		t[0] -= 1;
		int i = 0;
		while (t[i] < 0)
		{
			t[i] += vod, t[i + 1]--;
			i++;
		}
	}
	bool d2()
	{
		bool ret = (t[0] & 1);
		for (int i = l - 1; i > 0; i--)
		{
			t[i - 1] += vod * (t[i] & 1);
			t[i] >>= 1;
		}
		t[0] >>= 1;
		if (l > 1 && !t[l - 1])
			l--;
		return ret;
	}
};
struct matrix
{
	long long v[4][4];	
	matrix operator*(const matrix &a) const
	{
		matrix ret = {0};
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				for (int k = 0; k < 4; k++)
					ret.v[i][j] = (ret.v[i][j] + (v[k][j] * a.v[i][k]) % mod) % mod;
		return ret;
	}
}orig, mt[40000];
int main()
{
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
	scanf("%s", buf);
	orig.v[0][0] = 2;
	orig.v[1][0] = orig.v[2][0] = orig.v[3][0] = 1;
	mt[0].v[0][0] = mt[0].v[0][1] = mt[0].v[0][2] = mt[0].v[1][1] = mt[0].v[1][2] = mt[0].v[2][1] = mt[0].v[3][1] = mt[0].v[3][3] = 1;
	mt[0].v[0][3] = mt[0].v[1][3] = 2;
	for (int i = 1; i < 37777; i++)
		mt[i] = mt[i - 1] * mt[i - 1];
	vint vt;
	vt.init();
	for (int j = 0; j < 37777; j++)
		if (vt.d2())
			orig = orig * mt[j];
	printf("%lld", orig.v[0][0]);
}
