#pragma once
#include<iostream>
using namespace std;

struct SinhVien {
	char* HoTen = new char[50];
	float Toan;
	float Ly;
	float Hoa;
};

void Input(SinhVien* sv);

void Output(SinhVien* sv);
