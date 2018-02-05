#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
long long f[1000];
int main()
{
	printf("%d", &f[1000] - &f[500]);
}
