#include "Header_15_1.h"

void Fibonacci() {
	long long int bef = 1, cur = 1;

	// ���� 100 ��° �Ǻ���ġ ���� ���Ѵٸ�, int �����÷ο찡 �������� �ϴ� ��
	// ���� ���⼭ �����ϵ��� �սô�.
	for (int i = 0; i < 98; i++) {
		long long int temp = cur;
		cur = cur + bef;
		bef = temp;
	}
	std::cout << "F100: " << cur << std::endl;
}

void DownloadMap() {
	// �ٿ� �������� ������Ʈ�� ������ �����ϴ� ��
	std::map<std::string, std::string> url_and_content;
	for (auto itr = url_and_content.begin(); itr != url_and_content.end(); ++itr) {
		const std::string& url = itr->first;

		// download �Լ��� ���ڷ� ���޹��� url ��  �ִ� ����Ʈ�� �ٿ� �޾� �����Ѵ�.
		itr->second = download(url);
	}
}