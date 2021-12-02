#pragma once

using namespace std;

vector<string> csv_read_row(istream& file, char delimiter)
{
    // 문자열을 저장할 스트림이다.
    stringstream ss;

    // 특수문자 여부를 묻는 bool 형식이다.
    bool inquotes = false;

    vector<string> row;//relying on RVO

    while (file.good())
    {
        // 첫 char 를 가져온다.
        char c = file.get();
        // inquotes 가 FALSE 이면서 쌍따옴표일 경우 inquotes 를 TRUE 로 반환한다.
        if (!inquotes && c == '"')
        {
            inquotes = true;
        }
        // inquotes 가 TRUE 이면서 쌍따옴표일 경우,
        else if (inquotes && c == '"')
        {
            /* 
                istream::peek
                인자 - 없음
                리턴값 - 그 다음 문자의 값을 리턴한다. 
                오류가 발생 시에 이 함수는 EOF 를 리턴하며, 
                내부 상태 플래그를 다음과 같은 상황에 맞게 변경하게 된다.

                eofbit - 작업 중 문자들의 끝에 도달하였을 때
                failbit -
                badbit - 위 같은 일들 외의 다른 오류가 발생 시

                ios::exceptions 함수들로 설정되었다면, ios_bas::failure 가 throw 된다.
                https://modoocode.com/194
            */
            if (file.peek() == '"')
            {
                ss << (char)file.get();
            }
            // 쌍따옴표가 아니기 때문에 inquotes 를 FALSE 로 반환한다.
            else
            {
                inquotes = false;
            }
        }
        // inquotes 가 FALSE 이면서 구분자일 경우,
        else if (!inquotes && c == delimiter)
        {
            /*
                vector::push_back
                void push_back(const T& x);
                벡터 끝에 원소를 추가한다.
                인자 - x: 새로 추가 될 원소에 복사될 원소
                       T:  백터에 저장되어 있는 원소들의 타입
                리턴값 - 없음

                만일 재할당이 발생한다면 이는 Allocator::allocate() 를 이용해서 수행되는데,
                예외를 던질(throw) 수 있다. 
                (디폴트 할당자의 경우 만일 요청한 할당이 성공하지 않을 경우 bad_alloc 이 던져진다)
                https://modoocode.com/185
            */
            // 빈 문자열을 row에 넣어준다.
            row.push_back(ss.str());
            // 문자열 스트림에 쌍따옴표로 초기화해준다.
            ss.str("");
        }
        // inquotes 가 FALSE 이면서 줄바꿈일 경우,
        else if (!inquotes && (c == '\r' || c == '\n'))
        {
            // 다음 문자도 줄바꿈일 경우 줄바꿈을 넣어준다.
            if (file.peek() == '\n') { file.get(); }
            // 빈 문자열을 row에 넣어준다.
            row.push_back(ss.str());
            // row를 출력한다.
            return row;
        }
        else
        {
            // 문자열 스트림에 글자를 집어 넣는다.
            ss << c;
        }
    }
}