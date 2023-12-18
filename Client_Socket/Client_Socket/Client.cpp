#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include<iostream>
#include<string>
#include<fstream>
#include<WinSock2.h>
#include <WS2tcpip.h> 
#include <cstring>
#include <vector>
#include<chrono>
#include<thread>
#include"Base64.h"
#include <sstream>
#include<nlohmann/json.hpp>
#include<atomic>
#include<mutex>
#include<condition_variable>
#pragma warning(disable: 4996)
using namespace std;
using json = nlohmann::json;

string client_domain;
string client_name;
string password;
string ip;
int SMTP_Port;
int POP3_Port;
int autoload;

struct to {
    string recv[100] = { "" };
    int n = 0;
};
struct cc {
    string recv[100] = { "" };
    int n = 0;
};
struct bcc {
    string recv[100] = { "" };
    int n = 0;
};

struct file_info {
    string link_file;
    string type;
    string name;
};
struct file {
    file_info file_url[100];
    int n = 0;
};

struct mail {
    int no;
    string to;
    string cc;
    string from;
    string subject;
    string content;
    vector<string> file;
    string buffer;
    bool hasfile=0;
    bool check = 0;
};

struct keyword {
    vector<string> keyfrom;
    vector<string> keysubject;
    vector<string> keycontent;
};

keyword keyproject, keywork, keyimportant, keyspam;

struct Folder {
    int n=0;
    mail list[100] = {};
};

struct list_recv {
    int no;
    int bytes;
};

std::mutex fileMutex;

void Disconnect(SOCKET& socket)
{
    closesocket(socket);
    WSACleanup();
}

//DAY LA SMTP
//DAY LA SMTP
//DAY LA SMTP
//DAY LA SMTP
//DAY LA SMTP
//DAY LA SMTP
//DAY LA SMTP

void erase_space(string& a) {
    for (int i = 0; i < a.length(); i++) {
        if (a[i] == ' ') {
            a.erase(i, 1);
            i--;
        }
    }
}
string name_file(string url) {
    for (int i = url.length() - 1; i >= 0; i--) {
        if (url[i] == '\\') {
            return url.substr(i + 1, url.length() - i - 1);
        }
    }
    return url;
}
string type_file(string url) {
    for (int i = url.length() - 1; i >= 0; i--) {
        if (url[i] == '.') {
            return url.substr(i + 1, url.length() - i - 1);
        }
    }
    return url;
}
bool compare(SOCKET send_mail, char revc[], string com, int len) {
    memset(revc, 0, len);
    int bytes_received = recv(send_mail, revc, len, 0);
    if (bytes_received == SOCKET_ERROR) {
        std::cout << "Loi nhan du lieu." << endl;
        return 0;
    }
    if (strcmp(revc, com.c_str()) != 0) {
        std::cout << "Loi nhan du lieu." << endl;
        return 0;
    }
    return 1;
}
bool send_header_mail(SOCKET send_mail, string content, char text[], string IP, string client_domain, to domain_to, cc domain_cc, bcc domain_bcc) {
    content = "EHLO [";
    content += IP + "]" + "\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    if (!compare(send_mail, text, "250 OK\r\n", 1024)) {
        return 0;
    }
    content = "MAIL FROM:<" + client_domain + ">\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    if (!compare(send_mail, text, "250 sender <" + client_domain + "> OK\r\n", 1024)) {
        return 0;
    }
    for (int i = 0; i < domain_to.n; i++) {
        content = "RCPT TO:<" + domain_to.recv[i] + ">\r\n";
        send(send_mail, content.c_str(), content.length(), 0);
        if (!compare(send_mail, text, "250 recipient <" + domain_to.recv[i] + "> OK\r\n", 1024)) {
            return 0;
        }
    }
    for (int i = 0; i < domain_cc.n; i++) {
        content = "RCPT TO:<" + domain_cc.recv[i] + ">\r\n";
        send(send_mail, content.c_str(), content.length(), 0);
        if (!compare(send_mail, text, "250 recipient <" + domain_cc.recv[i] + "> OK\r\n", 1024)) {
            return 0;
        }
    }
    for (int i = 0; i < domain_bcc.n; i++) {
        content = "RCPT TO:<" + domain_bcc.recv[i] + ">\r\n";
        send(send_mail, content.c_str(), content.length(), 0);
        if (!compare(send_mail, text, "250 recipient <" + domain_bcc.recv[i] + "> OK\r\n", 1024)) {
            return 0;
        }
    }
    content = "DATA\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    if (!compare(send_mail, text, "354 enter mail, end with line containing only \".\"\r\n", 1024)) {
        return 0;
    }
    return 1;
}
bool send_more_person(int port, string IP, string client_domain, to domain_to, cc domain_cc, bcc domain_bcc, string client_name, string subj, string content_mail) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartup failed: " << WSAGetLastError() << endl;
        return 0;
    }
    // Create a socket
    SOCKET send_mail = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (send_mail == INVALID_SOCKET) {
        std::cout << "Socket creation failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }

    // Connect to the server
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(IP.c_str());

    if (connect(send_mail, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cout << "Connection failed: " << WSAGetLastError() << endl;
        closesocket(send_mail);
        WSACleanup();
        return 0;
    }
    char text[1024];
    if (!compare(send_mail, text, "220 Test Mail Server\r\n", 1024)) {
        return 0;
    }
    string content = "";
    if (!send_header_mail(send_mail, content, text, IP, client_domain, domain_to, domain_cc, domain_bcc)) return 0;;
    int size_mail = 0;
    content = "To: ";
    for (int i = 0; i < domain_to.n; i++) {
        content += domain_to.recv[i] + ", ";
    }
    content += "\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    if (domain_cc.n != 0) {
        content = "Cc: ";
        for (int i = 0; i < domain_cc.n; i++) {
            content += domain_cc.recv[i] + ", ";
        }
        content += "\r\n";
        send(send_mail, content.c_str(), content.length(), 0);
        size_mail += content.length();
    }
    content = "From: " + client_name + " <" + client_domain + ">\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    content = "Subject: " + subj + "\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    content = "Content-Type: text/plain; charset=UTF-8; format=flowed\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    content = "Content-Transfer-Encoding: 7bit\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    content = "\n" + content_mail + "\n\n" + "." + "\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    if (!compare(send_mail, text, "250 " + to_string(size_mail) + " bytes accepted\r\n", 1024)) {
        return 0;
    }
    WSACleanup();
    return 1;
}

