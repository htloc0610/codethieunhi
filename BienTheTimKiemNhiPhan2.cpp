#include<iostream>
using namespace std;

int TimKiemNhiPhan(int a[], int n, int k)
{
	int dau = 0, cuoi = n - 1, kq = 0;
	while (dau <= cuoi)
	{
		int giua = (dau + cuoi) / 2;
		if (a[giua] >= k)
		{
			kq = giua;
			cuoi = giua - 1;
		}
		else
		{
			dau = giua + 1;
		}
	}
	return kq;
}

int main()
{
	int a[20];
	int n, k;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	cin >> k;
	cout << TimKiemNhiPhan(a, n, k);

	return 0;
}