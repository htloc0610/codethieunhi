#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int main()
{
	long long m = 0, n = 0, k = 0;
	cin >> m >> n >> k;
	vector <long long> a(m + 1);
	vector <long long> s(m + 1);
	for (long long i = 1; i < m + 1; i++)
	{
		cin >> a[i];
	}
	for (long long i = 1; i < m + 1; i++)
	{
		for (long long j = 1; j < i; j++)
		{
			if (a[j] < a[i])
			{
				swap(a[j], a[i]);
			}
		}
	}
	s[0] = 0;
	for (long long i = 1; i < m + 1; i++)
	{
		s[i] = s[i - 1] + a[i];
	}
	long long max = LLONG_MIN;
	bool check = 0;
	for (long long i = 1; i + n <= m + 1; i++)
	{
		long long l = i, r = i + n - 1;
		if (a[l] - a[r] <= k)
		{
			check = 1;
			if (s[r] - s[l-1] > max)
			{
				max = s[r] - s[l - 1];
			}
		}
	}
	if (check)
	{
		cout << max;
	}
	else
	{
		cout << -2;
	}

	return 0;
}