#pragma stackalloc(30000)
bool send_attach_file(int port, string IP, string client_domain, to domain_to, cc domain_cc, bcc domain_bcc, string client_name, string subj, string content_mail, file attach) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartup failed: " << WSAGetLastError() << endl;
        return 0;
    }
    // Create a socket
    SOCKET send_mail = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (send_mail == INVALID_SOCKET) {
        std::cout << "Socket creation failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }

    // Connect to the server
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(IP.c_str());

    if (connect(send_mail, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cout << "Connection failed: " << WSAGetLastError() << endl;
        closesocket(send_mail);
        WSACleanup();
        return 0;
    }
    char text[1024];
    if (!compare(send_mail, text, "220 Test Mail Server\r\n", 1024)) {
        return 0;
    }
    string content = "";
    if (!send_header_mail(send_mail, content, text, IP, client_domain, domain_to, domain_cc, domain_bcc)) return 0;
    int size_mail = 0;
    content = "Content-Type: multipart/mixed; boundary=\"------------bMjukifiBWdp31K6UwueGgxH\"\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    content = "MIME-Version: 1.0\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    content = "Content-Language: vi-x-KieuCu.[Chuan]\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    content = "To: ";
    for (int i = 0; i < domain_to.n; i++) {
        content += domain_to.recv[i] + ", ";
    }
    content += "\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    if (domain_cc.n != 0) {
        content = "Cc: ";
        for (int i = 0; i < domain_cc.n; i++) {
            content += domain_cc.recv[i] + ", ";
        }
        content += "\r\n";
        send(send_mail, content.c_str(), content.length(), 0);
        size_mail += content.length();
    }
    content = "From: " + client_name + " <" + client_domain + ">\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    content = "Subject: " + subj + "\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    content = "This is a multi-part message in MIME format.\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    content = "\n--------------bMjukifiBWdp31K6UwueGgxH\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    content = "Content-Type: text/plain; charset=UTF-8; format=flowed\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    content = "Content-Transfer-Encoding: 7bit\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    content = "\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    content = content_mail + "\n\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    for (int i = 0; i < attach.n; i++) {
        content = "--------------bMjukifiBWdp31K6UwueGgxH\r\n";
        send(send_mail, content.c_str(), content.length(), 0);
        size_mail += content.length();
        content = "Content-Type: " + attach.file_url[i].type + "; name=\"" + attach.file_url[i].name + "\"\r\n";
        send(send_mail, content.c_str(), content.length(), 0);
        size_mail += content.length();
        content = "Content-Disposition: attachment; filename=\"" + attach.file_url[i].name + "\"\r\n";
        send(send_mail, content.c_str(), content.length(), 0);
        size_mail += content.length();
        content = "Content-Transfer-Encoding: base64\r\n";
        send(send_mail, content.c_str(), content.length(), 0);
        size_mail += content.length();
        content = "\r\n";
        send(send_mail, content.c_str(), content.length(), 0);
        size_mail += content.length();
        ifstream input(attach.file_url[i].link_file, ios::binary);
        std::vector<char> pdf_data((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
        string str(pdf_data.begin(), pdf_data.end());
        content = base64_encode(str);
        int k = content.length() / 500;
        if (k < 1) {
            content += "\r\n";
            send(send_mail, content.c_str(), content.length(), 0);
            size_mail += content.length();
        }
        else {
            string sub_content = "";
            for (int i = 0; i < k; i++) {
                sub_content = content.substr(i * 500, 500);
                sub_content += "\r\n";
                send(send_mail, sub_content.c_str(), sub_content.length(), 0);
                size_mail += sub_content.length();
            }
            sub_content = content.substr(k * 500, content.length() - k * 6500);
            sub_content += "\r\n";
            send(send_mail, sub_content.c_str(), sub_content.length(), 0);
            size_mail += sub_content.length();
        }
    }
    content = "\n--------------bMjukifiBWdp31K6UwueGgxH--\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    content = ".\r\n";
    send(send_mail, content.c_str(), content.length(), 0);
    size_mail += content.length();
    if (!compare(send_mail, text, "250 " + to_string(size_mail) + " bytes accepted\r\n", 1024)) {
        return 0;
    }
    WSACleanup();
    return 1;
}
int valid_file(string url) {
    ifstream input(url, ios::binary);
    if (!input) return -1;
    input.seekg(0, 2);
    unsigned int n_byte = input.tellg();
    if (n_byte > 3145728) {
        return 0;
    }
    return 1;
}
void SMTP_service(int port, string IP, string client_domain, to& domain_to, cc& domain_cc, bcc& domain_bcc, string client_name, string& subj, string& content_mail, file& attach) {
    std::cout << "Day la thong tin soan mail: (neu khong dien vui long an enter de bo qua) \n";
    std::cout << "TO: ";
    string IP_for_to = "";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, IP_for_to);
    std::cout << "CC: ";
    string IP_for_cc = "";
    getline(cin, IP_for_cc);
    std::cout << "BCC: ";
    string IP_for_bcc = "";
    getline(cin, IP_for_bcc);
    std::cout << "Nhap Subject: ";
    getline(cin, subj);
    std::cout << "Nhap Content: ";
    getline(cin, content_mail);
    stringstream to_str(IP_for_to);
    string x = "";
    while (getline(to_str, x, ',')) {
        domain_to.recv[domain_to.n] = x;
        domain_to.n++;
    }
    for (int i = 0; i < domain_to.n; i++) erase_space(domain_to.recv[i]);
    stringstream cc_str(IP_for_cc);
    while (getline(cc_str, x, ',')) {
        domain_cc.recv[domain_cc.n] = x;
        domain_cc.n++;
    }
    for (int i = 0; i < domain_cc.n; i++) erase_space(domain_cc.recv[i]);
    stringstream bcc_str(IP_for_bcc);
    while (getline(bcc_str, x, ',')) {
        domain_bcc.recv[domain_bcc.n] = x;
        domain_bcc.n++;
    }
    for (int i = 0; i < domain_bcc.n; i++) erase_space(domain_bcc.recv[i]);
    int select = 0;
label:
    std::cout << "Ban co muon gui kem file hay khong(chon 1 neu muon, 2 neu khong):  ";
    cin >> select;
    while (select != 1 && select != 2) {
        std::cout << "Khong co tuy chon ban nhap, vui long nhap lai: ";
        cin >> select;
    }
    if (select == 2) {
        if (send_more_person(port, IP, client_domain, domain_to, domain_cc, domain_bcc, client_name, subj, content_mail))
            std::cout << "\nGui mail thanh cong!!!\n";
        else std::cout << "\nGui mail that bai!!!\n";
    }
    else {
        string url = "";
        int n_item = 0;
        std::cout << "\nNhap so luong file ban muon gui(Ban co the nhap 0 de quay lai phan tuy chon gui): ";
        cin >> n_item;
        if (n_item == 0) goto label;
        int i_item = 1;
        do {
            std::cout << "Nhap duong dan so " << i_item << "( luu y dung luong file <=3MB):  ";
            cin >> url;
            erase_space(url);
            int valid = valid_file(url);
            if (valid == 1) {
                attach.file_url[attach.n].link_file = url;
                attach.file_url[attach.n].name = name_file(url);
                attach.file_url[attach.n].type = type_file(url);
                attach.n++;
                n_item--;
                i_item++;
            }
            else {
                int option = 0;
                if (valid == 0)std::cout << "Rat tiec file ban vua nhap vao co dung luong vuot qua 3MB, ban hay nhap tuy chon:\n";
                else std::cout << "Rat tiec khong the tim dc file ban can, ban hay nhap tuy chon:\n";
                std::cout << " 1. Neu ban muon nhap duong dan khac \n 2. Neu ban muon bo qua file nay va giam so luong file muon gui";
                std::cout << "\n Lua chon cua ban: ";
                cin >> option;
                while (option != 1 && option != 2) {
                    std::cout << "Khong co tuy chon ban nhap, vui long nhap lai: ";
                    cin >> option;
                }
                if (option == 1) {
                    std::cout << "Vui long nhap lai: \n";
                }
                else {
                    n_item--;
                }
            }
        } while (n_item);
        if (send_attach_file(port, IP, client_domain, domain_to, domain_cc, domain_bcc, client_name, subj, content_mail, attach))
            std::cout << "\nGui mail thanh cong!!!\n";
        else std::cout << "\n Gui mail that bai!!!\n";
    }
}

//DAY LA POP3
//DAY LA POP3
//DAY LA POP3
//DAY LA POP3
//DAY LA POP3
//DAY LA POP3



SOCKET Connect(string ip,int port) {
    // Khởi tạo Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "Không thể khởi tạo Winsock\n";
        WSACleanup();
        return NULL;
    }
    // Tạo socket
    SOCKET socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_descriptor == INVALID_SOCKET)
    {
        return NULL;
    }
    // Kết nối với máy chủ
    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = inet_addr(ip.c_str());
    if (connect(socket_descriptor, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        cerr << "Failed to connect to the server." << endl;
        closesocket(socket_descriptor);
        WSACleanup();
        return NULL;
    }
    char buffer[1024];
    int bytesReceived = recv(socket_descriptor, buffer, 1024, 0);
    if (bytesReceived == SOCKET_ERROR) {
        cerr << "Error receiving data from the server." << endl;
        closesocket(socket_descriptor);
        WSACleanup();
        return NULL;
    }
    else {
        buffer[bytesReceived] = '\0';
    }
    return socket_descriptor;
}

