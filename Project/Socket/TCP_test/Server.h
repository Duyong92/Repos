#pragma once
#ifndef SERVER_H
#define SERVER_H
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <stdio.h>
#pragma comment(lib,"ws2_32")

#include <iostream>
using std::cout;
using std::endl;

#include <random>
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

//#include <iphlpapi.h>
#include <string>
using std::out_of_range;
using std::invalid_argument;

#include <chrono>
#include <thread>

#define SERVER_PORT 11235
#define BUF_SIZE 4096
#define QUEUE_SIZE 10
#define IPADDRESS "127.0.0.1"

#endif