#include<iostream>
using namespace std;

class Student {
private:
	string name = "unname";
	int id;
	double mark;
public:
	Student()
	{
		cout << "1 Student duoc khai bao" << endl;
	}
	Student(string name, int id, double mark) {
		cout << "Khoi tao" << endl;
		this->name = name;
		this->id = id;
		this->mark = mark;
	}
	~Student()
	{
		cout << "1 Student bi huy" << endl;
	}
	//getter/setter
	//getter
	string getName()
	{
		string name = "ABC";
		return this->name;
	}
	void getInfo() {
		cout << name << " " << id << " " << mark << endl;
	}
	//setter
	void setName(string newName) {
		name = newName;
	}
	void setId(int id)
	{
		this->id = id;//this-> tro toi dia chi bien id trong private
	}


	//private:
	//public:
	//protected:
};

int main()
{
	Student a;
	Student b = { "Nam",2,7.5 };
	a.getInfo();
	b.getInfo();

	return 0;
}