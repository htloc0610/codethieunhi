#include<iostream>
#include<string>
using namespace std;

struct Sach {
	int masach;
	string tensach;
	string tacgia;
	int namxuatban;
	int giatien;
	int soluong;
	string theloai;
};

struct Node {
	Sach sach;
	bool moinhapkho;
	bool sachduocban;
	Node* next;
};

istream& operator >> (istream& in, Sach& sach)
{
	cout << "\tNHAP DU LIEU CHO SACH\n";
	cout << "Nhap vao ma sach: ";
	in >> sach.masach;
	in.ignore();
	cout << "Nhap vao ten sach: ";
	getline(in, sach.tensach);
	cout << "Nhap vao ten tac gia: ";
	getline(in, sach.tacgia);
	cout << "Nhap vao nam xuat ban: ";
	in >> sach.namxuatban;
	cout << "Nhap vao gia tien: ";
	in >> sach.giatien;
	cout << "Nhap vao so luong: ";
	in >> sach.soluong;
	in.ignore();
	cout << "Nhap vao the loai: ";
	getline(in, sach.theloai);
	return in;
}

ostream& operator << (ostream& out, Sach& sach)
{
	out << "\tDU LIEU CUA SACH\n";
	out << "Ma sach: " << sach.masach << endl;
	out << "Ten sach: " << sach.tensach << endl;
	out << "Ten tac gia: " <<sach.tacgia << endl;
	out << "Nam xuat ban: " << sach.namxuatban << endl;
	out << "Gia tien: " << sach.giatien << endl;
	out << "So luong: " << sach.soluong << endl;
	out << "The loai: " << sach.theloai << endl;
	return out;
}

Node* newNode(Sach sach)
{
	Node* node = new Node;
	node->sach = sach;
	node->moinhapkho = true;
	node->sachduocban;
	node->next = NULL;
	return node;
}

void addNode(Node* &head, Sach sach)
{
	if (head == NULL)
	{
		head = newNode(sach);
		bool bansach;
		cout << "Sach co duoc ban hay khong (Nhap 1 neu ban hoac 0 neu khong ban): ";
		cin >> bansach;
		cout << endl;
		if (bansach)
		{
			head->sachduocban = true;
		}
		else
		{
			head->sachduocban = false;
		}
	}
	else
	{
		head->moinhapkho = false;
		addNode(head->next, sach);
	}
}

void Sapxepsoluongsach(Node* &head)
{
	if (head == NULL)
	{
		cout << "Danh sach rong!\n";
		return;
	}
	Node* current = head;

	while (current != NULL)
	{
		Node* index = current->next;

		while (index != NULL)
		{
			if (current->sach.soluong < index->sach.soluong)
			{
				Sach sachh = current->sach;
				current->sach = index->sach;
				index->sach = sachh;

				Node* mid = current;
				current->moinhapkho = index->moinhapkho;
				current->sachduocban = index->sachduocban;
				index->moinhapkho = mid->moinhapkho;
				index->sachduocban = mid->sachduocban;
			}

			index = index->next;
		}

		current = current->next;
	}

	cout << "\tDa sap xep sach thanh cong!\n";
}

void Timkiemsach(Node* head)
{
	if (head == NULL)
	{
		cout << "\tKhong co sach trong he thong!\n";
		return;
	}
	else
	{
		bool check = false;
		int masachh;
		cout << "Nhap vao ma sach can tim kiem: ";
		cin >> masachh;
		while (head != NULL)
		{
			if (head->sach.masach == masachh)
			{
				check = true;
				cout << head->sach;
				break;
			}
			head = head->next;
		}
		if (!check)
		{
			cout << "Khong tim thay sach!\n";
		}
	}
}

void Indanhsach(Node* head)
{
	if (head == NULL)
	{
		cout << "\tDanh sach rong!\n";
		return;
	}
	else
	{
		while (head != NULL)
		{
			cout << head->sach;
			head = head->next;
		}
	}
}

void menu(Node*& head) {
	cout << "\n===== MENU =====\n";
	cout << "1. Them sach\n";
	cout << "2. Sap xep so luong sach\n";
	cout << "3. Tim kiem sach\n";
	cout << "4. In danh sach\n";
	cout << "5. Thoat\n";
	int choice;
	do {
		cout << "Nhap lua chon cua ban: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			Sach newSach;
			cin >> newSach;
			addNode(head, newSach);
			break;
		}
		case 2: {
			Sapxepsoluongsach(head);
			break;
		}
		case 3: {
			Timkiemsach(head);
			break;
		}
		case 4: {
			Indanhsach(head);
			break;
		}
		case 5: {
			cout << "Ket thuc chuong trinh.\n";
			break;
		}
		default: {
			cout << "Lua chon khong hop le. Vui long nhap lai.\n";
			break;
		}
		}
	} while (choice != 5);
}

int main()
{
	Node* head = NULL;
	menu(head);
	return 0;
}