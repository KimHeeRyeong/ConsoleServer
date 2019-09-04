// Server.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>//socket사용을 위함. 가장 최근 버전이 2버전

void ErrorHandling(const char* message);

int main() {
	WSADATA wsaData;//윈도우 소켓 어플리케이션 데이터
	SOCKET hServSock, hClntSock;//서버의 소켓들
	SOCKADDR_IN servAddr, clntAddr;//주소

	int szClntAddr;
	char sendMsg[50] = "숫자 입력(종료는 0)";
	char reciveMsg[100] = {0};
	char message[100] = "숫자 입력(종료는 0)";

	//윈도우는 방화벽 존재하기 때문에
	//WSAStartup을 이용해 해당 프로그램 사용 허가 요청
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	//socket : 서버에서 사용할 소켓 생성
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	//주소 초기화
	memset(&servAddr, 0, sizeof(servAddr));//memory setting > 모든 데이터를 0으로 초기화
	servAddr.sin_family = AF_INET;//AF_INET ipv4사용하겠다
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);//s_addr:서버 주소 = htonl(INADDR_ANY):내 주소
	servAddr.sin_port = htons(10000);//10000번 포트를 열겠다.

	//bind 서버를 연다.
	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	//listen 한번에 최대 5개의 일을 처리하겠다.(줄을 5열로 세움)
	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	szClntAddr = sizeof(clntAddr);
	//accept 클라이언트 접속을 받기위해 대기. 여기서 멈춤
	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
	if (hClntSock == INVALID_SOCKET)
		ErrorHandling("accept() error");

	//hClntSock 는 일종의 계정명, id (클라이언트 소켓과 서버의 클라이언트 소켓은 다름)
	while (1) {
		//send 메세지
		memset(sendMsg, 0, sizeof(sendMsg));
		strcpy_s(sendMsg, sizeof("숫자 입력(종료는 0)"), "숫자 입력(종료는 0)");
		send(hClntSock, sendMsg, sizeof(sendMsg), 0);//flag 왠만하면 0 si쪽에서 많이 사용. 게임서버에서는 잘 사용 안함
		
		//첫번째 숫자 받기
		memset(reciveMsg, 0, sizeof(reciveMsg));
		int strLen = recv(hClntSock, reciveMsg, sizeof(reciveMsg) - 1, 0);
		if (strLen == -1)
			ErrorHandling("read() error!");
		printf("First number:%s \n", reciveMsg);
		if (!strcmp(reciveMsg, "0")) {
			printf("종료\n");
			break;
		}
		int first = atoi(reciveMsg);
		//send 메세지
		send(hClntSock, sendMsg, sizeof(sendMsg), 0);

		//두번째 숫자 받기
		memset(reciveMsg, 0, sizeof(reciveMsg));
		strLen = recv(hClntSock, reciveMsg, sizeof(reciveMsg) - 1, 0);
		if (strLen == -1)
			ErrorHandling("read() error!");
		printf("Second number:%s \n", reciveMsg);
		if (!strcmp(reciveMsg, "0")) {
			printf("종료\n");
			break;
		}
		int second = atoi(reciveMsg);

		//결과 메세지
		memset(sendMsg, 0, sizeof(sendMsg));
		_itoa_s(first*second, sendMsg, 10);
		printf("결과 : %s \n", sendMsg);
		printf("==============\n");
		send(hClntSock, sendMsg, sizeof(sendMsg), 0);
	}
	closesocket(hClntSock);
	closesocket(hServSock);
	WSACleanup();
	//윈도우에 허가 받은 부분 제거
	//제거 안하면 소켓이 종료되었음에도 이 소켓에서 쓰고 있는 포트가 계속 사용되고 있다고 인식
	//이럴때는 윈도우 재부팅을 통해 초기화해야함
	system("pause");
	return 0;
}
void ErrorHandling(const char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}