/*
** EPITECH PROJECT, 2024
** zappy/ai/client
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
}

void Client::run()
{
    printColor("Run client\n\n", BRIGHT_BLUE);

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
        printColor("🚀✅ Connected to server: " + _host + ":" + std::to_string(_port) + " on team: " + _teamName + "\n", BRIGHT_BLUE);
}

void Client::authenticate()
{
    std::string buffer;
    Message _message;
    unsigned int timeToGetIdentity = 0;
    std::string askForIdentity = "";

    // To pass the first message WELCOME
    recvMessage(buffer);

    // Ask two time for identity
    _message.format("I'm_searching_my_identity");
    askForIdentity = "Broadcast " + _message.content;
    sendMessage(_teamName);
    sendMessage(askForIdentity);
    sendMessage(askForIdentity);
    _message.content = "";

    auto condition = [&]()
    { return timeToGetIdentity < 3; };

    auto action = [&]()
    {
        std::string response;
        recvMessage(response);
        if (response.find("ko") != std::string::npos)
        {
            PRINT_ERROR("Authentication failed: verify teamName");
            close(_sockfd);
            exit(EXIT_FAILURE);
        }
        if (response.find("message") != std::string::npos)
        {
            _message.content = response;
            _message.vigenereDecrypt();
            return;
        }
        timeToGetIdentity++;
        _messageToReadBeforeStart--;
    };
    interactWithServer(condition, action);
    try
    {
        initBot(_message.content);
    }
    catch (const ClientException &e)
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

    if (!identityMessage.empty())
    {
        std::cout << "identityMessage: " << identityMessage << std::endl;
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
        else
        {
            _bot = BotFactory::createBot("SimpleBot");
        }
    }
    else
    {
        _bot = BotFactory::createBot("SimpleBot"); // TODO: is forker normally
        if (_bot == nullptr)
            throw ClientException("BotFactory failed");
    }
    if (_bot != nullptr)
    {
        _bot->init(_sockfd, _teamName, _host, _port, id, currentMessageId);
    }
    else
    {
        throw ClientException("Bot is null");
    }
}

void Client::sendMessage(const std::string &message)
{
    std::string messageToSend = message + "\n";

    send(_sockfd, messageToSend.c_str(), messageToSend.size(), 0);
}

void Client::loop()
{
    // clear messsages of servers before start
    auto condition = [&]()
    { return _messageToReadBeforeStart > 0; };
    auto action = [&]()
    {
        std::string response;
        recvMessage(response);
        _messageToReadBeforeStart--;
    };
    interactWithServer(condition, action);

    _bot->run("start");
    auto conditionStart = [&]()
    { return true; };
    auto actionStart = [&]()
    {
        std::string response;
        recvMessage(response);
        _bot->run(response);
    };
    interactWithServer(conditionStart, actionStart);
}

void Client::recvMessage(std::string &buffer)
{
    char recvBuffer[1024] = {0};
    int valread = read(_sockfd, recvBuffer, 1024);

    if (valread < 0)
    {
        PRINT_ERROR("Read failed");
        close(_sockfd);
        exit(FAILURE);
    }
    else if (valread == 0)
    {
        PRINT_ERROR("Server closed the connection");
        close(_sockfd);
        exit(FAILURE);
    }

    buffer = std::string(recvBuffer, valread);
}

template <typename ConditionFunc, typename ActionFunc>
void Client::interactWithServer(ConditionFunc condition, ActionFunc action)
{
    while (condition())
    {
        FD_ZERO(&_readfds);
        FD_SET(_sockfd, &_readfds);
        _tv.tv_sec = 0;
        _tv.tv_usec = 10000;
        int activity = select(_sockfd + 1, &_readfds, NULL, NULL, &_tv);

        if (activity > 0 && FD_ISSET(_sockfd, &_readfds))
            action();
    }
}
