#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#include "opencv2/imgcodecs/legacy/constants_c.h"
#include<winsock2.h>
#include<iostream>
//#include<opencv2/opencv.hpp>
#include<vector>
#include<fstream>
#include<sstream>
#pragma comment(lib, "ws2_32.lib")

using namespace std;


int main()
{
	char tem[1024] = { 0 };
	int l;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	string s;
	stringstream ss;

	SOCKET skt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in target;
	target.sin_family = AF_INET;
	target.sin_port = htons(8888);
	target.sin_addr.S_un.S_addr = inet_addr("192.168.0.107");
	if (!connect(skt, (sockaddr*)&target, sizeof(target))) cout << "connection success!" << endl;
	
	char buf[4096] = { 0 };
	//ifstream file("C:\\Users\\tcdyu\\Desktop\\1.txt", ios::binary);
	FILE* file;
	int filelen = 0;
	fopen_s(&file, "C:\\Users\\tcdyu\\Desktop\\opencv_contrib-4.5.1.tar.gz", "rb");
	fseek(file, 0, SEEK_END);
	filelen = ftell(file);
	ss << filelen; ss >> tem;
	for (l = 0; l < 1024; l++) {
		if (tem[l] == '\0') break;
	}
	send(skt, tem, l, 0);

	fseek(file, -filelen, SEEK_END);
	cout << filelen << endl;
	int n = filelen / 4096, r = filelen - n*4096;

	for (int i = 0; i < n; i++) {
		fread(buf, 4096, 1, file);
		send(skt, buf, 4096, 0);
		memset(buf, 0, 4096);
	}
	fread(buf, r, 1, file);
	send(skt, buf, r, 0);

	fclose(file);

	system("pause");
	return 0;
	
}