string CAPA(SOCKET &socket_descriptor) {
    char capaCMD[100] = "CAPA\r\n";
    if (send(socket_descriptor, capaCMD, strlen(capaCMD), 0) == SOCKET_ERROR)
    {
        cerr << "Failed to send cmd." << endl;
        closesocket(socket_descriptor);
        WSACleanup();
        return NULL;
    }
    else
    {
        char buffer[1024];
        int bytesReceived = recv(socket_descriptor, buffer, 1024, 0);
        if (bytesReceived == SOCKET_ERROR) {
            cerr << "Error receiving data from the server." << endl;
            closesocket(socket_descriptor);
            WSACleanup();
            return NULL;
        }
        else {
            buffer[bytesReceived] = '\0';
            return buffer;
        }
    }
}

void USER(SOCKET &socket_descriptor, string email)
{
    char userCMD[100] = "USER ";
    email = email + "\r\n";
    strcat(userCMD, email.c_str());
    if (send(socket_descriptor, userCMD, strlen(userCMD), 0) == SOCKET_ERROR)
    {
        cerr << "Failed to send cmd." << endl;
        closesocket(socket_descriptor);
        WSACleanup();
        return;
    }
    else {
        char buffer[1024];
        int bytesReceived = recv(socket_descriptor, buffer, 1024, 0);
        if (bytesReceived == SOCKET_ERROR) {
            cerr << "Error receiving data from the server." << endl;
            closesocket(socket_descriptor);
            WSACleanup();
            return;
        }
        else {
            buffer[bytesReceived] = '\0';
        }
    }
}

void PASS(SOCKET& socket_descriptor, string pass)
{
    char passCMD[100] = "PASS ";
    pass = pass + "\r\n";
    strcat(passCMD, pass.c_str());
    if (send(socket_descriptor, passCMD, strlen(passCMD), 0) == SOCKET_ERROR)
    {
        cerr << "Failed to send cmd." << endl;
        closesocket(socket_descriptor);
        WSACleanup();
        return;
    }
    else {
        char buffer[1024];
        int bytesReceived = recv(socket_descriptor, buffer, 1024, 0);
        if (bytesReceived == SOCKET_ERROR) {
            cerr << "Error receiving data from the server." << endl;
            closesocket(socket_descriptor);
            WSACleanup();
            return;
        }
        else {
            buffer[bytesReceived] = '\0';
        }
    }
}

string STAT(SOCKET& socket_descriptor)
{
    char statCMD[100] = "STAT\r\n";
    if (send(socket_descriptor, statCMD, strlen(statCMD), 0) == SOCKET_ERROR)
    {
        cerr << "Failed to send cmd." << endl;
        closesocket(socket_descriptor);
        WSACleanup();
        return NULL;
    }
    else {
        char buffer[1024];
        int bytesReceived = recv(socket_descriptor, buffer, 1024, 0);
        if (bytesReceived == SOCKET_ERROR) {
            cerr << "Error receiving data from the server." << endl;
            closesocket(socket_descriptor);
            WSACleanup();
            return NULL;
        }
        else {
            buffer[bytesReceived] = '\0';
            return buffer;
        }
    }
}

string LIST(SOCKET& socket_descriptor, vector<list_recv>& list)
{
    char listCMD[100] = "LIST\r\n";
    if (send(socket_descriptor, listCMD, strlen(listCMD), 0) == SOCKET_ERROR)
    {
        cerr << "Failed to send cmd." << endl;
        closesocket(socket_descriptor);
        WSACleanup();
        return NULL;
    }
    else {
        char buffer[1024];
        int bytesReceived = recv(socket_descriptor, buffer, 1024, 0);
        if (bytesReceived == SOCKET_ERROR) {
            cerr << "Error receiving data from the server." << endl;
            closesocket(socket_descriptor);
            WSACleanup();
            return NULL;
        }
        else {
            buffer[bytesReceived] = '\0';
            string temp = buffer;
            temp = temp.substr(5);
            int i = 0;
            for (int i = 0; i < temp.length() && temp[i] != '.'; )
            {
                size_t end_number_pos = temp.find(' ', i);
                size_t end_line = temp.find('\r', i);
                if (end_number_pos == string::npos || end_line == string::npos)
                {
                    continue;
                }
                int number = stoi(temp.substr(i, end_number_pos - i));
                int bytes = stoi(temp.substr(end_number_pos + 1, end_line - end_number_pos - 1));
                list_recv t{ number,bytes };
                list.push_back(t);
                i = end_line + 2;
            }
            return buffer;
        }
    }
}

