#include<iostream>
using namespace std;

int main()
{
	int d1 = 0, d2 = 0, d3 = 0;
	int m = 0;
	cin >> m;
	while (m != 0)
	{
		int x = 0, y = 0;
		cin >> x >> y;
		if ((x + y) % 2 != 0)
		{
			d3++;
		}
		d1 += x;
		d2 += y;
		--m;
	}
	if (d1 % 2 == 0 && d2 % 2 == 0)
	{
		cout << 0;
	}
	else if (d1 % 2 == 1 && d2 % 2 == 1)
	{
		if (d3 != 0)
		{
			cout << 1;
		}
		else
		{
			cout << -1;
		}
	}
	else
	{
		cout << -1;
	}

	return 0;
}