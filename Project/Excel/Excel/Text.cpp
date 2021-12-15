#include "Excel.h"

/*
    string 객체의 최대 길이는 42억이지만 물리적인 메모리 한계까지만 쓸 수 있다고 한다.
    CSV 같은 형태의 메모리 사용량은 감당할 수 있지만, 대용량 데이터에는 적합하지 않은 코드이다.
    기본적인 인코더 방식은 ANSI 이다.

    인자 :
    std::string _path : 상수 케릭터 포인터로 받는 파일의 경로이다.

    결과값 :
    std::string
*/
std::string ReadText(std::string _path) {
    std::ifstream in(_path);
    std::string s;

    if (in.is_open()) {
        // 위치 지정자를 파일 끝으로 옮긴다.
        in.seekg(0, std::ios::end);

        // 그리고 그 위치를 읽는다. (파일의 크기)
        int size = in.tellg();

        // 그 크기의 문자열을 할당한다.
        s.resize(size);

        // 위치 지정자를 다시 파일 맨 앞으로 옮긴다.
        in.seekg(0, std::ios::beg);

        // 파일 전체 내용을 읽어서 문자열에 저장한다.
        in.read(&s[0], size);
    }
    else {
        perror("파일을 찾을 수 없습니다!");
    }

    return s;
}

#include <sstream>
#include <locale>
#include <codecvt>
/*
    UTF-8 로도 text 형식의 파일을 읽을 수 있게 인코딩해서 출력합니다.
    reference : https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=enigs32167&logNo=221455061918
    조금 더 살펴 봐야한다.

    인자 :
    std::string _path : 상수 케릭터 포인터로 받는 파일의 경로이다.

    결과값 :
    std::string
*/
std::string ReadText_utf8(std::string _path) {
    std::string s;
    std::wstring _ws = std::wstring(_path.begin(), _path.end());
    const wchar_t* wcs = _ws.c_str();
    std::wifstream wif(wcs);
    wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
    std::wstringstream wss;
    wss << wif.rdbuf();

    // Setting Locale to Korean
    std::locale::global(std::locale("kor")); //"UTF-8") );
    
    std::wstring ws;
    do {
        ws = wss.str();
        std::cout << ws.c_str() << std::endl;
    } while ( !ws.empty() );

    s.assign(ws.begin(), ws.end());

    return s;
}