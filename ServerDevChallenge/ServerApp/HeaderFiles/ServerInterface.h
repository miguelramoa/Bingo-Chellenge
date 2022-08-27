#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <sstream>

/* This is the ServerInterface class, it defines the implementation of a Server that should accept Clients
 * and handle the draw that is explained in the exercise.
 * The existing methods and members should be maintained unchanged as best you can.
 * Your code should be added in order to complete the exercise. */

class ServerInterface
{

public:
	int serverSocket;
	ServerInterface();
	virtual ~ServerInterface();
	virtual int WaitConnection();

private:
	virtual bool CreateSocket();
	virtual void BindSocketAndListen();

public:
	/* This method should be used to send a message from the server to a client
	 * message: The message to be sent to the client
	 * clientSocket: The socket where the message should be sent */
	virtual void SendMessage(const std::string message, const int clientSocket) const = 0;

	/* This method should be used to generate a game card as defined in the exercise
	 * gameCard: The game card that should be generated */
	virtual void GenerateGameCard(std::vector<int> &gameCard) = 0;

	/* This method should be used to generate the game draw as defined in the exercise.
	 * The draw should be of 50 numbers (1 - 50) in a random order.
	 * return: The order of the draw with no repeated elements */
	virtual const std::vector<int> GenerateDraw() = 0;
};
