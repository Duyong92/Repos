#include "System_test.h"

int System_test_1(int argc, char* argv[])
{
	int ret = system("ls -a");
	return 0;
}