string UIDL(SOCKET& socket_descriptor)
{
    char uidlCMD[100] = "UIDL\r\n";
    if (send(socket_descriptor, uidlCMD, strlen(uidlCMD), 0) == SOCKET_ERROR)
    {
        cerr << "Failed to send cmd." << endl;
        closesocket(socket_descriptor);
        WSACleanup();
        return NULL;
    }
    else {
        char buffer[1024];
        int bytesReceived = recv(socket_descriptor, buffer, 1024, 0);
        if (bytesReceived == SOCKET_ERROR) {
            cerr << "Error receiving data from the server." << endl;
            closesocket(socket_descriptor);
            WSACleanup();
            return NULL;
        }
        else {
            buffer[bytesReceived] = '\0';
            return buffer;
        }
    }
}

string RETR(SOCKET& socket_descriptor, int number,int bytes)
{
    char retrCMD[100] = "RETR ";
    string num = to_string(number) + "\r\n";
    strcat(retrCMD, num.c_str());
    if (send(socket_descriptor, retrCMD, strlen(retrCMD), 0) == SOCKET_ERROR)
    {
        cerr << "Failed to send cmd." << endl;
        closesocket(socket_descriptor);
        WSACleanup();
        return "";
    }
    else {
        char* buffer = new char[100000];
        int bytesReceived = 1;
        int total = 0;
        string data;
        while( total< bytes + 9 + to_string(bytes).length())
        {
            bytesReceived = recv(socket_descriptor, buffer, 100000, 0);
            if (bytesReceived == SOCKET_ERROR) {
                cerr << "Error receiving data from the server." << endl;
                closesocket(socket_descriptor);
                WSACleanup();
                return "";
            }
            total += bytesReceived;
            data.append(buffer, bytesReceived);
        }
        //bytesReceived = recv(socket_descriptor, buffer, 100000, 0);
        /*cout << bytesReceived<<endl;*/
        delete[]buffer;
        return data;
    }
}

void QUIT(SOCKET& socket_descriptor)
{
    char quitCMD[100] = "QUIT\r\n";
    if (send(socket_descriptor, quitCMD, strlen(quitCMD), 0) == SOCKET_ERROR)
    {
        cerr << "Failed to send cmd." << endl;
        closesocket(socket_descriptor);
        WSACleanup();
        return;
    }
    else {
        char buffer[1024];
        int bytesReceived = recv(socket_descriptor, buffer, 1024, 0);
        if (bytesReceived == SOCKET_ERROR) {
            cerr << "Error receiving data from the server." << endl;
            closesocket(socket_descriptor);
            WSACleanup();
            return;
        }
        else {
            buffer[bytesReceived] = '\0';
        }
    }
    Disconnect(socket_descriptor);
}

void Login(SOCKET &in,string email, string pass)
{
    USER(in, email);
    PASS(in, pass);
}

// Function to decode base64 encoded image data
vector<uint8_t> decodeBase64(const string& base64String) {
    static const string base64Chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    vector<uint8_t> decodedData;

    int val = 0, valb = -8;
    for (char c : base64String) {
        if (c == '=') {
            break;
        }
        if (base64Chars.find(c) == string::npos) {
            continue;
        }

        val = (val << 6) | (base64Chars.find(c) & 0x3F);
        valb += 6;

        if (valb >= 0) {
            decodedData.push_back((val >> valb) & 0xFF);
            valb -= 8;
        }
    }

    return decodedData;
}

string getFilenameFromContentDisposition(const string& contentDisposition) {
    size_t filenamePos = contentDisposition.find("filename=\"");
    if (filenamePos != string::npos) {
        filenamePos += sizeof("filename=\"") - 1;  // Di chuyển vị trí vượt qua chuỗi tìm kiếm
        size_t filenameEndPos = contentDisposition.find("\"", filenamePos);
        if (filenameEndPos != string::npos) {
            return contentDisposition.substr(filenamePos, filenameEndPos - filenamePos);
        }
    }
    return "";
}

string getBoundaryFromContentType(const string& contentType) {
    size_t boundaryPos = contentType.find("boundary=\"");
    if (boundaryPos != string::npos) {
        boundaryPos += sizeof("boundary=\"") - 1;

        // Find the end of the boundary (until the next semicolon or end of the string)
        size_t boundaryEndPos = contentType.find("\"", boundaryPos);
        if (boundaryEndPos == string::npos) {
            // Return the boundary without surrounding double quotes
            return contentType.substr(boundaryPos);
        }
        else {
            // Return the boundary without surrounding double quotes
            return contentType.substr(boundaryPos, boundaryEndPos - boundaryPos);
        }
    }

    // Return an empty string if boundary is not found
    return "";
}


void DownloadFiles(const string& email) {
    string mimeMessage = email;

    // Set the boundary string (you need to set it based on your MIME structure)
    string boundary = getBoundaryFromContentType(email);

    // Find the first occurrence of the boundary
    size_t startPos = mimeMessage.find("filename=\"");
    size_t boundaryPos = mimeMessage.find(boundary, startPos);

    // Loop through each part in the MIME message
    while (boundaryPos != string::npos) {
        // Find the filename
        size_t filenamePos = mimeMessage.find("filename=\"", startPos);
        if (filenamePos != string::npos) {
            string FileName = getFilenameFromContentDisposition(email.c_str() + filenamePos);
            /*std::cout << "Found file: " << FileName << endl;*/

            // Find the beginning of the base64 data
            size_t contentTransferEncodingPos = mimeMessage.find("Content-Transfer-Encoding: base64", startPos);
            size_t base64DataPos = mimeMessage.find("\n", contentTransferEncodingPos);

            if (contentTransferEncodingPos != string::npos && base64DataPos != string::npos) {
                base64DataPos += 2; // Move to the next line

                // Extract base64 data
                string base64Data = mimeMessage.substr(base64DataPos, boundaryPos - base64DataPos - 2); // Exclude CRLF before boundary

                // Decode base64 data
                vector<uint8_t> Data = decodeBase64(base64Data);

                // Save the File to a file or do any other processing
                ofstream File(FileName, ios::binary);
                if (File.is_open()) {
                    File.write(reinterpret_cast<const char*>(Data.data()), Data.size());
                    File.close();
                    std::cout << "File saved successfully." << endl;
                }
                else {
                    cerr << "Error: Unable to open file for writing." << endl;
                }
            }
            else {
                cerr << "Error: Content-Transfer-Encoding or base64 data not found." << endl;
            }
        }
        else
        {
            cerr << "Error: File name not found." << endl;
        }

        // Move to the next part
        startPos = boundaryPos + boundary.length();
        boundaryPos = mimeMessage.find(boundary, startPos + 1);
    }
}

