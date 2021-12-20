#pragma warning(disable:4996)
#include <iostream> 
#include <winsock2.h> 
#pragma comment(lib, "ws2_32")
#include <thread> 

using namespace std; 

#define PACKET_SIZE 1024 

WSADATA wsa; 
SOCKET skt, *client_sock; 
SOCKADDR_IN *client; 
int *client_size, MAX; 



void recv_data(SOCKET &s,int client_num)
{ 
	char buf[PACKET_SIZE]; 
	while(1)
	{ 
		ZeroMemory(buf,PACKET_SIZE); 
		if (recv(s, buf, PACKET_SIZE, 0) == -1)
		{
			break; // 클라이언트 종료 감지 
		}
		cout << "\nClient #" << client_num << " << " << buf << "\n보낼 데이터를 입력 >> "; 
	} 

	return; 
} 

void accpetclients()
{ 
	char client_num[10]; 
	for(int i = 0; i < MAX; i++)
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
		
		cout << "Client #" << i << " Joined!" << endl;
		cout << "보낼 데이터를 입력 >> ";
		
		ZeroMemory(client_num,sizeof(client_num)); 
		/* char* itoa(int val, char* buf, int radix)
		val : 변환할 정수이다.
		buf : 변환 받을 문자열을 저장할 문자열 변수이다.
		radix : 변환할 진수이다.
		리턴 값 :
			변환된 문자열의 주소 */
		itoa(i,client_num,10); 
		
		send(client_sock[i],client_num,strlen(client_num),0); 
		
		thread (recv_data,ref(client_sock[i]),i).detach(); 
	} 
	
	return; 
} 

void openSocket(int PORT)
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
	addr.sin_port = htons(PORT); 
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
	
	char msg[PACKET_SIZE],sendnum[PACKET_SIZE];
	char msgBuf[PACKET_SIZE];
	
	while(1)
	{ 
		cout << "보낼 데이터를 입력 >> "; 
		
		cin >> msgBuf; //데이터 내용 
		strcpy(msg, msgBuf);
		cout << "msg repeat? : " << msg << endl;
		if (!strcmp(msg, "exit"))
		{
			break; // 데이터의 내용이 "exit"일 시 소켓종료 
		}

		cout << "대상 클라이언트를 입력(all:모두) >> ";

		cin >> sendnum; // 대상 클라이언트 번호 지정 "all"일 시 모든 클라이언트에게 전송 

		if (!strcmp(sendnum, "all")) // 변수sendnum의 내용이 "all" 이라면 모두에게 메세지전송 
		{
			for (int i = 0; i < MAX; i++)
			{
				send(client_sock[i], msg, strlen(msg), 0);
			}
		}
		else
		{
			send(client_sock[atoi(sendnum)], msg, strlen(msg), 0); // 아니라면 한명에게만 전송 
		}
	}
			
	for(int i=0;i<MAX;i++) 
		closesocket(client_sock[i]); 
			
	closesocket(skt); 
			
	WSACleanup(); 
			
	return; 
} 
		
int main()
{ 
	int PORT; 
	
	cout << "포트설정 >> "; 
	
	cin >> PORT; 
	
	cout << "클라이언트 최대수용 수 설정 >> "; 
	
	cin >> MAX; 
	
	client_sock = new SOCKET[MAX]; 
	client = new SOCKADDR_IN[MAX]; 
	client_size = new int[MAX]; 
	ZeroMemory(client_sock,sizeof(client_sock)); 
	ZeroMemory(client,sizeof(client)); 
	ZeroMemory(client_size,sizeof(client_size)); 
	
	openSocket(PORT); 
	
	delete[] client_sock, client, client_size; 
	
	return 0; 
}