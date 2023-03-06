#include<iostream>
#include<string>
#include<stack>
using namespace std;

int main()
{
	stack <int> a;
	string s;
	getline(cin, s);
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '(')
		{
			a.push(i+1);
		}
		else
		{
			cout << a.top() << " " << i + 1 << endl;
			a.pop();
		}
	}

	return 0;
}