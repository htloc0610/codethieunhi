/*
* Hãy đếm số lượng thừa số nguyên tố khác nhau trong phân tích thừa số nguyên tố của 1 số nguyên dương n
*/
#include<iostream>
using namespace std;

bool isPrime(long n)
{
	for (long i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
		{
			return 0;
		}
	}
	return n > 1;
}

int main()
{
	long n = 0, m = 0;
	cin >> n;
	while (n != 0)
	{
		cin >> m;
		int dem = 0;
		for (long i = 1; i <= m; i++)
		{
			if (m % i == 0)
			{
				if (isPrime(i))
				{
					++dem;
				}
			}
		}
		cout << dem << endl;
		/*if (n != 1)
		{
			cout<<endl;
		}*/
		--n;
	}
	return 0;
}