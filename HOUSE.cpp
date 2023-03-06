#include<iostream>
#include<climits>
using namespace std;

int main()
{
	long long n = 0, max = LLONG_MIN;
	cin >> n;
	long long* a = new long long[n];
	for (long long i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	for (long long i = 0; i < n; i++)
	{
		long long max2 = LLONG_MIN;
		for (long long j = i + 1; j < n; j++)
		{
			if (a[i] - a[j] > max2)
			{
				max2 = a[i] - a[j];
			}
		}
		if (max2 > max)
		{
			max = max2;
		}
	}

	if (max > 0)//Lai > 0 moi xuat ra khong thi xuat ra lo
	{
		cout << max;
	}
	else
	{
		cout << "Lo nang roi!";
	}
	delete[] a;

	return 0;
}