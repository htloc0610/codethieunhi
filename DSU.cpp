#include<iostream>
using namespace std;

int parent[100];
int sizee[100];
int n;

void make_set()
{
	for (int i = 1; i <= n; i++)
	{
		parent[i] = i;
		sizee[i] = 1;
	}
}

int find(int v)
{
	if (v == parent[v])
	{
		return v;
	}
	return parent[v] = find(parent[v]);
}

void Union(int a, int b)
{
	a = find(a);
	b = find(b);
	if (a != b)
	{
		if (sizee[a] < sizee[b])
		{
			swap(a, b);
		}
		parent[b] = a;
		sizee[a] += sizee[b];
	}
}

int main()
{
	return 0;
}