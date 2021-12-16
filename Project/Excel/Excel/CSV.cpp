#include "Excel.h"

/*
    CSV ������ ANSI ��� �����ϰ� ����ϴ� �Լ��̸�, character ���·� ���ڸ� �޾� ASCII �� ���Ͽ� ���� ������.
    �� �� �ȿ� '\'','\,','\n' �� ���� �����ϴ� Ư�����ڴ� �������� ���Ѵ�.
    ���������� CExcel class �� 2���� ���Ϳ� �����͸� �Է��Ѵ�.

    ���� :
    std::string _path : ���ڿ��� �޴� ������ ����̴�.

    ����� :
    void
*/
void CExcel::SetCSV(std::string _path) {
    char szASCII;   // char Ÿ������ ASCII �ڵ带 �޴� �����̴�.
    std::string sBuffer;    // ���Ϳ� �ֱ� �� ���ڿ��� �����ص� �����̴�.

    FILE* stream;
    
    if (NULL == (stream = fopen(_path.c_str(), "rt"))) {
        std::cout << "Unable to open: " << _path << std::endl;
        exit(1);
    }

    errno = 0;
    while (EOF != (szASCII = fgetc(stream))) {
        // ���� ����(�ƽ�Ű�ڵ� 10)�� ���
        if (szASCII == 10) {
            std::cout << "sBuffer: " << sBuffer << std::endl;
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
        else if (szASCII == 44) {
//            std::cout << "sBuffer: " << sBuffer << std::endl;
            // ���� �迭�� ���� �迭 ���Ϳ� �߰��մϴ�.
            m_vsCell.push_back(sBuffer);
            // �ӽ� ���ڿ��� �ʱ�ȭ �մϴ�.
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
/*
    CSV ������ UTF-8 �̶�� �����ϰ� ����ϴ� �Լ��̴�.
    wide character �� ���ڸ� ������, ���������� CExcel class �� 2���� ���Ϳ� �����͸� �Է��Ѵ�.
    reference : https://www.ibm.com/docs/ko/i/7.3?topic=functions-fgetwc-read-wide-character-from-stream#fgetwc

    ���� :
    std::string _path : ���ڿ��� �޴� ������ ����̴�.

    ����� :
    void
*/
void CExcel::SetCSV_utf8(std::string _path) {
    wchar_t wcASCII;    //  wchar_t Ÿ������ ASCII �ڵ带 �޴� �����̴�.
    std::string sBuffer;    // ���Ϳ� �ֱ� �� ���ڿ��� �����ص� �����̴�.

    FILE* stream;

    if (NULL == (stream = fopen(_path.c_str(), "rt+,ccs=UTF-8"))) {
        std::cout << "Unable to open: " << _path << std::endl;
        exit(1);
    }

    errno = 0;
    while (WEOF != (wcASCII = fgetwc(stream))) {
        if (wcASCII == 10) {
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
        else if (wcASCII == 44) {
            // ���� �迭�� ���� �迭 ���Ϳ� �߰��մϴ�.
            m_vsCell.push_back(sBuffer);
            // �ӽ� ���ڿ��� �ʱ�ȭ �մϴ�.
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
}
