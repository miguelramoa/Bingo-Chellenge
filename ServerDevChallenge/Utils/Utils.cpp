
#include "./Utils.h"

std::string RandomString(int ch)
{
    srand(time(NULL));
    char alpha[ch_MAX] = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z'};
    std::string result = "";
    for (int i = 0; i < ch; i++)
        result = result + alpha[rand() % ch_MAX];

    return result;
}

std::string PrintGameCard(std::vector<int> gameCard)
{
    std::ostringstream oss;

    if (!gameCard.empty())
    {
        // Convert all but the last element to avoid a trailing ","
        std::copy(gameCard.begin(), gameCard.end() - 1,
                  std::ostream_iterator<int>(oss, ","));

        // Now add the last element with no delimiter
        oss << gameCard.back();
    }

    return oss.str();
}

char *make_copy(const char *s)
{
    std::size_t sz = std::strlen(s);
    char *p = new char[sz];
    std::strcpy(p, s);
    return p;
}
const int str2int(const std::string &s)
{
    int x = -1;
    if (!strcmp(s.c_str(), text::GAME_REQUEST.c_str()))
    {
        x = GAME_REQUEST;
    }
    else if (!strcmp(s.c_str(), text::ACKNOWLEDGE_CARD_RECEIVED.c_str()))

    {
        x = ACKNOWLEDGE_CARD_RECEIVED;
    }
    else if (!strcmp(s.c_str(), text::NUMBER_IN_CARD.c_str()))

    {
        x = NUMBER_IN_CARD;
    }
    else if (!strcmp(s.c_str(), text::MISSING_PIECES.c_str()))

    {
        x = MISSING_PIECES;
    }
    else if (!strcmp(s.c_str(), text::WON.c_str()))

    {
        x = WON;
    }

    else if (!strcmp(s.c_str(), text::CONNECT_EVENT.c_str()))

    {
        x = CONNECT_EVENT;
    }

    else if (!strcmp(s.c_str(), text::GAME_REQUEST_REPLY.c_str()))

    {
        x = GAME_REQUEST_REPLY;
    }

    else if (!strcmp(s.c_str(), text::NUMBER_IN_CARD_REPLY.c_str()))

    {
        x = NUMBER_IN_CARD_REPLY;
    }

    else if (!strcmp(s.c_str(), text::MISSING_PIECES_REPLY.c_str()))

    {
        x = MISSING_PIECES_REPLY;
    }

    else if (!strcmp(s.c_str(), text::WON_REPLY.c_str()))

    {
        x = WON_REPLY;
    }

    else if (!strcmp(s.c_str(), text::BALL_EVENT.c_str()))

    {
        x = BALL_EVENT;
    }

    else if (!strcmp(s.c_str(), text::NUMBER_NOT_IN_CARD.c_str()))

    {
        x = NUMBER_NOT_IN_CARD;
    }

    else if (!strcmp(s.c_str(), text::NUMBER_NOT_IN_CARD_REPLY.c_str()))

    {
        x = NUMBER_NOT_IN_CARD_REPLY;
    }

    return x;
}