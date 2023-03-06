#include<iostream>
using namespace std;

int main()
{
	int a[100];
	int n = 0, k = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	cin >> k;
	int dau = 0, cuoi = n - 1;
	while (dau <= cuoi)
	{
		int giua = (dau + cuoi) / 2;
		if (a[giua] == k)
		{
			cout << giua;
		}
		if (a[giua] > k)
		{
			cuoi = giua - 1;
		}
		else
		{
			dau = giua + 1;
		}
	}

	return 0;
}