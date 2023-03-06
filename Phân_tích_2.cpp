/*
* Hãy phân tích một số nguyên dương thành tích các thừa số nguyên tố.
*/
#include<iostream>
using namespace std;

void sudungsangnguyento(bool sangnguyento[])
{
	for (int i = 0; i < 100001; i++)
	{
		sangnguyento[i] = 1;
	}
	sangnguyento[0] = 0;
	sangnguyento[1] = 1;
	for (int i = 2; i * i < 100001; i++)
	{
		if (sangnguyento[i])
		{
			for (int j = i * i; j < 100001; j += i)
			{
				sangnguyento[j] = 0;
			}
		}
	}
}

int main()
{
	bool sangnguyento[100001];
	sudungsangnguyento(sangnguyento);
	int n = 0, m = 0, f = 1;
	cin >> n;
	while (n != 0)
	{
		cin >> m;
		cout << "#TC" << f << ": ";
		for (int i = 2; i / 2 <= m; i++)
		{
			if (m % i == 0)
			{
				if (sangnguyento[i])
				{
					int dem = 0;
					while (m % i == 0)
					{
						m /= i;
						++dem;
					}
					cout << i << "(" << dem << ")" << " ";
				}

			}
		}
		cout << endl;
		++f;
		--n;
	}
	return 0;
}