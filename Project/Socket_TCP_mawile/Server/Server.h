#pragma once
#pragma warning(disable:4996)

#include <iostream> 
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::string;
using std::invalid_argument;
using std::out_of_range;

#include <winsock2.h> 
#pragma comment(lib, "ws2_32")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define BUF_SIZE 4096
#define IPADDRESS "127.0.0.1"
#define PACKET_SIZE 1024

void ServerBasicForm();
void Server_1();