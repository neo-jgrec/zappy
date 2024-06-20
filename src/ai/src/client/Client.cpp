/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Client.cpp
*/

#include "Client.hpp"

Client::Client(const std::string &host, const std::string &teamName, int port, bool arg)
    : _host(host), _teamName(teamName), _port(port)
{
    _arg = arg;
    if (_arg)
        printf("Arg is true\n");
    else
        printf("Arg is false\n");
    setupConnection();
}

Client::~Client()
{
    close(_sockfd);
}

void Client::run()
{
    std::cout << "Run client\n\n";

    authenticate();
    loop();
}

void Client::setupConnection()
{
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(_port);
    if (inet_pton(AF_INET, _host.c_str(), &serv_addr.sin_addr) <= 0)
    {
        perror("Invalid address or address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(_sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Connected to server: " << _host << ":" << _port << " on team: " << _teamName << "\n";
        std::string buffer;
    }
}

void Client::authenticate()
{
    std::string buffer;

    // to pass the first message welcome
    recvMessage(buffer);
    try
    {
        // Landmark: 1. Save host and port to fork.
        _bot = BotFactory::createBot("Forker");
    }
    catch (const std::exception &e)
    {
        PRINT_ERROR(e.what());
        close(_sockfd);
        exit(EXIT_FAILURE);
    }
    _bot->init(_sockfd, _teamName, _arg, _host, _port);
}

void Client::loop()
{
    while (true)
    {
        FD_ZERO(&_readfds);
        FD_SET(_sockfd, &_readfds);
        _tv.tv_sec = 0;
        _tv.tv_usec = 10000;

        int activity = select(_sockfd + 1, &_readfds, NULL, NULL, &_tv);
        // std::cout << "activity: " << activity << std::endl;
        if (activity > 0 && FD_ISSET(_sockfd, &_readfds))
        {
            std::string response;
            recvMessage(response);
            _bot->run(response);
        }
    }
}

void Client::recvMessage(std::string &buffer)
{
    char recvBuffer[1024] = {0};
    int valread = read(_sockfd, recvBuffer, 1024);

    buffer = std::string(recvBuffer, valread);
}
