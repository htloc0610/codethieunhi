#include<iostream>
using namespace std;

#define ll long long

int main()
{
	ll n = 0, q = 0;
	cin >> n >> q;
	ll* a = new ll[n + 1];
	a[0] = 0;
	for (ll i = 1; i <= n; i++)
	{
		cin >> a[i];
		a[i] = a[i] + a[i - 1];
	}
	while (q != 0)
	{
		ll m = 0, l = 0, k = 0;
		cin >> m >> l >> k;
		if (m == 0)
		{
			cout << a[k] << endl;;
		}
		//Max
		else
		{
			cout << a[l] - a[l - k] << endl;
		}
		--q;
	}
	delete[] a;
	return 0;
}
