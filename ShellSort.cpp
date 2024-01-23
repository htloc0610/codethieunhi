#include<bits/stdc++.h>
using namespace std;

int a[] = { 3, 2, 4, 6, 1, 9 };

int main()
{
    int n = sizeof(a) / sizeof(a[0]);
    int h = 0;
    for (h = 1; h < (n - 1) / 9; h = h * 3 + 1);
    for (; h > 0; h = h / 3)
    {
        for (int i = h; i < n - 1; i++)
        {
            int result = a[i];
            int j = i;
            while (j >= h && result < a[j - h])
            {
                a[j] = a[j - h];
                j -= h;
            }
            a[j] = result;
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}
