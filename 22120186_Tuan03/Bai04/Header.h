#pragma once
#include<iostream>
#include<iomanip>
using namespace std;

struct SinhVien {
	char* HoTen = new char[50];
	float Toan;
	float Ly;
	float Hoa;
	char* DiaChi = new char[100];
};

void Input(SinhVien* sv);

void Rank(SinhVien* sv);

void Output(SinhVien* sv);

void Find (SinhVien* sv, int n);