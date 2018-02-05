#include <cstdio>
#include <cstdlib>
int main(int argc, char **argv)
{
	int sz = atoi(argv[1]);
	bool *np = new bool[sz + 500];
	for (int i = 2; i < sz + 500; i++)
	{
		if (!np[i])
		{
			if (i > sz)
			{
				printf("%d", i);
				return 0;
			}
			for (long long j = 2; (j * i) < sz + 500; j += 1)
				np[j * i] = 1;
		}
	}
}
