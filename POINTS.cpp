#include<iostream>
using namespace std;

int main()
{
	int n, k = 0;
	cin >> n >> k;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		a[i] += k;
	}
	while (k != 0)
	{
		int l;
		cin >> l;
		a[l - 1]--;
		--k;
	}
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	delete[] a;

	return 0;
}