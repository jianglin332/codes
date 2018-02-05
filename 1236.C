#include <cstdio>
int main()
{
	char d;
for(int i = 0; i < 10; i++) getchar();getchar();
	for (int i = 0; i < 10; i++)
	{
		fseek(stdin, -6, SEEK_CUR);
		putchar(getchar());
	}
}
