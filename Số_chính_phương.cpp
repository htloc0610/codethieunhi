/*
* Kiểm tra số chính phương.
*/
#include<iostream>
#include<math.h>
using namespace std;

bool isSquare(long long n)
{
	if (((long long)sqrt(n) * sqrt(n) == n))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main()
{
	int n = 0;
	long long m = 0;
	cin >> n;
	while (n != 0)
	{
		cin >> m;
		if (isSquare(m))
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
		--n;
	}
	return 0;
}