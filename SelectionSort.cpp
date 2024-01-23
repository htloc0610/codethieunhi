#include<bits/stdc++.h>
using namespace std;

int a[] = { 3, 2, 4, 6, 1, 9 };

int main()
{
    int n = sizeof(a) / sizeof(a[0]);
    for (int i = 0; i < n; i++)
    {
        int index = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[index] > a[j])
            {
                index = j;
            }
        }
        swap(a[i], a[index]);
    }
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}
