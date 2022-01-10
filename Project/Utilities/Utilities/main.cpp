#include <iostream>
#include <string>
#include "Convert.h"

using namespace std;

int main()
{
	const char* pbz = "test";
	
	MessageBox(NULL, pbzPSZ(pbz), pbzPSZ("Error"), 0x10010);

	return 0;
}