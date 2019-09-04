#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

void ErrorMessage(const char* message);
int main() {
	WSADATA wsaData;
	SOCKET hServer, hClient;
	SOCKADDR_IN servAddr, clntAddr;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		ErrorMessage("WSAStartup() error");

	hServer = socket(PF_INET, SOCK_STREAM,0);
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);//빅엔디안으로 변경
	servAddr.sin_port = htonl(10000);

	if (bind(hServer,(SOCKADDR*)&servAddr, sizeof(servAddr))==SOCKET_ERROR) {

	}
	
}
void ErrorMessage(const char* message) {
	printf(message);
}