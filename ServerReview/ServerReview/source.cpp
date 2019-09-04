#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

void ErrorMessage(const char* message);
int main() {
	WSADATA wsaData;
	SOCKET hServer, hClient;
	SOCKADDR_IN servAddr, clntAddr;

	int szClntAddr;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		ErrorMessage("WSAStartup() error");

	//소켓 생성
	hServer = socket(PF_INET, SOCK_STREAM, 0);
	if (hServer == INVALID_SOCKET)
		ErrorMessage("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);//빅엔디안으로 변경
	servAddr.sin_port = htonl(10000);

	if (bind(hServer, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorMessage("bind() error");

	if (listen(hServer, 5) == SOCKET_ERROR)
		ErrorMessage("listen() error");

	szClntAddr = sizeof(clntAddr);
	hClient = accept(hServer, (SOCKADDR*)&clntAddr, &szClntAddr);
	if (hClient == INVALID_SOCKET)
		ErrorMessage("accept() error");
	
	closesocket(hClient);
	closesocket(hServer);
	WSACleanup();
	system("pause");
	return 0;
}
void ErrorMessage(const char* message) {
	printf(message);
}