#include "Excel.h"

//#pragma warning(disable: 4996)
/*
    string 객체의 최대 길이는 42억이지만 물리적인 메모리 한계까지만 쓸 수 있다고 한다.
    CSV 같은 형태의 메모리 사용량은 감당할 수 있지만, 대용량 데이터에는 적합하지 않은 코드이다.

    인자 :
    const char* _directory : 상수 케릭터 포인터로 받는 파일의 경로이다.

    결과값 :
    std::string
*/

/*
std::string CSVToString(const char* _path) {
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
*/

/*
CSV 를 ifstream으로 읽게 될 경우 '\,''\'','\"','\n' 같은 기호가 중첩으로 처리될 수 있다.
위와 같은 상황은 모두 배제하고 문자만 처리한다는 가정하에 사용할 수 있는 코드이다.

인자 :
std::string _content : CSV 의 모든 내용을 저장한 문자열 형태이다.

결과값 :
std::vector<std::vector<std::string>>
*/

/*
std::vector<std::vector<std::string>> readCSVString(std::string& _content) {
    std::string sBuffer;
    std::vector<std::string> m_vsCell;

    if (_content.empty())
        perror("해당 하는 CSV 문자열에 오류가 있습니다.");
    else {
        for(int i = 0; i < _content.size(); i++){}
    }
}
*/

/*
// locale 설정 이후로 UTF-8 파일을 읽는 방법이다.
void readUTF8_locale(std::string _path) {
    std::wstring ws_path = std::wstring(_path.begin(), _path.end());
    const wchar_t* wcs_path = ws_path.c_str();
    std::locale::global(std::locale(".UTF-8"));
    std::wifstream f(wcs_path);
    if (f.is_open()) {
        std::wstring ws;
        f >> ws;
        printf("is it working?");
    }
    else {
        perror("sth went wrong");
    }
}
*/

/*
C6262 : 함수에서 '20032' 바이트의 스택을 사용하는데 이 크기가  /analyze:stacjsuze '16384'을(를) 초과합니다.
일부 데이터를 힙으로 이동하십시오.
수정하지 않아도 사용이 가능하다.
buffer[10000] -> buffer[5000] 
*/

void CExcel::SetCSV(std::string _path) {
    char szASCII;   // char 타입으로 ASCII 코드를 받는 변수이다.
    std::string sBuffer;    // 벡터에 넣기 전 문자열을 저장해둘 변수이다.

    FILE* stream;

    if (NULL == (stream = fopen(_path.c_str(), "rt"))) {
        std::cout << "Unable to open: " << _path << std::endl;
        exit(1);
    }

    errno = 0;
    while (EOF != (szASCII = fgetc(stream))) {
        // 개행 문자(아스키코드 10)일 경우
        if (szASCII == 10) {
            // 문자 배열을 문자 배열 벡터에 추가합니다.
            m_vsCell.push_back(sBuffer);
            // 문자 배열 벡터를 2 차원 벡터에 추가합니다.
            m_vvsExcel.push_back(m_vsCell);
            // 최대 행 크기를 갱신합니다.
            if (m_unColumn < static_cast<unsigned int>(m_vsCell.size() - 1))
                m_unColumn = static_cast<unsigned int>(m_vsCell.size() - 1);
            // 문자 배열 벡터를 초기화합니다.
            m_vsCell.clear();
            // 임시 문자열을 초기화합니다.
            sBuffer = "";
            // 최대 열 크기를 갱신합니다.
            m_unRow++;
        }
        // 쉼표(아스키코드 44)일 경우
        else if (szASCII == 44) {
            std::cout << "sBuffer: " << sBuffer << std::endl;
            // 문자 배열을 문자 배열 벡터에 추가합니다.
            m_vsCell.push_back(sBuffer);
            // 임시 문자열을 초기화 합니다.
            sBuffer = "";
        }
        else
            sBuffer += szASCII;

    }

    if (EILSEQ == errno) {
        std::cout << "An invalid wide character was encountered." << std::endl;
        exit(1);
    }
    fclose(stream);
}


// fopen 의 파일 모드 옵션에 인코딩 타입 지정해 읽기
void CExcel::SetCSV_utf8(std::string _path) {
    wchar_t wcASCII;    //  wchar_t 형식 ASCII 코드를 표현할 변수이다.
    std::string sBuffer;    // 벡터에 넣기 전 문자열을 저장해둘 변수이다.
    typeid(_path).name();
    FILE* stream;

    if (NULL == (stream = fopen(_path.c_str(), "rt+,ccs=UTF-8"))) {
        /*
        C6284: 개체가 _Param_(2)으로 전달되었습니다. 'printf'에 대한 호출에는 문자열이 필요합니다.
        실제 형식: 'class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>>'
        
        #include <typeinfo>
        typeid(_path).name()
        로 출력해보면 똑같은 타입이 출력된다.
        */
        /*
        std::filesystem 호출이 되지 않는다.
        */
        std::cout << "Unable to open: " << _path << std::endl;
        exit(1);
    }

    errno = 0;
    while (WEOF != (wcASCII = fgetwc(stream))) {
        if (wcASCII == 10)
        {
            std::cout << sBuffer << std::endl;
            // 문자 배열을 문자 배열 벡터에 추가합니다.
            m_vsCell.push_back(sBuffer);
            // 문자 배열 벡터를 2 차원 벡터에 추가합니다.
            m_vvsExcel.push_back(m_vsCell);
            // 최대 행 크기를 갱신합니다.
            if (m_unColumn < static_cast<unsigned int>(m_vsCell.size() - 1))
                m_unColumn = static_cast<unsigned int>(m_vsCell.size() - 1);
            // 문자 배열 벡터를 초기화합니다.
            m_vsCell.clear();
            // 임시 문자열을 초기화합니다.
            sBuffer = "";
            // 최대 열 크기를 갱신합니다.
            m_unRow++;
        }
        // 쉼표(아스키코드 44)일 경우
        else if (wcASCII == 44)
        {
            // 문자 배열을 문자 배열 벡터에 추가합니다.
            m_vsCell.push_back(sBuffer);
            // 임시 문자열을 초기화 합니다.
            sBuffer = "";
        }
        else
            sBuffer += wcASCII;
    }
        
        
    if (EILSEQ == errno) {
        std::cout << "An invalid wide character was encountered." << std::endl;
        exit(1);
    }
    fclose(stream);

    /* 
    한 줄 읽기도 가능하다.
    wchar_t buffer[10000];
    fwscanf(f, L"%ls", buffer); // scanf 포맷으로 읽기
    fgetws(buffer, 1000, f);    // 한 줄 읽기 (gets w 버전)
    printf("%ls", buffer);
    */
}