string cut_mail_file(const string& mail) {
    string NameFile;
    string mimeMessage = mail;

    // Set the boundary string (you need to set it based on your MIME structure)
    string boundary = getBoundaryFromContentType(mail);

    // Find the first occurrence of the boundary
    size_t startPos = mimeMessage.find("filename=\"");
    size_t boundaryPos = mimeMessage.find(boundary, startPos);

    // Loop through each part in the MIME message
    while (boundaryPos != string::npos) {
        // Find the filename
        size_t filenamePos = mimeMessage.find("filename=\"", startPos);
        if (filenamePos != string::npos) {
            string FileName = getFilenameFromContentDisposition(mail.c_str() + filenamePos);
            NameFile += FileName;
            NameFile += "\n";
        }
        // Move to the next part
        startPos = boundaryPos + boundary.length();
        boundaryPos = mimeMessage.find(boundary, startPos + 1);
    }

    return NameFile;
}

string Upper(string str)
{
    string temp = str;
    for (int i = 0; i < temp.length(); i++)
    {
        if (temp[i] >= 'a' && temp[i] <= 'z')
        {
            temp[i] -= 32;
        }
    }
    return temp;
}

int Hasmail(SOCKET& in,string stat)
{
    int n = stat.length();
    int i=0, j=0;
    for (i = 0; i <= n && stat[i] != ' '; i++);
    for (j = i + 1; j <= n && stat[j] != ' '; j++);
    int TokLen = j-i-1;
    int number = stoi(stat.substr(i+1, TokLen));
    if (TokLen <= 0)
    {
        return 0;
    }
    else {
        return number;
    }
}

string cut_mail_to(string mail) // cần cải thiện
{
    size_t to_pos = mail.find("To:");
    if (to_pos == string::npos)
    {
        return"<empty>";
    }
    int to_i = to_pos;
    while (mail[to_i] != '\r')
    {
        to_i++;
    }
    string mail_list_to = mail.substr(to_pos+4, to_i - to_pos-4);
    if (mail_list_to.length() == 0)
    {
        return "<empty>";
    }
    while (mail_list_to[mail_list_to.length() - 1] == ',' || mail_list_to[mail_list_to.length() - 1] == ' ')
    {
        mail_list_to.pop_back();
    }
    return mail_list_to;

}

string cut_mail_cc(string mail) 
{
    size_t cc_pos = mail.find("Cc:");
    if (cc_pos == string::npos)
    {
        return"<empty>";
    }
    int cc_i = cc_pos;
    while (mail[cc_i] != '\r')
    {
        cc_i++;
    }
    string mail_list_cc = mail.substr(cc_pos+4, cc_i - cc_pos-4);
    if (mail_list_cc.length() == 0)
    {
        return "<empty>";
    }
    while (mail_list_cc[mail_list_cc.length() - 1] == ',' || mail_list_cc[mail_list_cc.length() - 1] == ' ')
    {
        mail_list_cc.pop_back();
    }
    return mail_list_cc;
}

string cut_mail_from(string mail) 
{
    size_t from_pos = mail.find("From:");
    if (from_pos == string::npos)
    {
        return"";
    }
    int from_i = from_pos ;
    while (mail[from_i] != '\r')
    {
        from_i++;
    }
    string from = mail.substr(from_pos + 6, from_i - from_pos - 6);
    return from;
}

string cut_mail_subject(string mail)
{
    size_t sub_pos = mail.find("Subject:");
    if (sub_pos == string::npos)
    {
        return"<empty>";
    }
    int sub_i = sub_pos;
    while (mail[sub_i] != '\r')
    {
        sub_i++;
    }
    string subject = mail.substr(sub_pos + 9, sub_i - sub_pos - 9);
    if (subject.length() == 0)
    {
        return "<empty>";
    }
    return subject;
}

string cut_mail_content(string mail)
{
    size_t bit_pos = mail.find("bit\r\n\r\n");
    if (bit_pos == string::npos)
    {
        return "";
    }
    size_t boundary_pos = mail.find("boundary=");
    string boundary;
    bool hasfile=1 ;
    if (boundary_pos == string::npos)
    {
        hasfile = 0;
    }
    else {
        int end_boundary_pos;
        for (end_boundary_pos = boundary_pos + 10; mail[end_boundary_pos] != '"'; end_boundary_pos++);
        boundary = "--" + mail.substr(boundary_pos + 10, end_boundary_pos - boundary_pos-10);
    }
    size_t content_pos = bit_pos + 7;
    if (hasfile)
    {
        size_t end_content_pos = mail.find(boundary,content_pos);
        end_content_pos = end_content_pos - 4;
        if (end_content_pos <= content_pos)
        {
            return "<empty>";
        }
        string content = mail.substr(content_pos, end_content_pos - content_pos);
        return content;
    }
    else {
        size_t end_content_pos = mail.find("\r\n\r\n.");
        string content = mail.substr(content_pos, end_content_pos - content_pos);
        return content;
    }
}

void cut_file(string mail,vector<string> &filename)
{
    string temp = cut_mail_file(mail);
    for (int i = 0; i <= temp.length(); i++)
    {
        size_t file_pos = temp.find('\n', i);
        if (file_pos == string::npos)
        {
            return ;
        }
        string file_temp = temp.substr(i, file_pos - i);
        filename.push_back(file_temp);
        i = file_pos;
    }
}

string Show_mail(mail email)
{
    string show="";
    if (email.check == 0)
    {
        show = show+ "(chua doc)";
    }
    show = show + "<" + email.from + ">" + "<" + email.subject + ">\n";
    return show;
}

void Show_mail_box(Folder& box)
{
    if (box.n == 0)
    {
        std::cout << "<empty>\r\n";
        return;
    }
    for (int i = 1; i <= box.n; i++)
    {
        std::cout<<to_string(i)+ ". "+Show_mail(box.list[i]);
    }
}


