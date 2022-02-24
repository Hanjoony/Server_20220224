#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "ws2_32.lib")		// �����쿡 �⺻���� ����ִ� ���̺귯�� �ҷ����� �ʿ�

int main()
{
	WSAData wsaData;

	// 1. winsock �ʱ�ȭ, �����츸 �մϴ�. linux, unix ���� ������� ����
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Winsock Error" << GetLastError() << endl;		// GetLastError() �������� �� ������ ��ȣ�� ������
		exit(-1);												// ��������� winsock �ʱ�ȭ
	}

	// 2. create socket
	SOCKET ServerSocket;										//listen Ŭ���̾�Ʈ ��� ����(��)

	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "socket Error : " << GetLastError() << endl;
		exit(-1);
	}

	// 2. ip, port�� �Ҵ��ؼ� �����̶� ����
	SOCKADDR_IN ServerAddr;

	memset(&ServerAddr, 0, sizeof(ServerAddr));			// �޸� ������ 0���� ä��

	ServerAddr.sin_family = AF_INET;					// 2����Ʈ
	ServerAddr.sin_port = htons(50000);					// 2����Ʈ
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);		// 4����Ʈ
	
	if (bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)		//  ���� ���� Ȯ��, port�� ���ļ� �������� ��� ����
	{
		cout << "bind Error : " << GetLastError() << endl;
		exit(-1);
	}

	// 3. Ŭ���̾�Ʈ ������ ��ٷ���
	if (listen(ServerSocket, 0) == SOCKET_ERROR)
	{
		cout << "listen Error : " << GetLastError() << endl;
		exit(-1);
	}
	while (1)				// ������ �� ������ �ݺ�
	{
		// 4. �����ؼ� Ŭ���̾�Ʈ�� ������ �ϼ�
		SOCKADDR_IN ClientAddr;
		int ClientAddrSize = sizeof(ClientAddr);
		SOCKET ClientSocket = 0;					// Ŭ���̾�Ʈ�� �� ��� (��)
		ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddr, &ClientAddrSize);
		if (ClientSocket == SOCKET_ERROR)
		{
			cout << "accept Error : " << GetLastError() << endl;
			exit(-1);
		}

		cout << "connect ip : " << inet_ntoa(ClientAddr.sin_addr) << endl;		// inet network to address
		cout << "connect port : " << ntohs(ClientAddr.sin_port) << endl; 		// network to host short

		// 5. ������ �ڷḦ Ŭ���̾�Ʈ����
		char Message[1024] = { 0, };
		recv(ClientSocket, Message, 1024 - 1, 0);

		cout << "client sended : " << Message << endl;

		send(ClientSocket, Message, strlen(Message) + 1, 0);

		cout << "client send : " << Message << endl;

		// 6. ���� ����
		closesocket(ClientSocket);
	}

	closesocket(ServerSocket);

	// 7. Winsock ����,	1���ϰ� 7���� �����츸 ��
	WSACleanup();

	return 0;
}