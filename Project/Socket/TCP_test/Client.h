#pragma once
#ifndef CLIENT_H
#define CLIENT_H
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32")

#include <iostream>
using std::cout;
using std::endl;

#include <chrono>
#include <string>

#include <queue>
#include <thread>

#define SERVER_PORT 11235
#define BUF_SIZE 4096
#define QUEUE_SIZE 10
#define IPADDRESS "127.0.0.1"

#endif