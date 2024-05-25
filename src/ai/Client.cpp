/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Client.cpp
*/

#include "Client.hpp"

Client::Client(const std::string &host, const std::string &teamName, int port)
    : _host(host), _teamName(teamName), _port(port)
{
    setupConnection();
}

Client::~Client()
{
    close(_sockfd);
    delete _bot;
}

void Client::run()
{
    std::cout << "Run client\n";

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
        // recvMessage(buffer);
    }
}

void Client::authenticate()
{
    std::string buffer;

    recvMessage(buffer);                // to handle Welcome message
    _bot = new Bot(_sockfd, _teamName); // to verify: don't do new
}

void Client::loop()
{
    bool a = false;
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
