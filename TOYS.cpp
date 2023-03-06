#include<iostream>
using namespace std;

int main()
{
	unsigned long long n = 0, k = 0;
	cin >> n >> k;
	if (k <= n)
	{
		cout << (k - 1) / 2;
	}
	else
	{
		cout << (2 * n - k + 1) / 2;
	}

	return 0;
}