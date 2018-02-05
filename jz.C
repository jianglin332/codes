#include <cstdio>
using namespace std;
int main()
{
	int n;
	scanf("%d\n%^c", &n);
	char c;
	for (int i = 0; i < n - 1; i++)
	{
		scanf(" %c", &c);
		printf("%c=%d ", c, i);
	}
	printf("\n%d", n - 1);
}
