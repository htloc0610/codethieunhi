#include<iostream>
#include<math.h>
using namespace std;

int main()
{
	int n = 0, dem = 0;
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < n / i + 1; j++)
		{
			if (i * j < n)
			{
				++dem;
			}
		}
	}
	cout << dem;
	return 0;
}