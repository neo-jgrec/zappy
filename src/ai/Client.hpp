/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Client.hpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "Bot.hpp"

class Client
{
public:
    Client(const std::string &host, const std::string &teamName, int port);
    ~Client();

    void run();

private:
    std::string _host;
    std::string _teamName;
    int _port;
    int _sockfd;
    fd_set _readfds;
    struct timeval _tv;
    Bot *_bot;

    void setupConnection();
    void authenticate();
    void loop();
    void recvMessage(std::string &buffer);
};