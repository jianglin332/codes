#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
char a[10101010];
char s[] = "input1.txt";
char t[] = "output1.txt";
void get(int t)
{
	s[5] = t + '0';
}
void gx(int s)
{
	t[6] = s + '0';
}
int main()
{
	int i = 0;
	freopen("problem.txt", "r", stdin);
	while (cin.getline(a, 10101010))
	{
		if (!strncmp(a, "InData=", 7))
		{
			cin.getline(a, 10101010);
			cin.getline(a, 10101010);
			get(i);
			freopen(s, "w", stdout);
			cout<<a<<endl;
			cin.getline(a, 10101010);
			cout<<a;
		}
		if (!strncmp(a, "OutData=", 8))
		{
			cin.getline(a, 10101010);
			cin.getline(a, 10101010);
			gx(i++);
			freopen(t, "w", stdout);
			cout<<a;
		}
	}
}
