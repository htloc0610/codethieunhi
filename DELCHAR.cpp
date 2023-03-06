#include<iostream>
#include<cstring>
#include<math.h>
using namespace std;

#define MAX 300000

bool DELCHAR(char s[], int n, int a, int b)
{
	char s1[MAX], s2[MAX];
	strcpy_s(s1, s);
	strcpy_s(s2, s);
	for (int i = a; i < n; i++)
	{
		s1[i] = s1[i + 1];
	}
	for (int i = b; i < n; i++)
	{
		s2[i] = s2[i + 1];
	}
	for (int i = 0; i < n - 2; i++)
	{
		if (s1[i] != s2[i])
		{
			return 0;
		}
	}
	return 1;
}

int main()
{
	char s[MAX];
	int n, dem = 0;
	cin >> n;
	cin.ignore();
	cin.getline(s, n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (DELCHAR(s, n, i, j))
			{
				++dem;
			}
		}
	}
	cout << dem;
	return 0;
}