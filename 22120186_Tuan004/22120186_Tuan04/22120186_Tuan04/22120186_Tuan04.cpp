#include<iostream>
#include<string>
#include<fstream>
using namespace std;

typedef struct HS
{
	char MaSo[8];
	char HoTen[20];
	float Diem[3]; //Toán, Lý, Hóa
} HocSinh;

int ReadMem(ifstream& input)
{
	int n = 0;
	string s;
	while (!input.eof())
	{
		getline(input, s);
		n++;
	}
	return n;
}

void ReadFile(ifstream& input,HocSinh *a)
{
	string s;
	int i = 0;
	while (!input.eof())
	{
		// Tach Ma So
		getline(input, s, '	');
		for (int j = 0; j < s.size(); j++)
		{
			a[i].MaSo[j] = s[j];
		}
		a[i].MaSo[s.size()] = '\0';
		// Tach Ho Ten
		getline(input, s, '	');
		for (int j = 0; j < s.size(); j++)
		{
			a[i].HoTen[j] = s[j];
		}
		a[i].HoTen[s.size()] = '\0';
		// Tach diem
		//Toan
		getline(input, s, ' ');
		a[i].Diem[0] = stof(s);
		//Ly
		getline(input, s, ' ');
		a[i].Diem[1] = stof(s);
		//Hoa
		getline(input, s);
		a[i].Diem[2] = stof(s);
		i++;
	}
}

float DTB(HocSinh a)
{
	return (a.Diem[0] + a.Diem[1] + a.Diem[2]) / 3;
}

int MemOfQ1(HocSinh* a, int n)
{
	int x = 0;
	for (int i = 0; i < n; i++)
	{
		if (DTB(a[i]) >= 8)
		{
			++x;
		}
	}
	return x;
}

int MemOfQ2(HocSinh* a, int n)
{
	int x = 0;
	for (int i = 0; i < n; i++)
	{
		if (DTB(a[i]) < 5)
		{
			++x;
		}
	}
	return x;
}

void SetMem(HocSinh *Q1,HocSinh *Q2 ,HocSinh *a, int n)
{
	int j = 0, k = 0;
	for (int i = 0; i < n; i++)
	{
		if (DTB(a[i]) >= 8)
		{
			Q1[j++] = a[i];
		}
		else if (DTB(a[i]) < 5)
		{
			Q2[k++] = a[i];
		}
	}
}

void Sort(HocSinh *a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (DTB(a[j]) < DTB(a[i]))
			{
				swap(a[j], a[i]);
			}
		}
	}
}

void ReadFile(HocSinh* a, int n,string s)
{
	ofstream output(s);
	if (output.is_open())
	{
		for (int i = 0; i < n; i++)
		{
			output << a[i].MaSo << "\t" << a[i].HoTen << "\t" << a[i].Diem[0] << " " << a[i].Diem[1] << " " << a[i].Diem[2] << endl;
		}
	}
	else
	{
		cout << "Khong the ghi file";
	}
	output.close();
}

int main()
{
	ifstream input("DS_hoc_sinh.csv");
	if (input.is_open())
	{
		int n = ReadMem(input);
		input.seekg(0, 0);
		HocSinh * a = new HocSinh[n];
		ReadFile(input, a);
		for (int i = 0; i < n; i++)
		{
			cout << a[i].MaSo << "\t" << a[i].HoTen << "\t" << a[i].Diem[0] << " " << a[i].Diem[1] << " " << a[i].Diem[2] << endl;
		}
		HocSinh* Q1 = new HocSinh[MemOfQ1(a, n)];
		HocSinh* Q2 = new HocSinh[MemOfQ2(a, n)];
		SetMem(Q1, Q2, a, n);
		Sort(Q1, MemOfQ1(a, n));
		ReadFile(Q1, MemOfQ1(a, n), "DS_hoc_sinh_gioi.csv");
		Sort(Q2, MemOfQ2(a, n));
		ReadFile(Q2, MemOfQ2(a, n), "DS_hoc_sinh_kem.csv");
		input.close();
		delete[] a;
		delete[] Q1;
		delete[] Q2;
	}
	else
	{
		cout << "Khong doc duoc file";
	}
	return 0;
}