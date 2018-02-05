#include <stack>
#include <cstring>
#include <cstdio>
#include <cctype>
using namespace std;
char buf[30303030];
int g()
{
	static char *nw = buf;
	int r = 0;
	while (!isdigit(*nw))
		nw++;
	while (isdigit(*nw))
		r = r * 10 + *(nw++) - '0';
	return r;
}
int v[3030303];
int s[3030303];
int e[3030303];
stack<int> st;
int main()
{
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	fread(buf, 30303020, 1, stdin);
	int n = g();
	for (int i = 0; i < n; i++)
		v[i] = g();
	for (int i = 0; i < n; i++)
	{
		while ((!st.empty()) && v[st.top()] < v[i])
		{
			s[st.top()] = i;
			st.pop();
		}
		st.push(i);
	}
	while (!st.empty())
	{
		s[st.top()] = n;
		st.pop();
	}
	for (int i = n - 1; i >= 0; i--)
	{
		while ((!st.empty()) && v[st.top()] <= v[i])
		{
			e[st.top()] = i;
			st.pop();
		}
		st.push(i);
	}
	while (!st.empty())
	{
		e[st.top()] = -1;
		st.pop();
	}
	memset(buf, 0, sizeof(buf));
	for (int i = 0; i < n; i++)
	{
		long long ans = s[i] - i;
		ans *= i - e[i];
		long long d = 1e15;
		while (!(ans / d))
			d /= 10;
		static char *nw = buf;
		while (d)
		{
			*(nw++) = ans / d + '0';
			ans %= d;
			d /= 10;
		}
		*(nw++) = ' ';
	}
	fwrite(buf, sizeof(buf), 1, stdout);
	return 0;
}
