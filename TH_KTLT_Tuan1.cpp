#include<iostream>
using namespace std;

struct Sach {
	char maso[7];
	char ten[50];
	char tgia[50];
	char nxban[50];
	int gia;
	int sotrang;
	int namxuatban;
};

Sach NhapDanhSach();
void XuatDanhSach(Sach a);
void SapXepTangDanTheoNamXuatBan(Sach* a, int n);
void TimSachCoGiaBanCaoNhat(Sach* a, int n, int k);
void Them1Quyensach(Sach*& a, Sach a1, int& n, int k);
void XoaPhanTu(Sach* a, int& n, int vitri);

int main()
{
	int n = 0;
	cout << "Nhap vao so sach can nhap thong tin: ";
	cin >> n;
	Sach* a = new Sach[n];
	//Nhap danh sach
	for (int i = 0; i < n; i++)
	{
		a[i] = NhapDanhSach();
	}
	cout << "Danh sach tang dan theo nam xuat ban la: " << endl;
	//Sap xep tang dan theo nam xuat ban
	SapXepTangDanTheoNamXuatBan(a, n);
	//Xuat danh sach
	for (int i = 0; i < n; i++)
	{
		XuatDanhSach(a[i]);
	}
	//Tim sach co gia ban cao nhat
	int k = 0;
	cout << "Nhap vao so trang: ";
	cin >> k;
	cout << "Sach co gia tien lon nhat voi so trang be hon " << k << " la: " << endl;
	TimSachCoGiaBanCaoNhat(a, n, k);
	//Them 1 quyen sach
	cout << "Nhap thong tin sach can them: " << endl;
	Sach a1 = NhapDanhSach();
	int x;
	cout << "Nhap vi tri can chen: ";
	cin >> x;
	Them1Quyensach(a, a1, n, x);
	for (int i = 0; i < n; i++)
	{
		XuatDanhSach(a[i]);
	}
	//Xoa sach co nam xuat ban truoc nam chi dinh
	int nam = 0;
	cout << "Nhap vao nam: ";
	cin >> nam;
	int vitri = 0;
	while (vitri < n)
	{
		if (a[vitri].namxuatban < nam)
		{
			XoaPhanTu(a, n, vitri);
		}
		else
		{
			vitri++;
		}
	}
	cout << "Danh sach sau khi xoa la: " << endl;
	for (int i = 0; i < n; i++)
	{
		XuatDanhSach(a[i]);
	}
	delete[] a;

	return 0;
}

Sach NhapDanhSach()
{
	Sach a;
	cin.ignore();
	cout << "Nhap ma so sach: ";
	cin.getline(a.maso, 7);
	cout << "Nhap ten sach: ";
	cin.getline(a.ten, 50);
	cout << "Nhap ten tac gia: ";
	cin.getline(a.tgia, 50);
	cout << "Nhap nha xuat ban: ";
	cin.getline(a.nxban, 50);
	cout << "Nhap gia tien: ";
	cin >> a.gia;
	cout << "Nhap so trang: ";
	cin >> a.sotrang;
	cout << "Nhap nam xuat ban: ";
	cin >> a.namxuatban;
	cout << endl << endl;
	return a;
}

void XuatDanhSach(Sach a)
{
	cout << "Ma so sach: " << a.maso << endl;
	cout << "Ten sach: " << a.ten << endl;
	cout << "Ten tac gia: " << a.tgia << endl;
	cout << "Nha xuat ban: " << a.nxban << endl;
	cout << "Gia tien: " << a.gia << " ngan dong" << endl;
	cout << "So trang: " << a.sotrang << endl;
	cout << "Nam xuat ban: " << a.namxuatban << endl;
	cout << endl << endl;
}

void SapXepTangDanTheoNamXuatBan(Sach* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (a[i].namxuatban < a[j].namxuatban)
			{
				swap(a[i], a[j]);
			}
		}
	}
}

void TimSachCoGiaBanCaoNhat(Sach*a,int n, int k)
{
	int vitri = 0, gia = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i].sotrang <= k)
		{
			if (a[i].gia > gia)
			{
				vitri = i;
				gia = a[i].gia;
			}
		}
	}
	XuatDanhSach(a[vitri]);
}

void Them1Quyensach(Sach* &a,Sach a1 ,int &n, int k)
{
	Sach* b = new Sach[n+1];
	for (int i = 0; i < k; i++)
	{
		b[i] = a[i];
	}
	if (k > n - 1)
	{
		b[n] = a1;
	}
	else
	{
		b[k] = a1;
		for (int i = k + 1; i < n + 1; i++)
		{
			b[i] = a[i - 1];
		}
	}
	Sach* c = a;
	a = b;
	n++;
	delete[]c;
}

void XoaPhanTu(Sach* a, int &n,int vitri)
{
	for (int i = vitri; i < n; i++)
	{
		a[i] = a[i + 1];
	}
	n--;
}