void Save_mail_box(ofstream& output, string filename, Folder& box)
{
    std::lock_guard<std::mutex> lock(fileMutex);
    output.open(filename);
    if (!output.is_open())
    {
        return;
    }
    output << box.n << endl;
    for (int i = 1; i <= box.n; i++)
    {
        output << box.list[i].no << " " << box.list[i].to << "\t" << box.list[i].cc << "\t" << box.list[i].from << "\t" << box.list[i].subject << "\t" << box.list[i].content << "\t" << box.list[i].buffer << "\t";
        output << box.list[i].file.size() << " ";
        for (int j = 0; j < box.list[i].file.size(); j++)
        {
            output << box.list[i].file[j] << "\t";
        }
        output << box.list[i].check << " " << box.list[i].hasfile << endl;
    }
    output.close();
}

void Load_mail_file(ifstream& input, string filename, Folder& box)
{
    std::lock_guard<std::mutex> lock(fileMutex);
    input.open(filename);
    if (!input.is_open())
    {
        return;
    }
    int nfile = 0;
    string temp;
    input >> box.n;
    input.ignore();
    for (int i = 1; i <= box.n; i++)
    {
        input >> box.list[i].no;
        input.ignore();
        getline(input, box.list[i].to, '\t');
        getline(input, box.list[i].cc, '\t');
        getline(input, box.list[i].from, '\t');
        getline(input, box.list[i].subject, '\t');
        getline(input, box.list[i].content, '\t');
        getline(input, box.list[i].buffer, '\t');
        input >> nfile;
        input.ignore();
        for (int j = 0; j < nfile; j++)
        {
            getline(input, temp, '\t');
            box.list[i].file.push_back(temp);
        }
        input >> box.list[i].check;
        input >> box.list[i].hasfile;
    }
    input.close();
}

void mail_read(mail &email) {
    string mail_list_to = email.to;
    string mail_list_cc = email.cc;
    string mail_list_from = email.from;
    string subject = email.subject;
    string content = email.content;
    string mail_read = "To: " + mail_list_to + "\r\n" + "Cc: " + mail_list_cc + "\r\n" + "From: " + mail_list_from + "\r\n" + "Subject: " + subject + "\r\n\r\n" + content + "\r\n";
    std::cout << mail_read<<endl;
    if (email.hasfile == 1)
    {
        for (int i = 0; i < email.file.size(); i++)
        {
            std::cout << "File dinh kem: " << email.file[i]<<endl;
        }
    }
    email.check = 1;
}

void read_mail(Folder& box, int number)
{
    mail_read(box.list[number]);
}

void delete_mail(Folder& box, int pos)
{
    if (pos >= 0 && pos <= box.n)
    {
        for (int i = pos; i < box.n; i++)
        {
            box.list[i] = box.list[i + 1];
        }
    }
    box.n--;
}

void from_filter(Folder& box,Folder&sub_box,string mail_from)
{
    int n = box.n;
    int n_sub = sub_box.n;
    string temp_from = Upper(mail_from);
    for (int i = 1; i <= n; i++)
    {
        string temp = Upper(box.list[i].from); 
        size_t temp_pos = temp.find(temp_from);
        if (temp_pos == string::npos)
        {
            continue;
        }
        else {
            sub_box.list[++sub_box.n] = box.list[i];
            delete_mail(box, i);
            n=box.n;
        }
    }
}

void sub_filter(Folder& box, Folder& sub_box,string mail_subject)
{
    int n = box.n;
    int n_sub = sub_box.n;
    string temp_sub = Upper(mail_subject);
    for (int i = 1; i <= n; i++)
    {
        string temp = Upper(box.list[i].subject);
        size_t temp_pos =temp.find(temp_sub);
        if (temp_pos == string::npos)
        {
            continue;
        }
        else {
            sub_box.list[++sub_box.n] = box.list[i];
            delete_mail(box, i);
            n=box.n;
        }
    }
}

void filter_content(Folder& box, Folder&sub_box,string mail_content)
{
    int n = box.n;
    int n_sub = sub_box.n;
    string temp_cont = Upper(mail_content);
    for (int i = 1; i <= n; i++)
    {
        string temp = Upper(box.list[i].content);
        size_t temp_pos = temp.find(temp_cont);
        if (temp_pos == string::npos)
        {
            continue;
        }
        else {
            sub_box.list[++sub_box.n] = box.list[i];
            delete_mail(box, i);
            n=box.n;
        }
    }
}


void filter_mail(Folder& inbox, Folder& sub_box, keyword key)
{
    for (int i = 0; i < key.keyfrom.size(); i++)
    {
        from_filter(inbox, sub_box, key.keyfrom[i]);
    }

    for (int i = 0; i < key.keysubject.size(); i++)
    {
        sub_filter(inbox, sub_box, key.keysubject[i]);
    }

    for (int i = 0; i < key.keycontent.size(); i++)
    {
        filter_content(inbox, sub_box, key.keycontent[i]);
    }
}


int unread_mail(Folder box)
{
    int count = 0;
    for (int i = 0; i < box.n; i++)
    {
        if (box.list[i].check == 0)
        {
            count++;
        }
    }
    return count;
}

int number_mail(Folder box)
{
    return box.n;
}


void Load_mail_inbox(SOCKET& in, Folder& inbox,Folder&project,Folder& important,Folder&work,Folder&spam,string inboxname,string projectname,string importantname,string workname,string spamname) 
{
    vector<list_recv> list_recv;
    string stat = STAT(in);
    string list = LIST(in,list_recv);
    string uidl = UIDL(in);
    int mail_num_new = Hasmail(in, stat);
    if (mail_num_new == 0) { return; }
    ifstream inboxfile, projectfile, workfile, importantfile, spamfile;
    Load_mail_file(inboxfile, inboxname, inbox);
    Load_mail_file(projectfile, projectname, project);
    Load_mail_file(importantfile, importantname, important);
    Load_mail_file(workfile, workname, work);
    Load_mail_file(spamfile, spamname, spam);
    int mail_num_old = inbox.n + project.n + important.n + work.n + spam.n;
    if (mail_num_new > mail_num_old) {
        for (int i = mail_num_old+1; i <= mail_num_new; i++)
        {
            string mail = RETR(in, list_recv[i-1].no, list_recv[i-1].bytes);
 /*           cout << mail.length();*/
            inbox.n++;
            inbox.list[inbox.n].no = i;
            inbox.list[inbox.n].to = cut_mail_to(mail);
            inbox.list[inbox.n].cc = cut_mail_cc(mail);
            inbox.list[inbox.n].from = cut_mail_from(mail);
            inbox.list[inbox.n].subject = cut_mail_subject(mail);
            inbox.list[inbox.n].content = cut_mail_content(mail);
            inbox.list[inbox.n].buffer = mail;
            cut_file(mail, inbox.list[inbox.n].file);
            if (inbox.list[inbox.n].file.size() != 0)
            {
                inbox.list[inbox.n].hasfile = 1;
            }
        }
    }
}

