#pragma once

#include <time.h> /* time */
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <set>

#include "./ServerInterface.h"
#include "../SourceFiles/ServerInterface.cpp"

#include "../../Commons/Commons.h"
#include "../../Utils/Utils.h"
#include "../../Utils/Utils.cpp"
class Server : public ServerInterface
{

public:
    typedef struct ClientInfo
    {

    public:
        int clientSocket;
        int holdedNumbers;
        Status status;
        std::vector<int> gameCard;
        std::string alias;

    } ClientInfo;

    std::map<int, ClientInfo*> map;
    Server();
    ~Server();
    // static void Start(Server serverSingleton, int clientSocket);
    void MainLoop();
    void SendMessage(const std::string message, const int clientSocket) const;
    void GenerateGameCard(std::vector<int> &gameCard);

    const std::vector<int> GenerateDraw();
};
