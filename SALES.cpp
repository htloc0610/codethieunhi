#include<iostream>
using namespace std;

int main()
{
	int n = 0;
	cin >> n;
	int* a = new int[n];
	int* b = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		b[i] = 1;
		for (int j = 0; j < i; j++)
		{
			if (a[i] == a[j])
			{
				b[i] = 0;
				b[j]++;
				break;
			}
		}
	}
	int dem = 0;
	bool check = 1;
	for (int i = 0; i < n; i++)
	{
		if (b[i] != 1)
		{
			if (b[i] - (b[i] / 3 * 3) == 1)
			{
				dem += (b[i] / 3 - 1) + 2;
			}
			else
			{
				dem += (b[i] / 3) + (b[i] % 3 / 2);
			}
		}
		else
		{
			check = 0;
			break;
		}
	}
	if (check)
	{
		cout << dem;
	}
	else
	{
		cout << -1;
	}
	delete[] a;
	delete[] b;

	return 0;
}