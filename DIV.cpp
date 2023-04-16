#include<iostream>
using namespace std;

int SumDiv(int a)
{
	int s = 0;
	for (int i = 1; i * i <= a; i++)
	{
		if (a % i == 0)
		{
			if (a / i != i)
			{
				s += i + (a / i);
			}
			else
			{
				s += i;
			}
		}
	}
	return s;
}

int main()
{
	int n = 0;
	cin >> n;
	while (n != 0)
	{
		int i = 0;
		cin >> i;
		cout << SumDiv(i) << endl;
		--n;
	}
	return 0;
}