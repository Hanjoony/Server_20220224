#include <WinSock2.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "ws2_32.lib")		// 윈도우에 기본으로 깔려있는 라이브러리 불러오기 필요

int main()
{
	WSAData wsaData;

	// winsock 초기화, 윈도우만 합니다. linux, unix 에선 사용하지 않음
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Winsock Error" << GetLastError() << endl;		// GetLastError() 마지막에 난 에러의 번호를 리턴함
		exit(-1);												// 여기까지가 winsock 초기화
	}
}