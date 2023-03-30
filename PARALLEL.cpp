#include<iostream>
#include<vector>
using namespace std;

struct HOPDIEM {
	int n[12];
};

istream& operator >> (istream& is, HOPDIEM& a)
{
	for (int i = 0; i < 12; i++)
	{
		is >> a.n[i];
	}
	return is;
}

bool checkhopdiem(HOPDIEM x)
{
	for (int i = 0; i < 12; i++)
	{
		if (x.n[i] != 0)
		{
			return true;
		}
	}
	return false;
}

bool checkhinhhopchunhat(HOPDIEM x)
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (x.n[i] < x.n[j])
			{
				swap(x.n[i], x.n[j]);
			}
		}
	}
	for (int i = 0; i < 12; i+=4)
	{
		for (int j = 0; j < 4; j++)
		{
			if (x.n[i] != x.n[i + j])
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{
	HOPDIEM x;
	cin >> x;
	while (checkhopdiem(x))
	{
		if (checkhinhhopchunhat(x))
		{
			cout << "yes" << endl;
		}
		else
		{
			cout << "no" << endl;
		}
		cin >> x;
	}

	return 0;
}