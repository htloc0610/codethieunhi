#include<iostream>
using namespace std;

int main()
{
	int n = 0, m = 0;
	cin >> n >> m;
	int a[50000 + 2] = { 0 };
	while (m != 0)
	{
		int l = 0, r = 0, i = 0;
		cin >> l >> r >> i;
		a[l] += i;
		a[r + 1] -= i;
		--m;
	}
	for (int i = 1; i < n + 1; i++)
	{
		a[i] += a[i - 1];
	}
	int k = 0;
	cin >> k;
	while (k != 0)
	{
		int l = 0, r = 0;
		cin >> l >> r;
		int max = a[l];
		for (int i = l; i < r + 1; i++)
		{
			if (max < a[i])
			{
				max = a[i];
			}
		}
		cout << max << endl;
		--k;
	}
	return 0;
}