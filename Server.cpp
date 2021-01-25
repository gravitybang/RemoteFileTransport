#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<cstring>
#include<sstream>

int main()
{
	std::stringstream ss;
	long total = 0, sum = 0;

	int server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in serveraddr, clientaddr;

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(8888);
	serveraddr.sin_addr.s_addr = inet_addr("192.168.0.107");
	socklen_t addr;
	bind(server, (sockaddr*)&serveraddr, sizeof(serveraddr));
	listen(server, 5);
	std::cout<<"listening"<<std::endl;
	int client = accept(server, (sockaddr*)&clientaddr, &addr);
	std::cout<<"connection success"<<std::endl;
	char recvdata[4096] = { 0 };
	int size = 0, k = 0;
	recv(client, recvdata, 1024, 0);
	ss<<recvdata;ss>>total;
	FILE* file;
	file = fopen("/home/pi/Desktop/opencv_contrib-4.5.1.tar.gz","wb"); 
	while (1)
	{
		memset(recvdata, 0, 4096);
		size = recv(client, recvdata, 4096, 0);
		if (size>0){
			fwrite(recvdata, size, 1, file);k++;
			sum += size;
			std::cout<<size<<" "<<k<<std::endl;
		}
		if(sum == total) break;
	}
	fclose(file);
	return 0;
}