#include <stdio.h>
char s[333][333];
int main()
{
	int n;
	scanf("%d", &n);
	int a = (n - 1) / 2;
	int b = n - 1 - a;
	printf(">");
	for (int i = 0; i < a; i++)
		printf(">>");
	for (int i = 0; i < b; i++)
		printf(">.");
	printf("v\n");
	for (int i = 1; i < n; i++)
	{
		printf("^v");
		for (int i = 0; i < b; i++)
			printf(".<");
		for (int i = 0; i < a; i++)
			printf("<<");
		printf("\n^");
		for (int i = 0; i < a; i++)
			printf(">>");
		for (int i = 0; i < b; i++)
			printf(">.");
		printf("v\n");
	}
	printf("^");
	for (int i = 0; i < b; i++)
		printf(".<");
	for (int i = 0; i < a; i++)
		printf("<<");
	printf("<\n1 1");
}
