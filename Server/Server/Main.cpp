// Server.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>//socket����� ����. ���� �ֱ� ������ 2����

void ErrorHandling(const char* message);

int main() {
	WSADATA wsaData;//������ ���� ���ø����̼� ������
	SOCKET hServSock, hClntSock;//������ ���ϵ�
	SOCKADDR_IN servAddr, clntAddr;//�ּ�

	int szClntAddr;
	char message[] = "Hello world";

	//������� ��ȭ�� �����ϱ� ������
	//WSAStartup�� �̿��� �ش� ���α׷� ��� �㰡 ��û
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	//socket : �������� ����� ���� ����
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	//�ּ� �ʱ�ȭ
	memset(&servAddr, 0, sizeof(servAddr));//memory setting > ��� �����͸� 0���� �ʱ�ȭ
	servAddr.sin_family = AF_INET;//AF_INET ipv4����ϰڴ�
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);//s_addr:���� �ּ� = htonl(INADDR_ANY):�� �ּ�
	servAddr.sin_port = htons(10000);//10000�� ��Ʈ�� ���ڴ�.

	//bind ������ ����.
	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	//listen �ѹ��� �ִ� 5���� ���� ó���ϰڴ�.(���� 5���� ����)
	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	szClntAddr = sizeof(clntAddr);
	//accept Ŭ���̾�Ʈ ������ �ޱ����� ���. ���⼭ ����
	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
	if (hClntSock == INVALID_SOCKET)
		ErrorHandling("accept() error");

	//send �޼���
	send(hClntSock, message, sizeof(message), 0);//flag �ظ��ϸ� 0 si�ʿ��� ���� ���. ���Ӽ��������� �� ��� ����
		
	closesocket(hClntSock);
	closesocket(hServSock);
	WSACleanup();
	//�����쿡 �㰡 ���� �κ� ����
	//���� ���ϸ� ������ ����Ǿ������� �� ���Ͽ��� ���� �ִ� ��Ʈ�� ��� ���ǰ� �ִٰ� �ν�
	//�̷����� ������ ������� ���� �ʱ�ȭ�ؾ���
	system("pause");
	return 0;
}
void ErrorHandling(const char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}