#include<iostream>
#include<string>
using namespace std;

int trongso(char a,int n)
{
	int khoangcach = (int)a - (int)'a' + n;
	if (khoangcach <= 25)
	{
		return khoangcach;
	}
	else
	{
		return khoangcach - 26;
	}
}

int main()
{
	string s;
	getline(cin, s);
	int m = 0, sum = 0;
	cin >> m;
	for (int i = 0; i < s.size(); i++)
	{
		sum += trongso(s[i], m);
	}
	cout << sum;
	return 0;
}