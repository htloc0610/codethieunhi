#include<iostream>
#include<vector>
using namespace std;

struct pupil{
	char name[31];
	char code[6];
	float grade;
};
typedef struct pupil PUPIL;

void inputPupil(PUPIL& p)
{
	cin.getline(p.name, 31);
	cin.getline(p.code, 6);
	cin.ignore();
	cin >> p.grade;
}

void arrayInput(vector<PUPIL>& a,int n)
{
	a.resize(0);
	while (n != 0)
	{
		PUPIL x;
		inputPupil(x);
		a.push_back(x);
		--n;
	}
	a.resize(n);
}

int main()
{
	vector<PUPIL>a;
	int n = 0;
	cin >> n;
	arrayInput(a, n);
	return 0;
}