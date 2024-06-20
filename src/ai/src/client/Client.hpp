/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Client.hpp
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <memory>

#include "../botFactory/BotFactory.hpp"
#include "../constant/Constants.hpp"

class Client
{
public:
    Client(const std::string &host, const std::string &teamName, int port, bool arg);
    ~Client();

    void run();

private:
    std::string _host;
    std::string _teamName;
    int _port;
    int _sockfd;
    fd_set _readfds;
    struct timeval _tv;
    std::unique_ptr<IBot> _bot;
    bool _arg;

    // Map Data
    unsigned int _slot = 0;
    unsigned int _width = 42;
    unsigned int _height = 42;

    int messageToReadBeforeStart = 3;

    void setupConnection();
    void authenticate();
    void loop();
    void recvMessage(std::string &buffer);
    void sendMessage(const std::string &message);
    void initBot(const std::string identityMessage);
    void listenFirstResponse(const std::string &response);
};

#endif /* !CLIENT_HPP_ */
