#include "../HeaderFiles/Client.h"

using namespace std;

/* The class constructor
 * The Constructor will create a socket for the instantiated client
 * and try to connect to the server.
 * If anything fails the constructor throws a runtime_error exception.*/
Client::Client()
{
    if (CreateSocket() && ConnectToServer())
    {
        std::cout << "Initiating MainLoop" << std::endl;
        this->gameCard = std::vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    }
    else
    {
        throw runtime_error("There was a problem creating the socket or connecting to the server.");
    }
}

Client::~Client()
{
    std::cout << "Closing Socket File Descriptor" << std::endl;
    close(clientSocket);
}

/* This method is responsible for a socket creation
 * it uses socket() from socket programming library
 * AF_NET: it means we're using IPv4
 * SOCK_STREAM: connection type. In this case, it means TCP
 * 0: it means we're using IP protocol
 * returns true if the socket is created successfully and false if it falis to create the socket*/
bool Client::CreateSocket()
{
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {

        return false;
    }
    return true;
}

/* This method connects to the server based on the client's port and ip members
 * returns true if the connection is successful and false if it fails*/
bool Client::ConnectToServer()
{
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    int connectRes = connect(clientSocket, (sockaddr *)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        cout << "Could not send to server!\n";
        return false;
    }
    return true;
}
void Client::SendMessage(text::Type message) const
{
    send(clientSocket, message.c_str(), strlen(message.c_str()), 0);
    return;
}

void Client::MainLoop()
{
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

        string reply;
        switch (str2int(action))
        {
        case CONNECT_EVENT:
            std::cout << "{CONNECT_EVENT} Connect to the Server... Sending GAME_REQUEST" << std::endl;
            SendMessage(text::GAME_REQUEST.append(delimiter));
            break;
        case GAME_REQUEST_REPLY:
        {
            char *token = strtok(make_copy(content.c_str()), ",");
            int i = 0;
            while (token != NULL)
            {
                gameCard[i] = stoi(token);
                token = strtok(NULL, ",");
                i++;
            }
            std::cout << "{GAME_REQUEST_REPLY} Receving my GameCard \n\t " << PrintGameCard(gameCard) << std::endl;
            SendMessage(text::ACKNOWLEDGE_CARD_RECEIVED.append(delimiter));
        }

        break;
        case BALL_EVENT:
            std::cout << "{BALL_EVENT} Receiving a Ball Event. Drawn number is: [" << content << "]" << std::endl;
            if (std::find(gameCard.begin(), gameCard.end(), stoi(content)) != gameCard.end())
            {
                holdedNumbers++;
                std::cout << "I Have the drawn number !!! HoldedNumbers{" << holdedNumbers << "}" << std::endl;
                SendMessage(text::NUMBER_IN_CARD.append(delimiter));
            }
            else
            {
                std::cout << "I Do not have the drawn number !!! HoldedNumbers{" << holdedNumbers << "}" << std::endl;
                SendMessage(text::NUMBER_NOT_IN_CARD.append(delimiter));
            }
            sleep(1);
            // action
            reply = text::MISSING_PIECES;
            // content
            reply.append(delimiter);
            reply.append(std::to_string(10 - holdedNumbers));
            SendMessage(reply);

            break;

        case NUMBER_IN_CARD_REPLY:
            std::cout << " {NUMBER_IN_CARD_REPLY} Server knows how much left for my victory" << std::endl;

            break;
        case NUMBER_NOT_IN_CARD_REPLY:
            std::cout << "{NUMBER_NOT_IN_CARD_REPLY} Server knows how much left for my victory" << std::endl;

            break;
        case MISSING_PIECES_REPLY:
            std::cout << "{MISSING_PIECES_REPLY}" << std::endl;

            break;
        case WON:
            std::cout << "{WON}" << std::endl;
            SendMessage(text::WON.append(delimiter));
            break;
        default:
            std::cout << "InValide Action '" << action << "'" << std::endl;
            exit(0);
            break;
        }
    }
}
