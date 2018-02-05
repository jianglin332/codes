#include <stdio.h>
bool IsNotPrime[10101010];
int Prime[10101010], NumberOfPrime;
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 2; i <= n; i++)
		if (!IsNotPrime[i])
		{
			Prime[NumberOfPrime++] = i; 
			for (int j = i; j * (long long)i <= n; j++)
				IsNotPrime[j * i] = 1;
		}
	printf("%d\n", NumberOfPrime);
}
