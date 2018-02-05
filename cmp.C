#include <cstdio>
int main()
{
	FILE *a = fopen("o.t", "r");
	FILE *b = fopen("output0.txt", "r");
	char c;
	while ((c = getc(b)) == getc(a));
	printf("%c", c);
}
