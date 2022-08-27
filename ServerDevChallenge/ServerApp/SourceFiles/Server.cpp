
#include "../HeaderFiles/Server.h"

Server::Server() : ServerInterface()
{
    std::cout << "Hello World" << std::endl;
}

Server::~Server()
{
    std::cout << "Closing ServerSocket File Descriptor" << std::endl;
    close(Server::serverSocket);
    if (map.size() > 0)
        for (std::map<int, Server::ClientInfo *>::iterator it = Server::map.begin(); it != Server::map.end(); ++it)
        {
            std::cout << "Closing ClientSocket File Descriptor, Client:" << it->second->alias << std::endl;
            close(it->first);
        }
}

void Server::SendMessage(const std::string message, const int clientSocket) const
{
    send(clientSocket, message.c_str(), strlen(message.c_str()), 0);
    return;
}
void Server::GenerateGameCard(std::vector<int> &gameCard)
{
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        gameCard[i] = rand() % 50;
    }

    return;
}
const std::vector<int> Server::GenerateDraw()
{

    std::vector<int> g1;
    return g1;
}

typedef struct thread_args_1
{
    Server *server;
    int clientSocket;
} thread_args_1;

void *Start(void *ptr)
{
    thread_args_1 *args = (thread_args_1 *)ptr;
    Server *server = args->server;
    int clientSocket = args->clientSocket;

    std::vector<int>
        gameCard{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    PrintGameCard(gameCard);
    server->GenerateGameCard(gameCard);
    PrintGameCard(gameCard);

    Server::ClientInfo clientInfo = {
        .clientSocket = clientSocket,
        .status = Status::CLIENT_CONNECTION_ESTABLISHED,
        .gameCard = gameCard,
        .alias = RandomString(10)};

    server->map.insert(std::pair<int, Server::ClientInfo *>(clientSocket, &clientInfo));
    std::cout << "New Player " << clientInfo.alias << std::endl;
    server->SendMessage(text::CONNECT_EVENT.append(delimiter), clientSocket);
    char buffer[1024] = {0};
    for (;;)
    {
        memset(&buffer[0], 0, sizeof(buffer));
        read(clientSocket, buffer, 1024);

        std::string buffer_parsed(buffer);
        size_t pos = 0;
        std::string token, action, content;

        if ((pos = buffer_parsed.find(delimiter)) != std::string::npos)
        {
            token = buffer_parsed.substr(0, pos);
            action = token;
            buffer_parsed.erase(0, pos + delimiter.length());
        }
        content = buffer_parsed;

        std::string reply;
        switch (str2int(action))
        {
        case GAME_REQUEST:
            std::cout << "{GAME_REQUEST}" << std::endl;
            // action
            reply = text::GAME_REQUEST_REPLY;
            // content
            reply.append(delimiter);
            reply.append(PrintGameCard(gameCard));
            server->SendMessage(reply, clientSocket);
            clientInfo.status = Status::CLIENT_PLAYING;

            break;

        case ACKNOWLEDGE_CARD_RECEIVED:
            std::cout << "{ACKNOWLEDGE_CARD_RECEIVED} Client " << clientInfo.alias << " confirmed  the reception of the game card" << std::endl;
            clientInfo.status = Status::CLIENT_READY_TO_PLAY;

            break;
        case NUMBER_IN_CARD:
            std::cout << "{NUMBER_IN_CARD} Client " << clientInfo.alias << " is one step more closer to the victory " << std::endl;
            server->SendMessage(text::NUMBER_IN_CARD_REPLY.append(delimiter), clientSocket);
            clientInfo.status = Status::CLIENT_PLAYING;

            break;
        case NUMBER_NOT_IN_CARD:
            std::cout << "{NUMBER_NOT_IN_CARD} Client " << clientInfo.alias << " is one step more closer to the victory " << std::endl;
            server->SendMessage(text::NUMBER_NOT_IN_CARD_REPLY.append(delimiter), clientSocket);
            clientInfo.status = Status::CLIENT_PLAYING;
            break;
        case MISSING_PIECES:
            std::cout << "{MISSING_PIECES} Client " << clientInfo.alias << " has " << content << " pieces missing" << std::endl;
            if (stoi(content) == 0)
            {
                reply = text::WON;
                reply.append(delimiter);
                server->SendMessage(reply, clientSocket);
                break;
            }
            else
            {
                server->SendMessage(text::MISSING_PIECES_REPLY.append(delimiter), clientSocket);
            }
            clientInfo.status = Status::CLIENT_READY_TO_PLAY;
            break;
        case WON_REPLY:
            std::cout << "{WON_REPLY} Client " << clientInfo.alias << " WON " << std::endl;
            clientInfo.status = Status::CLIENT_PLAYING;

            exit(0);
            break;
        default:
            std::cout << "InValide Action '" << action << "'" << std::endl;
            exit(0);

            break;
        }
    }
}

void *DrawnNumbers(void *ptr)
{

    set<int> alreadyDrawn;

    int i = 0;
    thread_args_1 *args = (thread_args_1 *)ptr;
    Server *server = args->server;

    std::string str;
    std::getline(std::cin, str);

    for (;;)
    {

        if (server->map.size() > 0 && str == "ready")
        {

            sleep(1);
            bool flag = true;
            for (std::map<int, Server::ClientInfo *>::iterator it = server->map.begin(); it != server->map.end(); ++it)
            {
                Server::ClientInfo *ci = (it->second);
                // ci->status = Status::CLIENT_READY_TO_PLAY;
                if (ci->status != Status::CLIENT_READY_TO_PLAY)
                {

                    flag = false;
                }
            }

            if (flag)
            {
                int drawnNumber = -1;
                bool is;

                do
                {
                    is = (alreadyDrawn.find(drawnNumber) != alreadyDrawn.end());
                    srand(time(NULL));
                    drawnNumber = rand() % 50;
                } while (is);

                alreadyDrawn.insert(drawnNumber);

                for (std::map<int, Server::ClientInfo *>::iterator it = server->map.begin(); it != server->map.end(); ++it)
                {

                    int clientSocket = it->second->clientSocket;
                    std::string reply = text::BALL_EVENT;
                    // content
                    reply.append(delimiter);
                    reply.append(std::to_string(drawnNumber));
                    server->SendMessage(reply, clientSocket);
                }
            }
        }
    }
}

void Server::MainLoop()
{
    pthread_t threads[100];
    int i = 0;
    for (;;)
    {
        int clientSocket = this->Server::WaitConnection();
        try
        {
            thread_args_1 t_args;
            t_args.clientSocket = clientSocket;
            t_args.server = this;

            if (pthread_create(&threads[i++], NULL, Start, (void *)&t_args) != 0)
                printf("Failed to create thread\n");
            if (pthread_create(&threads[i++], NULL, DrawnNumbers, (void *)&t_args) != 0)
                printf("Failed to create thread\n");
        }
        catch (...)
        {
            std::cout << "Error\n";
        }
        std::cout << "Another interaction\n";
    }
}