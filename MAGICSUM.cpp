#include<iostream>
using namespace std;

int main()
{
	int n, s = 0;
	cin >> n;
	while (n-- != 0)
	{
		int a, b;
		cin >> a >> b;
		s += a + b;
	}
	cout << s;

	return 0;
}