#include<iostream>
#include<fstream>
using namespace std;

int TimKiemNhiPhan(int s[], int d, int c, int l, int k)
{
	int kc = 20 + 1;
	while (d <= c)
	{
		int g = (d + c) / 2;
		if (s[l] - s[g] >= k)
		{
			kc = l - g;
			d = g + 1;
		}
		else
		{
			c = g - 1;
		}
	}
	return kc;
}

int main()
{
	ifstream fin("SUB.INP");
	ofstream fout("SUB.OUT");
	int n, k, min = 20 + 1;
	int a[20], s[20];
	fin >> n >> k;
	for (int i = 1; i <= n; i++)
	{
		fin >> a[i];
		s[i] = s[i - 1] + a[i];
	}
	for (int i = 1; i <= n; i++)
	{
		int l = TimKiemNhiPhan(s, 1, i, i, k);
		if (l < min)
		{
			min = l;
		}
	}
	fout << min;

	return 0;
}