#include<iostream>
#include<map>
#include<set>
using namespace std;

void callSet()
{
	set<int> st;
	int n = 0;
	cin >> n;
	while (n != 0)
	{
		int m = 0;
		cin >> m;
		for (int i = 0; i < m; i++)
		{
			int x = 0;
			cin >> x;
			st.insert(x);
		}
		cout << st.size() << endl;
		--n;
	}
}

void callMap()
{
	map<int, int> mp;
	int n = 0;
	cin >> n;
	while (n != 0)
	{
		int m = 0;
		cin >> m;
		for (int i = 0; i < m; i++)
		{
			int x, count = 0;
			cin >> x;
			mp.insert({ x,0 });
		}
		cout << mp.size() << endl;
		--n;
	}
}


int main()
{
	//callSet();
	callMap();

	return 0;
}