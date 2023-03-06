#include<iostream>
#include<climits>
using namespace std;

int main()
{
	int n = 0;
	cin >> n;
	int* a = new int[n];
	int s = 0, max = INT_MIN;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		s += a[i];
	}
	for (int i = 0; i < n - 1; i++)
	{
		int s1 = s - 2 * (a[i] + a[i + 1]);
		if (s1 > max)
		{
			max = s1;
		}
	}
	cout << max;

	delete[] a;

	return 0;
}