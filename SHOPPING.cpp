#include <iostream>
using namespace std;

// Hàm tính số lượng ước của một số sử dụng phân tích thành thừa số nguyên tố
int countDivisors(int n) {
    int countt = 1;
    int div = 2; // Bắt đầu với thừa số nguyên tố nhỏ nhất

    while (div * div <= n) {
        int power = 0;
        while (n % div == 0) {
            n /= div;
            power++;
        }
        countt *= (power + 1); // Số lượng ước = (số mũ + 1) cho mỗi thừa số nguyên tố
        div = (div == 2) ? 3 : div + 2; // Bỏ qua các số chẵn (ngoại trừ số 2)
    }

    if (n > 1) {
        countt *= 2; // Nếu n là số nguyên tố, thừa số nguyên tố cuối cùng có số mũ là 1
    }

    return countt;
}

int main() {
    int n;
    cin >> n;
    long long sum = 0; // Sử dụng long long để xử lý các giá trị lớn hơn

    for (int k = 1; k < n; k++) {
        int l = n - k;
        sum += (long long)countDivisors(k) * countDivisors(l);
    }

    cout << sum << endl;
    return 0;
}