#pragma warning(disable:4996)
#include <iostream> 
#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#include <thread> 

using namespace std; 

#define PACKET_SIZE 1024 

void recv_data(SOCKET &s)
{ 
	char buf[PACKET_SIZE]; 
	
	while(1)
	{ 
		ZeroMemory(buf,PACKET_SIZE); 
		
		recv(s,buf,PACKET_SIZE,0); 
		
		if (WSAGetLastError())
		{
			break; // �������� ����
		}
		cout << "\n[Server] >> " << buf << endl;
		cout << "���� �����͸� �Է� >> ";
	} 
	
	return;
} 

void openSocket(char IP[], int PORT) 
{
	WSADATA wsa; 
	
	if (WSAStartup(MAKEWORD(2, 2), &wsa)) 
	{ 
		cout << "WSA error"; 
		
		WSACleanup(); 
		
		return; 
	} 
	
	SOCKET skt; 
	
	skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); 
	if (skt == INVALID_SOCKET) 
	{ 
		cout << "socket error"; 
		
		closesocket(skt); 
		
		WSACleanup(); 
		
		return; 
	} 
	
	SOCKADDR_IN addr = {}; 
	addr.sin_family = AF_INET; 
	addr.sin_port = htons(PORT); 
	addr.sin_addr.s_addr = inet_addr(IP); 
	
	while (connect(skt, (SOCKADDR*)&addr, sizeof(addr))); 
	
	char buf[PACKET_SIZE]; 
	
	recv(skt, buf, PACKET_SIZE, 0); 
	
	int mynum = atoi(buf); 
	
	sprintf(buf, "[%d] %s::%d", mynum, inet_ntoa(addr.sin_addr), ntohs(addr.sin_port)); 

	int nLen;
	wchar_t wstrBuf[PACKET_SIZE*2];
	
	nLen = (int)strlen(buf) + 1;
	mbstowcs(wstrBuf, buf, nLen);

	SetConsoleTitle(wstrBuf);
	
	thread(recv_data, ref(skt)).detach(); 
	
	while (!WSAGetLastError()) 
	{
		cout << "���� �����͸� �Է� >> "; 
		
		cin.getline(buf, PACKET_SIZE, '\n');
		
		send(skt, buf, strlen(buf), 0); // ������ ���� 
	} 
	
	closesocket(skt); 
	
	WSACleanup(); 
} 

int main()
{ 
	char IP[100]; 
	int PORT; 
	
	cout << "�������ּ� ���� >> "; 
	
	cin >> IP; 
	
	cout << "��Ʈ ���� >> "; 
	
	cin >> PORT; 
	
	openSocket(IP,PORT); 
	
	return 0; 
}