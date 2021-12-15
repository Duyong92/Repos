#include "Excel.h"

/*
    string ��ü�� �ִ� ���̴� 42�������� �������� �޸� �Ѱ������ �� �� �ִٰ� �Ѵ�.
    CSV ���� ������ �޸� ��뷮�� ������ �� ������, ��뷮 �����Ϳ��� �������� ���� �ڵ��̴�.
    �⺻���� ���ڴ� ����� ANSI �̴�.

    ���� :
    std::string _path : ��� �ɸ��� �����ͷ� �޴� ������ ����̴�.

    ����� :
    std::string
*/
std::string ReadText(std::string _path) {
    std::ifstream in(_path);
    std::string s;

    if (in.is_open()) {
        // ��ġ �����ڸ� ���� ������ �ű��.
        in.seekg(0, std::ios::end);

        // �׸��� �� ��ġ�� �д´�. (������ ũ��)
        int size = in.tellg();

        // �� ũ���� ���ڿ��� �Ҵ��Ѵ�.
        s.resize(size);

        // ��ġ �����ڸ� �ٽ� ���� �� ������ �ű��.
        in.seekg(0, std::ios::beg);

        // ���� ��ü ������ �о ���ڿ��� �����Ѵ�.
        in.read(&s[0], size);
    }
    else {
        perror("������ ã�� �� �����ϴ�!");
    }

    return s;
}

#include <sstream>
#include <locale>
#include <codecvt>
/*
    UTF-8 �ε� text ������ ������ ���� �� �ְ� ���ڵ��ؼ� ����մϴ�.
    reference : https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=enigs32167&logNo=221455061918
    ���� �� ���� �����Ѵ�.

    ���� :
    std::string _path : ��� �ɸ��� �����ͷ� �޴� ������ ����̴�.

    ����� :
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