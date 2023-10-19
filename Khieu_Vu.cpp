//#include<iostream>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//bool customCompare(int a, int b) {
//	if ((a < 0 && b < 0)) {
//		return a > b;
//	}
//	else if ((a >= 0 && b >= 0))
//	{
//		return a < b;
//	}
//	else if (a < 0 && b >= 0) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//
//int main()
//{
//	int n, k;
//	cin >> n >> k;
//	vector<int> a(n);
//	for (int i = 0; i < n; i++)
//	{
//		cin >> a[i];
//	}
//	sort(a.begin(), a.end(), customCompare);
//	for (int x : a)
//	{
//		cout << x << " ";
//	}
//	cout << endl;
//	int dem = 0;
//	for (int i = 0; i < n; i++)
//	{
//		if (a[i] > 0)
//		{
//			for (int j = 0; j < i && a[j] < 0; j++)
//			{
//				int diff = a[i] - abs(a[j]);
//				if (diff >= 0 && diff <= k)
//				{
//					++dem;
//					//cout << i << " " << j << endl;
//				}
//				if (diff < 0)
//				{
//					break;
//				}
//			}
//		}
//	}
//	cout << dem;
//	return 0;
//}
//


#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;
	vector<int> a;
	vector<int> b;
	for (int i = 0; i < n; i++)
	{
		int num = 0;
		cin >> num;
		if (num > 0)
		{
			a.push_back(num);
		}
		else
		{
			b.push_back(-num);
		}
	}
	sort(b.begin(), b.end());
	//for (int x : a)
	//{
	//	cout << x << " ";
	//}
	//cout << endl;
	//for (int x : b)
	//{
	//	cout << x << " ";
	//}
	int cnt = 0;
	for (int i = 0; i < a.size(); i++)
	{
		int startt = lower_bound(b.begin(), b.end(), a[i] - k) - b.begin();
		int endd = upper_bound(b.begin(), b.end(), a[i]) - b.begin();
		endd--;
		if (startt <= endd)
		{
			cnt += (endd - startt + 1);
		}
	}
	cout << cnt;
	return 0;
}