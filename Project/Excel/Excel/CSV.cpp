#include "Excel.h"

/*
    string 객체의 최대 길이는 42억이지만 물리적인 메모리 한계까지만 쓸 수 있다고 한다.
    CSV 같은 형태의 메모리 사용량은 감당할 수 있지만, 대용량 데이터에는 적합하지 않은 코드이다.
 
    인자 : 
    const char* _directory : 상수 케릭터 포인터로 받는 파일의 경로이다.
 
    결과값 :
    std::string
*/

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

// fopen 의 파일 모드 옵션에 인코딩 타입 지정해 읽기
void CExcel::SetCSV_utf8(std::string _path) {
    wchar_t wcASCII;    //  wchar_t 형식 ASCII 코드를 표현할 변수이다.
    std::string sBuffer;    // 벡터에 넣기 전 문자열을 저장해둘 변수이다.

    FILE* stream;

    if (NULL == (stream = fopen(_path.c_str(), "rt+,ccs=UTF-8"))) {
        printf("Unable to open: %s\n", _path);
        exit(1);
    }

    errno = 0;
    while (WEOF != (wcASCII = fgetwc(stream))) {
        if (wcASCII == 10)
        {
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
        printf("An invalid wide character was encountered.\n");
        exit(1);
    }
    fclose(stream);
}
