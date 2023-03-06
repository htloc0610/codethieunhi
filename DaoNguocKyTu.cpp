#include<iostream>
#include<cstring>
using namespace std;

void process(char str[], char outstr[])
{
	for (int i = 0; i < strlen(str); i++)
	{
		outstr[strlen(str) - 1 - i] = str[i];
	}
	outstr[strlen(str)] = '\0';
}

int main()
{
	const int MAX_SIZE = 100;
	char str[MAX_SIZE];
	cin.getline(str, 100);
	char outstr[MAX_SIZE];
	process(str, outstr);
	cout << outstr;

	return 0;
}