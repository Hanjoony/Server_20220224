#include <WinSock2.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "ws2_32.lib")		// �����쿡 �⺻���� ����ִ� ���̺귯�� �ҷ����� �ʿ�

int main()
{
	WSAData wsaData;

	// winsock �ʱ�ȭ, �����츸 �մϴ�. linux, unix ���� ������� ����
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Winsock Error" << GetLastError() << endl;		// GetLastError() �������� �� ������ ��ȣ�� ������
		exit(-1);												// ��������� winsock �ʱ�ȭ
	}
}