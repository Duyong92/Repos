#include "Header.h"
#include <iostream>
#include <thread>
#include <Windows.h>

int main() {
	std::thread t1(LoadServer);
	
	Sleep(100);

	std::thread t2(LoadClient);

	// A,B Client.
	// A -> B csv File 
	// A csv File ��θ� ģ��.
	// B -> A 

	t1.join();
	t2.join();
}