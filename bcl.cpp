#include <stdio.h>
#include <ctype.h>
#include <algorithm>
#define REP(a, b, c) for (int a = b; a < c; a++)
#define Rep(a, b) REP(i, a, b)
#define rep(a) Rep(0, a)
using namespace std;
char s[60606];
char ans[30303];
char buf[60606];
int na;
int sa[60606];
int t1[120606], t2[120606], c[60606];
char *nw = buf;
int main()
{
fread(buf, 60606, 1, stdin);
int n = 0;
while (!isdigit(*nw))nw++;
while (isdigit(*nw))n = n * 10 + *(nw++) - '0';
rep(n)
{
while (!isalpha(*nw))nw++;
s[i] = *(nw++) - 'A' + 2;
}
rep(n)s[n + i + 1] = s[n - i - 1];
int N = n + n + 2;
s[n] = 0, s[n + n + 1] = 1;
int *x = t1, *y = t2;
rep(N)c[x[i] = s[i]]++;
Rep(1, 28)c[i] += c[i - 1];
for (int i = N - 1; i >= 0; i--)sa[--c[s[i]]] = i;
int m = 28;
for (int k = 1; k <= N; k <<= 1)
{
int p = 0;
Rep(N - k, N)y[p++] = i;
rep(N)if (sa[i] >= k)y[p++] = sa[i] - k;
rep(m)c[i] = 0;
rep(N)c[x[i]]++;
Rep(1, m)c[i] += c[i - 1];
for (int i = N - 1; i >= 0; i--)sa[--c[x[y[i]]]] = y[i];
swap(x, y);
p = 0;
x[sa[0]] = 0;
Rep(1, N)x[sa[i]] = y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] ? p : ++p;
if (p == N - 1)break;
m = p + 1;
}
int st = 0, ed = n - 1;
while (st <= ed)
{
if (x[st] < x[N - ed - 2])ans[na++] = s[st++];
else ans[na++] = s[ed--];
}
rep(n)
{
putchar(ans[i] + 'A' - 2);
if (!((i + 1) % 80))putchar('\n');
}
}
