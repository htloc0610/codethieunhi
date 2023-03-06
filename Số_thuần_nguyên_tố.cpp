/*
* Một số được coi là thuần nguyên tố nếu nó là số nguyên tố, tất cả các chữ số là nguyên tố và tổng chữ số của nó cũng là một số nguyên tố. Bài toán đặt ra là đếm xem trong một đoạn giữa hai số nguyên cho trước có bao nhiêu số thuần nguyên tố.
*/
#include<iostream>
#include <math.h>
using namespace std;

int snt(int n)
{
    for (int i = 2; i * i <= n; ++i)
    {
        if (n % i == 0) return 0;
    }
    return n > 1;
}

int check(int n)
{
    while (n != 0)
    {
        int x = n % 10;
        if (x != 2 && x != 3 && x != 5 && x != 7)
        {
            return 0;
        }
        n /= 10;
    }
    return 1;
}

int thuannt(int n)
{
    int sum = 0;
    while (n != 0)
    {
        sum += n % 10;
        n /= 10;
    }
    if (snt(sum))
        return 1;
    return 0;
}

int main()
{
    int x, y;
    cin >> x >> y;
    int dem = 0;
    for (int i = x; i <= y; ++i) {
        if (check(i) && snt(i) && thuannt(i)) ++dem;
    }
    cout << dem;
    return 0;
}