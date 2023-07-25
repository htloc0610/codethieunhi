#include<iostream>
#include<vector>
#include<set>
using namespace std;

float count(vector<char> s, int i, int j)
{
	set<char> a;
	for (int n = i; n <= j; n++)
	{
		a.insert(s[n]);
	}
	return (float)a.size() / (j - i + 1);
}

int main()
{
	int n = 0;
	cin >> n;
	vector<char> s(n);
	for (int i = 0; i < n; i++)
	{
		cin >> s[i];
	}
	int i = 0, j = 0; // Initialize i and j to 0.
	float color = 1;

	while (j < n) // Use "< n" instead of "<= n" to avoid going out of range.
	{
		if (count(s, i, j) <= color)
		{
			color = count(s, i, j);
			j++;
		}
		else
		{
			break;
		}
	}
	j--;
	while (i < j && count(s, i, j) <= color) // Adjust the loop condition to prevent i and j from being equal.
	{
		color = count(s, i, j);
		i++;
	}
	i--;
	cout << i << " " << j;
	return 0;
}
