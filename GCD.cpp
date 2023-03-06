#include<iostream>
using namespace std;

long long GCD(long long n)
{
	for (long long i = 2; i <= n; i++)
	{
		if (n % i == 0)
		{
			return i;
		}
	}
	return n;
}

int main()
{
	long long n = 0, s = 1;
	cin >> n;
	long long* a = new long long[n];
	for (long long i = 0; i < n; i++)
	{
		cin >> a[i];
		bool check = true;
		for (long long j = 0; j < i; j++)
		{
			if (GCD(a[j]) == GCD(a[i]))
			{
				check = false;
				break;
			}
		}	
		if (check)
		{
			s *= GCD(a[i]);
		}
	}
	cout << s;
	delete[] a;

	return 0;
}