void Save_mail_file(Folder& inbox, Folder& project, Folder& important, Folder& work, Folder& spam, string inboxname, string projectname, string importantname, string workname, string spamname)
{
    ofstream inboxfile, projectfile, workfile, importantfile, spamfile;
    Save_mail_box(inboxfile, inboxname, inbox);
    Save_mail_box(projectfile, projectname, project);
    Save_mail_box(importantfile, importantname, important);
    Save_mail_box(workfile, workname, work);
    Save_mail_box(spamfile, spamname, spam);
}

void POP3Menu(int POP3_Port,string IP,string account,string password)
{
    cout << "Loading.........." << endl;
    ofstream output;
    ifstream input;
    Folder inbox;
    Folder project;
    Folder important;
    Folder work;
    Folder spam;
    SOCKET in = Connect(IP, POP3_Port);
    if (in == NULL) { return; }
    string capa = CAPA(in);
    Login(in, account, password);
    Load_mail_inbox(in, inbox, project, important, work, spam, "inbox.txt", "project.txt", "important.txt", "work.txt", "spam.txt");
    filter_mail(inbox, important, keyimportant);
    filter_mail(inbox, project, keyproject);
    filter_mail(inbox, work, keywork);
    filter_mail(inbox, spam, keyspam);
    int select_1=-1;
    do {
        system("cls");
        std::cout << "Day la danh sach cac thu muc mail cua ban: " << endl;
        std::cout << "1. Inbox   2. Project    3. Important   4. Work    5. Spam " << endl;
        std::cout << "Chon thu muc(chon 0 de quay lai man hinh chinh): ";
        cin >> select_1;
        if (select_1 == 0)
        {
            break;
        }
        else if (select_1 == 1) {
            do {
                int select_2=-1;
                std::cout << "Day la danh sach cac mail trong thu muc Inbox:" << endl;
                Show_mail_box(inbox);
                std::cout << "Chon mail ban muon doc(chon 0 neu ban muon quay lai danh sach thu muc): ";
                cin >> select_2;
                if (select_2 <= 0)
                {
                    break;
                }
                else if (select_2 > inbox.n)
                {
                    std::cout << "Khong ton tai mail!" << endl;
                }
                else
                {
                    std::cout << endl << endl;
                    read_mail(inbox, select_2);
                    if (inbox.list[select_2].hasfile == 1)
                    {
                        std::cout << "Ban co muon tai cac file khong?(1:Co, 2:Khong) " << endl;
                        int choose;
                        cin >> choose;
                        if (choose == 1)
                        {
                            DownloadFiles(inbox.list[select_2].buffer);
                        }
                    }
                }
            } while (true);

        }
        else if (select_1 == 2) {
            do {
                int select_2 = -1;
                std::cout << "Day la danh sach cac mail trong thu muc Project:" << endl;
                Show_mail_box(project);
                std::cout << "Chon mail ban muon doc(chon 0 neu ban muon quay lai danh sach thu muc): ";
                cin >> select_2;
                if (select_2 <= 0)
                {
                    break;
                }
                else if (select_2 > project.n)
                {
                    std::cout << "Khong ton tai mail!" << endl;
                }
                else
                {
                    std::cout << endl << endl;
                    read_mail(project, select_2);
                    if (project.list[select_2].hasfile == 1)
                    {
                        std::cout << "Ban co muon tai cac file khong?(1:Co, 2:Khong) " << endl;
                        int choose;
                        cin >> choose;
                        if (choose == 1)
                        {
                            DownloadFiles(project.list[select_2].buffer);
                        }
                    }
                }
            } while (true);

        }
        else if (select_1 == 3) {
            do {
                int select_2 = -1;
                std::cout << "Day la danh sach cac mail trong thu muc Important:" << endl;
                Show_mail_box(important);
                std::cout << "Chon mail ban muon doc(chon 0 neu ban muon quay lai danh sach thu muc): ";
                cin >> select_2;
                if (select_2 <= 0)
                {
                    break;
                }
                else if (select_2 > important.n)
                {
                    std::cout << "Khong ton tai mail!" << endl;
                }
                else
                {
                    std::cout << endl << endl;
                    read_mail(important, select_2);
                    if (important.list[select_2].hasfile == 1)
                    {
                        std::cout << "Ban co muon tai cac file khong?(1:Co, 2:Khong) " << endl;
                        int choose;
                        cin >> choose;
                        if (choose == 1)
                        {
                            DownloadFiles(important.list[select_2].buffer);
                        }
                    }
                }
            } while (true);

        }
        else if (select_1 == 4) {
            do {
                int select_2 = -1;
                std::cout << "Day la danh sach cac mail trong thu muc Work:" << endl;
                Show_mail_box(work);
                std::cout << "Chon mail ban muon doc(chon 0 neu ban muon quay lai danh sach thu muc): ";
                cin >> select_2;
                if (select_2 <= 0)
                {
                    break;
                }
                else if (select_2 > work.n)
                {
                    std::cout << "Khong ton tai mail!" << endl;
                }
                else
                {
                    std::cout << endl << endl;
                    read_mail(work, select_2);
                    if (work.list[select_2].hasfile == 1)
                    {
                        std::cout << "Ban co muon tai cac file khong?(1:Co, 2:Khong) " << endl;
                        int choose;
                        cin >> choose;
                        if (choose == 1)
                        {
                            DownloadFiles(work.list[select_2].buffer);
                        }
                    }
                }
            } while (true);

        }
        else if (select_1 == 5) {
            do {
                int select_2 = -1;
                std::cout << "Day la danh sach cac mail trong thu muc Spam:" << endl;
                Show_mail_box(spam);
                std::cout << "Chon mail ban muon doc(chon 0 neu ban muon quay lai danh sach thu muc): ";
                cin >> select_2;
                if (select_2 <= 0)
                {
                    break;
                }
                else if (select_2 > spam.n)
                {
                    std::cout << "Khong ton tai mail!" << endl;
                }
                else
                {
                    std::cout << endl << endl;
                    read_mail(spam, select_2);
                    if (spam.list[select_2].hasfile == 1)
                    {
                        std::cout << "Ban co muon tai cac file khong?(1:Co, 2:Khong) " << endl;
                        int choose;
                        cin >> choose;
                        if (choose == 1)
                        {
                            DownloadFiles(spam.list[select_2].buffer);
                        }
                    }
                }
            } while (true);

        }
        else {
        std::cout << "Khong ton tai thu muc!" << endl << endl;
        chrono::seconds duration(2);
        this_thread::sleep_for(duration);
        }
        system("cls");
    } while (true);
    Save_mail_file(inbox, project, important, work, spam, "inbox.txt", "project.txt", "important.txt", "work.txt", "spam.txt");
    QUIT(in);
}

