#include "System_test.h"

using namespace std;

int sys() 
{
	//system("ls");
	//system("top");

	auto ret = system(nullptr);
	if (ret != 0)
		cout << "shell is available on the system!" << endl;
	else
		cout << "shell is not available on the system!" << endl;

	return EXIT_SUCCESS;
}