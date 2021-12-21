참조(Reference) :
TCP/IP 통신 함수 사용과 WinSock2.h
https://locs.tistory.com/19

https://docs.microsoft.com/en-us/windows/win32/api/winsock2/

PF_INET과 AF_INET의 차이점 by 해커남
https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=ifkiller&logNo=70081338273

AF_INET은 주소 체계(주소 패밀리) 중 하나입니다.
IPv4 인터넷 프로토콜로 정의됩니다.

socket 통신
https://mikrkosmos97.tistory.com/8
https://mintnlatte.tistory.com/273
	setsockopt를 통해 소켓 옵션도 조절할 수 있다.

recv()
https://www.it-note.kr/123

To Do
추후 소켓 에러 코드에 따른 분류를 enum switch로 구분할 수 있는 함수 만들기
다중 클라이언트 관리

Else
10:30 git 잘못된 운용으로 인한 작업 손실 / 꾸준한 push 와 pool 을 통해 관리 필요

12:00  Socket_TCP_mintnlatte PF_INET 형식이라 예제 포기

12:00 Socket_TCP_mawile 대체 사이트로 https://mawile.tistory.com/30?category=959178 참조

12:14 오류 C4996 'inet_addr': Use inet_pton() or InetPton() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings

12:25 #pragma warning(disable:4996)으로 해결



12:54 Server_Receiver https://twinw.tistory.com/155 참조



14:12 Server_Multi, Client_Multi

15:00 다중 Client, Server 연결 완료, Client 간의 연결 실패

16:07 Server, Client 간 cin 으로 문자열 공백 삽입 불가 

	char[]이 원인인 것으로 착각 -> string 입력 후 split 함수를 만들어 char[]로 나누어 송신 시도

	cin 공백 입력이 안되는 것으로 확인

	cin.getline() 으로 시도 -> 구분자로 인해 send 불가

16:46 C++ 동기, 비동기 개념 공부

17:31 promise, future의 wait for을 사용하여 동기식 설정으로 채팅 업그레이드 예정

(참조 : https://github.com/Duyong92/repos)
	