void POP3_Non_Menu(int POP3_Port, string IP, string account, string password,int autoload,mutex &mutex_,condition_variable &cv,bool&p)
{
    while (true)
    {
        
        //this_thread::sleep_for(chrono::seconds(autoload));
        std::unique_lock<std::mutex> lock(mutex_);
        if (!cv.wait_for(lock, chrono::seconds(autoload), [&p] { return p == false; })) {
            ofstream output;
            ifstream input;
            Folder inbox;
            Folder project;
            Folder important;
            Folder work;
            Folder spam;
            SOCKET in = Connect(IP, POP3_Port);
            if (in == NULL) { return; }
            string capa = CAPA(in);
            Login(in, account, password);
            Load_mail_inbox(in, inbox, project, important, work, spam, "inbox.txt", "project.txt", "important.txt", "work.txt", "spam.txt");
            filter_mail(inbox, important, keyimportant);
            filter_mail(inbox, project, keyproject);
            filter_mail(inbox, work, keywork);
            filter_mail(inbox, spam, keyspam);
            Save_mail_file(inbox, project, important, work, spam, "inbox.txt", "project.txt", "important.txt", "work.txt", "spam.txt");
            QUIT(in);

        }
        else {
            break;
        }
    }
}

void POP3_Non_Thread(int POP3_Port, string IP, string account, string password, int autoload)
{
        ofstream output;
        ifstream input;
        Folder inbox;
        Folder project;
        Folder important;
        Folder work;
        Folder spam;
        SOCKET in = Connect(IP, POP3_Port);
        if (in == NULL) { return; }
        string capa = CAPA(in);
        Login(in, account, password);
        Load_mail_inbox(in, inbox, project, important, work, spam, "inbox.txt", "project.txt", "important.txt", "work.txt", "spam.txt");
        filter_mail(inbox, important, keyimportant);
        filter_mail(inbox, project, keyproject);
        filter_mail(inbox, work, keywork);
        filter_mail(inbox, spam, keyspam);
        Save_mail_file(inbox, project, important, work, spam, "inbox.txt", "project.txt", "important.txt", "work.txt", "spam.txt");
        QUIT(in);
        //this_thread::sleep_for(chrono::seconds(autoload));
}


//Menu
//Menu
//Menu
//Menu

void ClientMenu(int SMTP_Port,int POP3_Port,string IP,string client_domain,string client_name)
{
    int select_0 = -1;
    do {
        system("cls");
        std::cout << "Ban muon lam gi: " << endl;
        std::cout << "0. Thoat chuong trinh. " << endl;
        std::cout << "1. Gui mail. " << endl;
        std::cout << "2. Xem mail trong mailbox." << endl;
        std::cout << "Ban hay chon thao tac: ";
        cin >> select_0;
        if (select_0 == 0)
        {
            break;
        }
        else if (select_0 == 1)
        {
            system("cls");
            to domain_to;
            cc domain_cc;
            bcc domain_bcc;
            string content_mail = "", subj = "";
            file attach;
            SMTP_service(SMTP_Port, IP, client_domain, domain_to, domain_cc, domain_bcc, client_name, subj, content_mail, attach);
            chrono::seconds duration(2);
            this_thread::sleep_for(duration);
        }
        else if (select_0 == 2)
        {
            system("cls");
            POP3Menu(POP3_Port, IP, client_domain, password);
        }
        else {
            std::cout << "Loi thao tac!" << endl;
            chrono::seconds duration(2);
            this_thread::sleep_for(duration);
        }
    } while (select_0 != 0);
    std::cout << "Cam on da su dung phan mem cua chung toi!" << endl;
}

//Doc file config
//Doc file config
//Doc file config
//Doc file config

void read_general(string& username, string& account, string& password, string& ip, int& smtp_port, int& pop3_port, int& autoload)
{
    fstream input;
    input.open("general.json");
    string file;
    getline(input, file, char(-1));
    json jsonData = json::parse(file);
    password = jsonData["password"];
    ip = jsonData["mailserver"];
    smtp_port = jsonData["SMTP"];
    pop3_port = jsonData["POP3"];
    autoload = jsonData["autoload"];
    string temp = jsonData["username"];
    size_t mail_pos = temp.find('<');
    if (mail_pos == string::npos)
    {
        username = "";
    }
    username = temp.substr(0, mail_pos - 1);
    size_t end_mail_pos = temp.find('>');
    account = temp.substr(mail_pos + 1, end_mail_pos - mail_pos - 1);
    input.close();
}

void read_filter(keyword& project, keyword& work, keyword& important, keyword& spam)
{
    ifstream input;
    input.open("filter.json");
    string file;
    getline(input, file, char(-1));
    json jsonData = json::parse(file);
    json projectData = jsonData["project"];
    json workData = jsonData["work"];
    json importantData = jsonData["important"];
    json spamData = jsonData["spam"];
    //lay tu khoa cho project;
    project.keyfrom = projectData["from"];
    project.keysubject = projectData["subject"];
    project.keycontent = projectData["content"];

    //lay tu khoa cho work;

    work.keyfrom = workData["from"];
    work.keysubject = workData["subject"];
    work.keycontent = workData["content"];

    //lay tu khoa cho important;

    important.keyfrom = importantData["from"];
    important.keysubject = importantData["subject"];
    important.keycontent = importantData["content"];

    //lay tu khoa cho spam;

    spam.keyfrom = spamData["from"];
    spam.keysubject = spamData["subject"];
    spam.keycontent = spamData["content"];

}


int main()
{
    bool p =true;
    mutex mutex_;
    condition_variable cv;
    read_general(client_name, client_domain, password, ip, SMTP_Port, POP3_Port, autoload);
    read_filter(keyproject, keywork, keyimportant, keyspam);
    POP3_Non_Thread(POP3_Port,ip, client_domain, password, autoload);
    thread Autoload(POP3_Non_Menu, POP3_Port, ip, client_domain, password, autoload,ref(mutex_),ref(cv), ref(p));
    ClientMenu(SMTP_Port, POP3_Port, ip, client_domain, client_name);
    {
        std::lock_guard<std::mutex> lock(mutex_);
        p = false;
    }
    cv.notify_one();
    Autoload.join();
    return 0;
}