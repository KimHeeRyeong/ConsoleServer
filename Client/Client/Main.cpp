#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

void ErrorHandling(const char* message);

int main() {
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;
	char sendMsg[50] = {0};
	char reciveMsg[100] = {0};
	char message[100];
	int strLen;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(10000);

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error");
	while (1) {
		//recv������ ���������� ���
		//�޼��� �ޱ�
		memset(reciveMsg, 0, sizeof(reciveMsg));
		strLen = recv(hSocket, reciveMsg, sizeof(reciveMsg) - 1, 0);
		if (strLen == -1)
			ErrorHandling("read() error!");
		printf("%s \n", reciveMsg);

		//ù��° ���� ������
		memset(sendMsg, 0, sizeof(sendMsg));
		scanf_s("%s", sendMsg, sizeof(sendMsg));
		send(hSocket, sendMsg, sizeof(sendMsg), 0);
		if (!strcmp(sendMsg, "0")) {
			printf("����\n");
			break;
		}
		//�޼��� �ޱ�
		memset(reciveMsg, 0, sizeof(reciveMsg));
		strLen = recv(hSocket, reciveMsg, sizeof(reciveMsg) - 1, 0);
		if (strLen == -1)
			ErrorHandling("read() error!");
		printf("%s \n", reciveMsg);

		//�ι�° ���� ������
		memset(sendMsg, 0, sizeof(sendMsg));
		scanf_s("%s", sendMsg, sizeof(sendMsg));
		send(hSocket, sendMsg, sizeof(sendMsg), 0);
		if (!strcmp(sendMsg, "0")) {
			printf("����\n");
			break;
		}

		//��� �޼��� �ޱ�
		memset(reciveMsg, 0, sizeof(reciveMsg));
		strLen = recv(hSocket, reciveMsg, sizeof(reciveMsg) - 1, 0);
		if (strLen == -1)
			ErrorHandling("read() error!");
		printf("�����:%s \n", reciveMsg);
		printf("==============\n");
	}
	closesocket(hSocket);
	WSACleanup();
	system("pause");
	return 0;
}
void ErrorHandling(const char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}