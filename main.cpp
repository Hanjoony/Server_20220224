#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "ws2_32.lib")		// 윈도우에 기본으로 깔려있는 라이브러리 불러오기 필요

int main()
{
	WSAData wsaData;

	// 1. winsock 초기화, 윈도우만 합니다. linux, unix 에선 사용하지 않음
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Winsock Error" << GetLastError() << endl;		// GetLastError() 마지막에 난 에러의 번호를 리턴함
		exit(-1);												// 여기까지가 winsock 초기화
	}

	// 2. create socket
	SOCKET ServerSocket;										//listen 클라이언트 대기 소켓(문)

	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "socket Error : " << GetLastError() << endl;
		exit(-1);
	}

	// 2. ip, port를 할당해서 소켓이랑 연결
	SOCKADDR_IN ServerAddr;

	memset(&ServerAddr, 0, sizeof(ServerAddr));			// 메모리 영역을 0으로 채움

	ServerAddr.sin_family = AF_INET;					// 2바이트
	ServerAddr.sin_port = htons(50000);					// 2바이트
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);		// 4바이트
	
	if (bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)		//  소켓 에러 확인, port가 겹쳐서 에러나는 경우 많음
	{
		cout << "bind Error : " << GetLastError() << endl;
		exit(-1);
	}

	// 3. 클라이언트 연결을 기다려라
	if (listen(ServerSocket, 0) == SOCKET_ERROR)
	{
		cout << "listen Error : " << GetLastError() << endl;
		exit(-1);
	}
	while (1)				// 서버가 안 꺼지게 반복
	{
		// 4. 수락해서 클라이언트와 연결을 완성
		SOCKADDR_IN ClientAddr;
		int ClientAddrSize = sizeof(ClientAddr);
		SOCKET ClientSocket = 0;					// 클라이언트가 된 통로 (문)
		ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddr, &ClientAddrSize);
		if (ClientSocket == SOCKET_ERROR)
		{
			cout << "accept Error : " << GetLastError() << endl;
			exit(-1);
		}

		cout << "connect ip : " << inet_ntoa(ClientAddr.sin_addr) << endl;		// inet network to address
		cout << "connect port : " << ntohs(ClientAddr.sin_port) << endl; 		// network to host short

		// 5. 보낸다 자료를 클라이언트한테
		char Message[1024] = { 0, };
		recv(ClientSocket, Message, 1024 - 1, 0);

		cout << "client sended : " << Message << endl;

		send(ClientSocket, Message, strlen(Message) + 1, 0);

		cout << "client send : " << Message << endl;

		// 6. 연결 종료
		closesocket(ClientSocket);
	}

	closesocket(ServerSocket);

	// 7. Winsock 종료,	1번하고 7번은 윈도우만 함
	WSACleanup();

	return 0;
}