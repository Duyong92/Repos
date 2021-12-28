#ifdef _DEBUG
	#define _DEBUG_WAS_DEFINED 1
#undef _DEBUG
#endif

#include <Python.h>

#ifdef _DEBUG_WAS_DEFINED
	#define _DEBUG 1
#endif

int main(void)
{
	Py_Initialize();
	if (Py_IsInitialized())
	{
		const char* str1 = "tmp2 = 20\nprint(tmp2)";
		PyRun_SimpleString("print(\'Hello, Python\')");
		PyRun_SimpleString("tmp1 = 10");
		PyRun_SimpleString("print(tmp1)");
		PyRun_SimpleString(str1);

		printf("\n");

		PyRun_SimpleString("from time import time, ctime\n"
			"print('Today is ', ctime(time()))\n");
		Py_Finalize();
	}

	return 0;
}