ed2k://|file|SW_DVD5_Office_Professional_Plus_2013_64Bit_ChnSimp_MLF_X18-55285.ISO|958879744|678EF5DD83F825E97FB710996E0BA597|/
#include <cstdio>
char gnc()
{
	char c = getchar();
	fseek(stdin, -2L, SEEK_CUR);
	return c;
}
int main()
{
	int e, tmp;
	scanf("%d", &e);
	fseek(stdin, -1L, SEEK_END);
	int n = 0, d = 1;
	char c;
	while ((c = getchar()) > '9' || c < '0')
		fseek(stdin, -2L, SEEK_CUR);
	fseek(stdin, -2L, SEEK_CUR);
	while (e)
	{
		if (c == ' ')
		{
			printf("%d ", n);
			e--;
			n = 0;
			d = 1;
		}
		else if (c <= '9' && c >= '0')
		{
			n += (c - '0') * d;
			d *= 10;
		}
		else
		{
			printf("%d ", n);
			e--;
			n = 0;
			d = 1;
		}
		c = gnc();
	}
	return 0;
}
