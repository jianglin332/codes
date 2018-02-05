/*
ID: jiangli16
PROG: gift1
LANG: C++
*/
#include <fstream>
#include <string>
#include <map>
using namespace std;
ofstream cout("gift1.out");
ifstream cin("gift1.in");
int main()
{
	map<string, int> mp;
	int n;
	cin>>n;
	string *strs = new string[n];
	for (int i = 0; i < n; i++)
		cin>>strs[i];
	for (int i = 0; i < n; i++)
	{
		string nm;
		cin>>nm;
		int a, b;
		cin>>a>>b;
		if (b == 0)
			continue;
		mp[nm] -= a - a % b;
		int c = a / b;
		for (int i = 0; i < b; i++)
		{
			string t;
			cin>>t;
			mp[t] += c;
		}
	}
	for (int i = 0; i < n; i++)
	{
		cout<<strs[i]<<' '<<mp[strs[i]]<<endl;
	}
	return 0;
}
