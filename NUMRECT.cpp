#include<iostream>
using namespace std;

#define ll long long

ll C(ll n) {
	return  n * (n - 1) / 2;
}

int main()
{
	ll q = 0;
	cin >> q;
	while (q-- != 0)
	{
		ll m = 0, n = 0;
		cin >> m >> n;
		m++; n++;
		cout << C(m) * C(n) << endl;
	}
}
