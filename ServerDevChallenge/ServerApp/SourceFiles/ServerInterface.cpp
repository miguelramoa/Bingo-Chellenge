#include "../HeaderFiles/ServerInterface.h"

using namespace std;

ServerInterface::ServerInterface()
{
    if (CreateSocket())
    {
        BindSocketAndListen();
        std::cout << "Bind Ok " << std::endl;
    }

    else
        throw runtime_error("Couldn't create server socket");
}

ServerInterface::~ServerInterface()
{
}

/* This method is responsible for a socket creation
 * it uses socket() from socket programming library
 * AF_NET: it means we're using IPv4
 * SOCK_STREAM: connection type. In this case, it means TCP
 * 0: it means we're using IP protocol */
bool ServerInterface::CreateSocket()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0); // Create a socket

    // if socket() method doesn't return a positive value, it means something bad happen in socket creation process
    if (serverSocket == -1)
    {
        // in that case, it displays an error messange and return false
        cerr << "Can't create a socket! Quitting" << endl;
        return false;
    }
    else
        // if there's no problem creating a new socket, return true
        return true;
}

/* This method is responsible for associating a local IP address and the server socket */
void ServerInterface::BindSocketAndListen()
{
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    bind(serverSocket, (sockaddr *)&hint, sizeof(hint));

    listen(serverSocket, SOMAXCONN); // Start listening for connections on that socket
}

/* This method is responsible for handling socket connection.
 * It blocks processing until a connection is available,
 * socket: socket we want to associate with a local IP adress*/
int ServerInterface::WaitConnection()
{
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    std::cout << "Waiting new connection at:" << serverSocket << std::endl;
    // Accepts pending connection and when it happens, it creates a new socket, returning it's descriptor
    int clientSocket = accept(serverSocket, (sockaddr *)&client, &clientSize);

    // TODO : Should we include this?
    char host_c[NI_MAXHOST];    // Client's remote name
    char service_c[NI_MAXSERV]; // port the client is connect on

    memset(host_c, 0, NI_MAXHOST);
    memset(service_c, 0, NI_MAXSERV);
    // displaying connection status
    auto status = getnameinfo((sockaddr *)&client, sizeof(client), host_c, NI_MAXHOST, service_c, NI_MAXSERV, 0);

    if (status == 0)
    {

        cout << "Client connected:" << endl;
        cout << host_c << " connected on port " << ntohs(client.sin_port) << endl;
    }
    else
    {
        cout << "An error occured with code " << to_string(status) << endl;
    }

    return clientSocket;
}
