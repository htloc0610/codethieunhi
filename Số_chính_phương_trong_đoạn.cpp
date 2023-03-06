/*
* In ra các số chính phương trong đoạn từ a tới b.
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
	int n = 0, a = 0, b = 0;
	cin >> n;
	while (n != 0)
	{
		cin >> a >> b;
		for (int i = a; i <= b; i++)
		{
			if (isSquare(i))
			{
				cout << i << " ";
			}
		}
		cout << endl;
		--n;
	}
	return 0;
}