#include"Header.h";

void Input(SinhVien* sv)
{
	cin.ignore();
	cout << "Nhap vao ho va ten: ";
	cin.getline(sv->HoTen, 50);
	cout << "Nhap diem Toan: ";
	cin >> sv->Toan;
	while (sv->Toan < 0 || sv->Toan>10)
	{
		cout << "Nhap lai diem Toan: ";
		cin >> sv->Toan;
	}
	cout << "Nhap diem Ly: ";
	cin >> sv->Ly;
	while (sv->Ly < 0 || sv->Ly>10)
	{
		cout << "Nhap lai diem Ly: ";
		cin >> sv->Ly;
	}
	cout << "Nhap diem Hoa: ";
	cin >> sv->Hoa;
	while (sv->Hoa < 0 || sv->Hoa>10)
	{
		cout << "Nhap lai diem Hoa: ";
		cin >> sv->Hoa;
	}
	cin.ignore();
	cout << "Nhap dia chi: ";
	cin.getline(sv->DiaChi, 100);
	cout << endl;
}
void Rank(SinhVien* sv)
{
	float a = (sv->Toan + sv->Ly + sv->Hoa) / 3;
	if (a >= 9 && a <= 10)
	{
		cout << "Xep loai: Xuat sac" << endl;
	}
	else if (a >= 8 && a < 9)
	{
		cout << "Xep loai: Gioi" << endl;
	}
	else if (a >= 7 && a < 8)
	{
		cout << "Xep loai: Kha" << endl;
	}
	else if (a >= 5 && a < 7)
	{
		cout << "Xep loai: Trung binh" << endl;
	}
	else
	{
		cout << "Xep loai: Yeu" << endl;
	}
}

void Output(SinhVien* sv)
{
	cout << "Ho Ten: " << sv->HoTen << "\t" << "Diem Toan: " << sv->Toan << "\t" << "Diem Ly: " << sv->Ly << "\t" << "Diem Hoa: " << sv->Hoa << "\t" << "Diem Trung Binh: " << setprecision(3) << (sv->Toan + sv->Ly + sv->Hoa) / 3 << " ";
	Rank(sv);
}

void Find(SinhVien* sv,int n)
{
	char* a = new char[100];
	bool check = 0;
	cout << "Nhap dia chi can tim kiem: ";
	cin.getline(a, 100);
	for (int i = 0; i < n; i++)
	{
		if (strcmp(a, sv[i].DiaChi) == 0)
		{
			Output(&sv[i]);
			check = 1;
		}
	}
	if (!check)
	{
		cout << "Khong co sinh vien o dia chi tren";
	}

	delete[] a;
}