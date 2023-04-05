#include<iostream>
using namespace std;

int main()
{
	int a[1000] = { 0 };
	int dem[1000] = { 0 };
	int vet[1000] = { 0 };
	int n = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	dem[0] = 1; dem[1] = 2;
	a[0] = -1000000;
	a[n + 1] = 1000000;
	for (int i = 0; i <= n + 1; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if ((a[i] > a[j]) && (dem[i] < dem[j] + 1))
			{
				dem[i] = dem[j] + 1;
				vet[i] = j;
			}
		}
	}
	cout << dem[n + 1] - 2 << endl;
	int z = 0;
	int x = n + 1;
	while (z < dem[n + 1] - 2)
	{
		x = vet[x];
		cout << a[x] << " ";
		z++;
	}


	return 0;
}