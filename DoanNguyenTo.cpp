#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

vector<bool>snt(100001, true);

void checksnt()
{
	snt[0] = false;
	snt[1] = false;
	for (int i = 2; i * i < 100001; i++)
	{
		if (snt[i] == true)
		{
			for (int j = i * 2; j < 100001; j += i)
			{
				snt[j] = false;
			}
		}
	}
}

int main()
{
	checksnt();
	int n, k;
	cin >> n >> k;
	vector<int> arr(n + 1);
	arr[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> arr[i];
		if (snt[arr[i]])
		{
			arr[i] = 0;
		}
		else
		{
			int dis = 1;
			while (snt[arr[i] + dis] == false && snt[arr[i] - dis] == false)
			{
				++dis;
			}
			arr[i] = dis;
		}
		arr[i] = arr[i - 1] + arr[i];
	}
	int res = INT_MAX;
	for (int i = k; i <= n; i++)
	{
		if (res > arr[i] - arr[i - k])
			res = arr[i] - arr[i - k];
	}

	cout << res;
	return 0;
}
