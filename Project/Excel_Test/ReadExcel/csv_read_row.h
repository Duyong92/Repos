#pragma once

using namespace std;

vector<string> csv_read_row(istream& file, char delimiter)
{
    // ���ڿ��� ������ ��Ʈ���̴�.
    stringstream ss;

    // Ư������ ���θ� ���� bool �����̴�.
    bool inquotes = false;

    vector<string> row;//relying on RVO

    while (file.good())
    {
        // ù char �� �����´�.
        char c = file.get();
        // inquotes �� FALSE �̸鼭 �ֵ���ǥ�� ��� inquotes �� TRUE �� ��ȯ�Ѵ�.
        if (!inquotes && c == '"')
        {
            inquotes = true;
        }
        // inquotes �� TRUE �̸鼭 �ֵ���ǥ�� ���,
        else if (inquotes && c == '"')
        {
            /* 
                istream::peek
                ���� - ����
                ���ϰ� - �� ���� ������ ���� �����Ѵ�. 
                ������ �߻� �ÿ� �� �Լ��� EOF �� �����ϸ�, 
                ���� ���� �÷��׸� ������ ���� ��Ȳ�� �°� �����ϰ� �ȴ�.

                eofbit - �۾� �� ���ڵ��� ���� �����Ͽ��� ��
                failbit -
                badbit - �� ���� �ϵ� ���� �ٸ� ������ �߻� ��

                ios::exceptions �Լ���� �����Ǿ��ٸ�, ios_bas::failure �� throw �ȴ�.
                https://modoocode.com/194
            */
            if (file.peek() == '"')
            {
                ss << (char)file.get();
            }
            // �ֵ���ǥ�� �ƴϱ� ������ inquotes �� FALSE �� ��ȯ�Ѵ�.
            else
            {
                inquotes = false;
            }
        }
        // inquotes �� FALSE �̸鼭 �������� ���,
        else if (!inquotes && c == delimiter)
        {
            /*
                vector::push_back
                void push_back(const T& x);
                ���� ���� ���Ҹ� �߰��Ѵ�.
                ���� - x: ���� �߰� �� ���ҿ� ����� ����
                       T:  ���Ϳ� ����Ǿ� �ִ� ���ҵ��� Ÿ��
                ���ϰ� - ����

                ���� ���Ҵ��� �߻��Ѵٸ� �̴� Allocator::allocate() �� �̿��ؼ� ����Ǵµ�,
                ���ܸ� ����(throw) �� �ִ�. 
                (����Ʈ �Ҵ����� ��� ���� ��û�� �Ҵ��� �������� ���� ��� bad_alloc �� ��������)
                https://modoocode.com/185
            */
            // �� ���ڿ��� row�� �־��ش�.
            row.push_back(ss.str());
            // ���ڿ� ��Ʈ���� �ֵ���ǥ�� �ʱ�ȭ���ش�.
            ss.str("");
        }
        // inquotes �� FALSE �̸鼭 �ٹٲ��� ���,
        else if (!inquotes && (c == '\r' || c == '\n'))
        {
            // ���� ���ڵ� �ٹٲ��� ��� �ٹٲ��� �־��ش�.
            if (file.peek() == '\n') { file.get(); }
            // �� ���ڿ��� row�� �־��ش�.
            row.push_back(ss.str());
            // row�� ����Ѵ�.
            return row;
        }
        else
        {
            // ���ڿ� ��Ʈ���� ���ڸ� ���� �ִ´�.
            ss << c;
        }
    }
}