#include "Excel.h"

/*
    string ��ü�� �ִ� ���̴� 42�������� �������� �޸� �Ѱ������ �� �� �ִٰ� �Ѵ�.
    CSV ���� ������ �޸� ��뷮�� ������ �� ������, ��뷮 �����Ϳ��� �������� ���� �ڵ��̴�.
 
    ���� : 
    const char* _directory : ��� �ɸ��� �����ͷ� �޴� ������ ����̴�.
 
    ����� :
    std::string
*/

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

// fopen �� ���� ��� �ɼǿ� ���ڵ� Ÿ�� ������ �б�
void CExcel::SetCSV_utf8(std::string _path) {
    wchar_t wcASCII;    //  wchar_t ���� ASCII �ڵ带 ǥ���� �����̴�.
    std::string sBuffer;    // ���Ϳ� �ֱ� �� ���ڿ��� �����ص� �����̴�.

    FILE* stream;

    if (NULL == (stream = fopen(_path.c_str(), "rt+,ccs=UTF-8"))) {
        printf("Unable to open: %s\n", _path);
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
}
