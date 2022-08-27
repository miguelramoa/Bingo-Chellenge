#pragma once

std::string delimiter = ">=";

namespace text
{
    typedef std::string Type;
    Type GAME_REQUEST = "GAME_REQUEST";
    Type ACKNOWLEDGE_CARD_RECEIVED = "ACKNOWLEDGE_CARD_RECEIVED";
    Type NUMBER_IN_CARD = "NUMBER_IN_CARD";
    Type MISSING_PIECES = "MISSING_PIECES";
    Type WON = "WON";
    Type CONNECT_EVENT = "CONNECT_EVENT";
    Type GAME_REQUEST_REPLY = "GAME_REQUEST_REPLY";
    Type NUMBER_IN_CARD_REPLY = "NUMBER_IN_CARD_REPLY";
    Type MISSING_PIECES_REPLY = "MISSING_PIECES_REPLY";
    Type WON_REPLY = "WON_REPLY";
    Type BALL_EVENT = "BALL_EVENT";
    Type NUMBER_NOT_IN_CARD = "NUMBER_NOT_IN_CARD";
    Type NUMBER_NOT_IN_CARD_REPLY = "NUMBER_NOT_IN_CARD_REPLY";
}
enum Status
{
    CLIENT_CONNECTION_ESTABLISHED,
    CLIENT_READY_TO_PLAY,
    CLIENT_PLAYING,
    CLIENT_WON,
    CLIENT_LOST
};

enum Messages
{
    GAME_REQUEST,
    ACKNOWLEDGE_CARD_RECEIVED,
    NUMBER_IN_CARD,
    MISSING_PIECES,
    WON,
    CONNECT_EVENT,
    GAME_REQUEST_REPLY,
    NUMBER_IN_CARD_REPLY,
    MISSING_PIECES_REPLY,
    WON_REPLY,
    BALL_EVENT,
    NUMBER_NOT_IN_CARD,
    NUMBER_NOT_IN_CARD_REPLY
};
