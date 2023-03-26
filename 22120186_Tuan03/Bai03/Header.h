#pragma once
#include<iostream>
#include<iomanip>
using namespace std;

struct SinhVien {
	char* HoTen = new char[50];
	float Toan;
	float Ly;
	float Hoa;
};

void Input(SinhVien* sv);

void Rank(SinhVien* sv);

void Output(SinhVien* sv);