#include<iostream>
#include<vector>
using namespace std;

int main() {
    // freopen("SUMEVEN.INP", "r", stdin);
    // freopen("SUMEVEN.OUT", "w", stdout);

    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1, 0);
    a[0] = 0;
    for (int i = 1; i <= n; i++) 
    {
        int x;
        cin >> a[i];
        if (i % 2 == 0)
        {
            a[i] = a[i - 2] + a[i];
        }
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        if (l % 2 != 0)
        {
            l++;
        }
        if (l % 2 != 0)
        {
            r--;
        }
        int s = a[r] - a[l - 2];
        cout << s << "\n";
    }
    return 0;
}