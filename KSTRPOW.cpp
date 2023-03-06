#include<iostream>
#include <string>
using namespace std;

int main()
{
	string s, s1, s2;
	int n = 0;
	getline(cin,s);
	getline(cin, s1);
	cin >> n;
	while (n != 0)
	{
		s2 += s;
		--n;
	}
	if (s2 == s1)
	{
		cout << "YES";
	}
	else
	{
		cout << "NO";
	}
	return 0;
}