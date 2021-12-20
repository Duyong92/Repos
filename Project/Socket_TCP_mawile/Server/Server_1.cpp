#include "Server.h"

#include <thread> // ��Ƽ ������ ��� 

using namespace std; 

#define MAX 10 // �ִ� ���� ������ Ŭ���̾�Ʈ �� ���� 

WSADATA wsa; // �������� ���� ���� �÷��ش� 
SOCKET skt,client_sock[MAX]; 
SOCKADDR_IN client[MAX] = {0}; 
int client_size[MAX]; 

void accpetclients()	// Ŭ���̾�Ʈ ���� ���� �Լ�(��Ƽ ������)
{  
	for(int i=0;i<MAX;i++)	//for������ Ŭ���̾�Ʈ �������!
	{  
		client_size[i] = sizeof(client[i]); 
		client_sock[i] = accept(skt,(SOCKADDR*)&client[i],&client_size[i]); 
		if(client_sock[i]==INVALID_SOCKET)
		{ 
			cout << "accept error"; closesocket(client_sock[i]); 
			closesocket(skt); 
			WSACleanup(); 
			return; 
		} 
	} 
} 

void Server_1()
{ 
	if(WSAStartup(MAKEWORD(2,2), &wsa))
	{ 
		cout << "WSA error"; 
		return; 
	} 
	
	skt = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP); 
	if(skt==INVALID_SOCKET)
	{ 
		cout << "socket error"; 
		closesocket(skt); 
		WSACleanup(); 
		return; 
	} 
	
	SOCKADDR_IN addr = {}; 
	addr.sin_family = AF_INET; 
	addr.sin_port = htons(4444); 
	addr.sin_addr.s_addr = htonl(INADDR_ANY); 
	
	if(bind(skt, (SOCKADDR*)&addr,sizeof(addr)))
	{ 
		cout << "bind error"; 
		closesocket(skt); 
		WSACleanup(); 
		return; 
	} 
	
	if(listen(skt,SOMAXCONN))
	{ 
		cout << "listen error"; 
		closesocket(skt); 
		WSACleanup(); 
		return; 
	} 
	
	thread (accpetclients).detach(); 
	// ��Ƽ �����带 ����Ͽ� 'accecptclients�Լ��� ȣ��' 
	// .detach(); ���� �Լ��� �� �̻� �ش� �����尡 ����� ������ 
	// ��ٷ����� ����(������ ������ ������� �и�) 
	while(1)
	{ 
		cout << "SERVER_1" << endl;
	} 
	
	for(int i=0;i<MAX;i++) 
		closesocket(client_sock[i]); // for������ ���� ���� �ø��� 
	
	closesocket(skt); 
	WSACleanup(); 
}