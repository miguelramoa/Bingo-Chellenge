#pragma once
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <string>
#include <vector>
#include <algorithm>
#include "../../Commons/Commons.h"
#include "../../Utils/Utils.h"
#include "../../Utils/Utils.cpp"

/* This is the Client class, it should implement a client that connects to the server app
 * You should complete the class implementation in order to complete the exercise.
 * Existing methods and members should not be changed unless you feel there is a better way to implement the class */

class Client
{
	int clientSocket;
	int holdedNumbers;
	const int port = 54000;					   // server's app port
	const std::string ipAddress = "127.0.0.1"; // loopback address (local machine)
	std::vector<int> gameCard;

public:
	Client();
	~Client();
	void MainLoop();

private:
	bool CreateSocket();
	bool ConnectToServer();
	void SendMessage(text::Type message) const;
};
