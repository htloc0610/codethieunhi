#include<bits/stdc++.h>
using namespace std;

void heaptify(int a[], int n, int i)
{
    int result = a[i];
    while (i < n / 2)
    {
        int child = 2 * i + 1;
        if (child < n - 1)
        {
            if (a[child] < a[child + 1])
            {
                child++;
            }
        }
        if (result >= a[child])
        {
            break;
        }
        a[i] = a[child];
        i = child;
    }
    a[i] = result;
}

void heapsort(int a[], int n)
{
    for (int k = n / 2 - 1; k >= 0; k--)
    {
        heaptify(a, n, k);
    }
    while (n > 1)
    {
        swap(a[0], a[n - 1]);
        n--;
        heaptify(a, n, 0);
    }
}

int a[] = { 3, 2, 4, 6, 1, 9 };

int main()
{
    int n = sizeof(a) / sizeof(a[0]);
    heapsort(a, n);
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}
