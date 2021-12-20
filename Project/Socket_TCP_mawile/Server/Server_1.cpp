#include "Server.h"

#include <thread> // 멀티 쓰레드 사용 

using namespace std; 

#define MAX 10 // 최대 수용 가능한 클라이언트 수 지정 

WSADATA wsa; // 변수들은 제일 위로 올려준다 
SOCKET skt,client_sock[MAX]; 
SOCKADDR_IN client[MAX] = {0}; 
int client_size[MAX]; 

void accpetclients()	// 클라이언트 연결 관리 함수(멀티 쓰레드)
{  
	for(int i=0;i<MAX;i++)	//for문으로 클라이언트 연결관리!
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
	// 멀티 쓰레드를 사용하여 'accecptclients함수를 호출' 
	// .detach(); 메인 함수는 더 이상 해당 쓰레드가 종료될 때까지 
	// 기다려주지 않음(완전히 별개의 쓰레드로 분리) 
	while(1)
	{ 
		cout << "SERVER_1" << endl;
	} 
	
	for(int i=0;i<MAX;i++) 
		closesocket(client_sock[i]); // for문으로 종료 소켓 늘리기 
	
	closesocket(skt); 
	WSACleanup(); 
}