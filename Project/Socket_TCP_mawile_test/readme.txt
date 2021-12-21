211221 
0926 
C6066 : 포인터가 아닌 항목이 _Param_(2)로 전달되었습니다. 'printf'에 대한 호출에는 포인터가 필요합니다. 실제 형식 'int'
_clientNum -> &_clientNum
C6066 : 포인터가 아닌 항목이 _Param_(2)로 전달되었습니다. 'printf'에 대한 호출에는 포인터가 필요합니다. 실제 형식 'int'
i+1 -> &i+1
0941
함수에 내장하여 설정해주는 것이 더 좋아 보인다.
WORD wVersionRequested; -> (DELETE)
1001 
backlog 의 최대값은 <sys/socket.h> 에 정의된 SOMAXCONN 을 참조합니다.
https://techpad.tistory.com/62
1024
C3861 : 'ref': 식별자를 찾을 수 없습니다.
E0020 : 식별자 "stderr"이(가) 정의되어 있지 않습니다.
C2039 : 'ref': 'std'의 멤버가 아닙니다.
C2873 : 'ref': using 선언에서 기호를 사용할 수 없습니다.
1037
E0020 : 식별자 "stderr"이(가) 정의되어 있지 않습니다.
굳이 필요 없기 때문에 삭제해주었다
stderr -> (DELETE), fprintf() -> printf()
C3861 : 'ref': 식별자를 찾을 수 없습니다.
using std::reference_wrapper;, using std::ref; 추가
1045
클라이언트 소켓 포인터의 값이 존재하지 않아도 읽히기 때문에 전처리가 필요하다.
1101
클라이언트 소켓이 없을 경우 0으로 읽힌다.
클라이언트 0번째 값도 확인해보고 0으로 전처리할 예정이다.
1133
Debug Assertion Failed
Client.cpp 포트번호 입력 시 connect() 오류 10061 발생
1140
Expression:("'n' format specifier disabled", 0)
1322
Server.cpp 송신자 수 확인 관련 오타 수정
pszSendMessage->pszSendNum
1357
socket 번호를 통해 수신자 확인하려 했으나 실패
추후 vector를 통해 수신자 관리 예정
1428
수신 메세지를 string으로 임시로 변환시킴으로 수정하기 수월해졌다
단, 아직도 cin 부분에 띄어쓰기를 할 경우 문제는 해결되지 않는다.
1434
cin으로 문자열 받는 방법
https://leeusin.tistory.com/429
1454
getline() 함수 사용 시 delimeter를 설정해도 cin에서 넘어간다.
1530까지만 더 해보고 파일 TCP로 넘어갈 예정
1500
cin.ignore()을 통해 cin 호출 완료


