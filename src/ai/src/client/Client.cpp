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
    Message _message;
    unsigned int timeToGetIdentity = 0;

    _message.format("I'm_searching_my_identity_🤔");
    std::string askForIdentity = "Broadcast " + _message._content;
    sendMessage(_teamName);
    sendMessage(askForIdentity);
    sendMessage(askForIdentity);
    _message._content = "";

    while (timeToGetIdentity < 3)
    {
        FD_ZERO(&_readfds);
        FD_SET(_sockfd, &_readfds);
        _tv.tv_sec = 0;
        _tv.tv_usec = 10000;

        int activity = select(_sockfd + 1, &_readfds, NULL, NULL, &_tv);

        if (activity > 0 && FD_ISSET(_sockfd, &_readfds))
        {
            std::string response;
            recvMessage(response);

            if (response.find("message") != std::string::npos)
            {
                _message._content = response;
                _message.vigenereDecrypt();
                break;
            }
            timeToGetIdentity++;
        }
    }
    try
    {
        initBot(_message._content);
    }
    catch (const std::exception &e)
    {
        PRINT_ERROR(e.what());
        close(_sockfd);
        exit(EXIT_FAILURE);
    }
}

void Client::initBot(const std::string identityMessage)
{
    unsigned int id = 0;
    unsigned int currentMessageId = 0;

    std::cout << "identityMessage: " << identityMessage << std::endl;
    if (!identityMessage.empty())
    {
        std::string job = "";
        std::string prefixId = "you_are_bot=";
        std::string prefixJob = "your_job=";
        std::string prefixCurrentMessageId = "currentMessageId=";
        size_t pos = identityMessage.find(prefixId);
        size_t posJob = identityMessage.find(prefixJob);
        size_t posCurrentMessageId = identityMessage.find(prefixCurrentMessageId);

        if (pos != std::string::npos)
        {
            std::string idStr = identityMessage.substr(pos + prefixId.size());
            id = std::stoi(idStr);
        }
        if (posCurrentMessageId != std::string::npos)
        {
            std::string currentMessageIdStr = identityMessage.substr(posCurrentMessageId + prefixCurrentMessageId.size());
            currentMessageId = std::stoi(currentMessageIdStr);
        }
        if (posJob != std::string::npos)
        {
            job = identityMessage.substr(posJob + prefixJob.size());
            if (job.find("SIMPLE_BOT") != std::string::npos)
                _bot = BotFactory::createBot("SimpleBot");
        }
    }
    else
    {
        _bot = BotFactory::createBot("Forker");
    }
    if (_bot != nullptr)
    {
        _bot->init(_sockfd, _teamName, _arg, _host, _port, id, currentMessageId);
    }
    else
    {
        throw std::runtime_error("Bot is null");
    }
}

void Client::sendMessage(const std::string &message)
{
    std::string messageToSend = message + "\n";

    send(_sockfd, messageToSend.c_str(), messageToSend.size(), 0);
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
