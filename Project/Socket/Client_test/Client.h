#pragma once
#ifndef CLIENT_H
#define CLIENT_H
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma warning(disable:4996)

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32")

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;
using std::to_string;
using std::invalid_argument;
using std::out_of_range;

#include <chrono>
using std::chrono::seconds;

#include <thread>
using std::this_thread::sleep_for;
//#include <queue>

#define SERVER_PORT 11235
#define BUF_SIZE 4096
#define QUEUE_SIZE 10
#define IPADDRESS "127.0.0.1"

string currentTime();

#endif