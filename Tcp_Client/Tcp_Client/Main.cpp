#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
void ErrorHandling(const char* str);
int main() {
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char message[30];
	int strLen = 0;
	int idx = 0, readLen = 0;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
		ErrorHandling("wsaStartup() error");
	}

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if(hSocket==INVALID_SOCKET){
		ErrorHandling("socket() error");
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(10000);

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		ErrorHandling("connect() error");
	}

	while (readLen = recv(hSocket, &message[idx++], 1, 0)) {
		if (readLen == -1)
			ErrorHandling("read() error!");

		strLen += readLen;
	}

	printf("Message from Server:%s\n", message);
	printf("Function read call count : %d \n", strLen);

	closesocket(hSocket);
	WSACleanup();
	system("pause");
	return 0;
}
void ErrorHandling(const char * str)
{
	fputs(str, stderr);
	fputc('\n', stderr);
	exit(1);
}
