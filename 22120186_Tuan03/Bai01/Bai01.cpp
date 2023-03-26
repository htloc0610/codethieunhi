//So may 24
#include"Header.h";

int main()
{
	int n = 0;
	cout << "Nhap so luong sinh vien: ";
	cin >> n;
	while (n < 0 || n>10)
	{
		cout << "Vui long nhap lai so luong sinh vien dung yeu cau: ";
		cin >> n;
	}
	SinhVien* sv = new SinhVien[n];
	for (int i = 0; i < n; i++)
	{
		Input(&sv[i]);
	}
	for (int i = 0; i < n; i++)
	{
		Output(&sv[i]);
	}
	delete[] sv;

	return 0;
}