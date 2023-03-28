#include<iostream>
using namespace std;

int main()
{
	long n = 0;
	cin >> n;
	long min = n;
	long* a = new long [n] ;
	for (long i = 0; i < n; i++)
	{
		cin >> a[i];
		for (long j = 0; j < i; j++)
		{
			if (a[j] == a[i] && i - j < min)
			{
				min = i - j;
				break;
			}
		}
	}
	if (min == n)
	{
		cout << -1;
	}
	else
	{
		cout << min;
	}

	delete[] a;
	return 0;
}