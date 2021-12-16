#include "Header_15_1.h"

void Fibonacci() {
	long long int bef = 1, cur = 1;

	// 물론 100 번째 피보나치 항을 구한다면, int 오버플로우가 나겠지만 일단 그
	// 점은 여기서 무시하도록 합시다.
	for (int i = 0; i < 98; i++) {
		long long int temp = cur;
		cur = cur + bef;
		bef = temp;
	}
	std::cout << "F100: " << cur << std::endl;
}

void DownloadMap() {
	// 다운 받으려는 웹사이트와 내용을 저장하는 맵
	std::map<std::string, std::string> url_and_content;
	for (auto itr = url_and_content.begin(); itr != url_and_content.end(); ++itr) {
		const std::string& url = itr->first;

		// download 함수는 인자로 전달받은 url 에  있는 사이트를 다운 받아 리턴한다.
		itr->second = download(url);
	}
}