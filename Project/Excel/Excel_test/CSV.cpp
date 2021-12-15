#include "Excel.h"

//#pragma warning(disable: 4996)
/*
    string ��ü�� �ִ� ���̴� 42�������� �������� �޸� �Ѱ������ �� �� �ִٰ� �Ѵ�.
    CSV ���� ������ �޸� ��뷮�� ������ �� ������, ��뷮 �����Ϳ��� �������� ���� �ڵ��̴�.

    ���� :
    const char* _directory : ��� �ɸ��� �����ͷ� �޴� ������ ����̴�.

    ����� :
    std::string
*/

/*
std::string CSVToString(const char* _path) {
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
*/

/*
CSV �� ifstream���� �а� �� ��� '\,''\'','\"','\n' ���� ��ȣ�� ��ø���� ó���� �� �ִ�.
���� ���� ��Ȳ�� ��� �����ϰ� ���ڸ� ó���Ѵٴ� �����Ͽ� ����� �� �ִ� �ڵ��̴�.

���� :
std::string _content : CSV �� ��� ������ ������ ���ڿ� �����̴�.

����� :
std::vector<std::vector<std::string>>
*/

/*
std::vector<std::vector<std::string>> readCSVString(std::string& _content) {
    std::string sBuffer;
    std::vector<std::string> m_vsCell;

    if (_content.empty())
        perror("�ش� �ϴ� CSV ���ڿ��� ������ �ֽ��ϴ�.");
    else {
        for(int i = 0; i < _content.size(); i++){}
    }
}
*/

/*
// locale ���� ���ķ� UTF-8 ������ �д� ����̴�.
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
C6262 : �Լ����� '20032' ����Ʈ�� ������ ����ϴµ� �� ũ�Ⱑ  /analyze:stacjsuze '16384'��(��) �ʰ��մϴ�.
�Ϻ� �����͸� ������ �̵��Ͻʽÿ�.
�������� �ʾƵ� ����� �����ϴ�.
buffer[10000] -> buffer[5000] 
*/

// fopen �� ���� ��� �ɼǿ� ���ڵ� Ÿ�� ������ �б�
void CExcel::SetCSV_utf8(std::string _path) {
    wchar_t wcASCII;    //  wchar_t ���� ASCII �ڵ带 ǥ���� �����̴�.
    std::string sBuffer;    // ���Ϳ� �ֱ� �� ���ڿ��� �����ص� �����̴�.

    FILE* stream;

    if (NULL == (stream = fopen(_path.c_str(), "rt+,ccs=UTF-8"))) {
        /*
        C6284: ��ü�� _Param_(2)���� ���޵Ǿ����ϴ�. 'printf'�� ���� ȣ�⿡�� ���ڿ��� �ʿ��մϴ�.
        ���� ����: 'class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >'
        */
        printf("Unable to open: %s \n", _path);
        exit(1);
    }

    errno = 0;
    while (WEOF != (wcASCII = fgetwc(stream))) {
        if (wcASCII == 10)
        {
            // ���� �迭�� ���� �迭 ���Ϳ� �߰��մϴ�.
            m_vsCell.push_back(sBuffer);
            // ���� �迭 ���͸� 2 ���� ���Ϳ� �߰��մϴ�.
            m_vvsExcel.push_back(m_vsCell);
            // �ִ� �� ũ�⸦ �����մϴ�.
            if (m_unColumn < static_cast<unsigned int>(m_vsCell.size() - 1))
                m_unColumn = static_cast<unsigned int>(m_vsCell.size() - 1);
            // ���� �迭 ���͸� �ʱ�ȭ�մϴ�.
            m_vsCell.clear();
            // �ӽ� ���ڿ��� �ʱ�ȭ�մϴ�.
            sBuffer = "";
            // �ִ� �� ũ�⸦ �����մϴ�.
            m_unRow++;
        }
        // ��ǥ(�ƽ�Ű�ڵ� 44)�� ���
        else if (wcASCII == 44)
        {
            // ���� �迭�� ���� �迭 ���Ϳ� �߰��մϴ�.
            m_vsCell.push_back(sBuffer);
            // �ӽ� ���ڿ��� �ʱ�ȭ �մϴ�.
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

    /* 
    �� �� �б⵵ �����ϴ�.
    wchar_t buffer[10000];
    fwscanf(f, L"%ls", buffer); // scanf �������� �б�
    fgetws(buffer, 1000, f);    // �� �� �б� (gets w ����)
    printf("%ls", buffer);
    */
}
