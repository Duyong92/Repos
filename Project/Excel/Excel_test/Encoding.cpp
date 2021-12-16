#include "Excel.h"

#include <cstddef>
#include <locale>
#include <cstdlib>

/*
	character 로는 모자른 메모리 때문에 출력하지 못하는 언어들을 wide string으로 저장하여 출력한다.
	reference : https://movahws.tistory.com/43

	인자 :
	void

	결과값 :
	void
*/
void Encoding_test() {
	const std::wstring texts[] = {
		L"Ñá", //Spanish
			L"forêt intérêt",  //French
			L"Gesäß",  //German
			L"取消波蘇日奇諾",  //Chinesse
			L"日本人のビット",  //Japanese
			L"немного русский",  //Russian
			L"ένα κομμάτι της ελληνικής",  //Greek
			L"ਯੂਨਾਨੀ ਦੀ ਇੱਕ ਬਿੱਟ",  //Punjabi
			L"کمی از ایران ", //Persian
			L"కానీ ఈ ఏమి నరకం ఉంది?", //Telugu
			L"Но какво, по дяволите, е това?" //Bulgarian
	};
	std::locale::global(std::locale(""));
	std::wcout.imbue(std::locale());

	// 그리스, 푼자비, 페르시안, 텔루구, 벨기어는 사용하지 못한다.
	for (size_t i = 0; i < 11; ++i) {
		std::cout << i << "번째: ";
		std::wcout << texts[i] << std::endl;
	}
		
}

void Encoding_test2() {
	std::wcin.imbue(std::locale("korean"));
	std::wcout.imbue(std::locale("korean"));

	const int bottom = 0;
	const int top = 100;
	int source;
	
	for (;;) { // infinite loop
		std::wcout << bottom << L" 부터" << top;
		std::wcout << L"까지의 자연수를 입력해주세요." << std::endl;
		std::wcin >> source;

		if (source >= bottom && source <= top)
			break;
		else
			std::wcout << L"입력 형식이 잘못 되었습니다. 다시 입력해주세요." << std::endl;
	}

	std::wstring unit(L"십백천만");
	std::wstring num(L"일이삼사오육칠팔구");
	std::wstring output;
	for (int i = source, j = -1; ; i /= 10, ++j) {	// no condition
		if (j == -1 && (i % 10 != 0))
			output = num.substr((i % 10) - 1, 1);
		else if (i % 10 != 0)
			output = num.substr((i % 10) - 1, 1) + unit.substr(j, 1) + output;
		else if (source == 0)
			output = L"영";
		else
			;	// do nothing

		if (i < 10)
			break;
	}

	std::wcout << output << std::endl;
}