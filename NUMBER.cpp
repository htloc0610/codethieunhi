#include<iostream>
#include<vector>
#include <cstring>
using namespace std;

#define ll long long

int main()
{
	int n = 0, m = 0;
	cin >> n >> m;
	int a[1000];
	memset(a, 0, sizeof(a));
	while (m != 0)
	{
		int k = 0, l = 0;
		cin >> k >> l;
		for (int i = k; i <= l; i++)
		{
			a[i]++;
		}
		--m;
	}
	for (int i = 1; i <= n; i++)
	{
		if (a[i] % 2 == 0)
		{
			cout << 0 << " ";
		}
		else
		{
			cout << 1 << " ";
		}
	}
	return 0;
}