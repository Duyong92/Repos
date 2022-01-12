#include <iostream>
#include "CXl.h"

int main() {
	CXl xl;
	xl.Open();
	xl.SetActiveSheet(1);
	Sleep(5000);
	return 0;
}