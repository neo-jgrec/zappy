/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ABot.hpp
*/

#ifndef ABOT_HPP_
#define ABOT_HPP_

#include "IBot.hpp"
#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <sstream>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
#include <numeric>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>
#include <fstream>

#include "../state/BotState.hpp"
#include "../utils/PrintColor.hpp"
#include "../message/Message.hpp"
#include "../utils/StringUtils.hpp"
#include "IBot.hpp"
#include "../hash/Pairhash.hpp"
#include "../constant/Constants.hpp"

class ABot : public IBot
{
public:
    ABot();
    ~ABot();
    virtual void run(const std::string &response) = 0;
    // TODO: remove arg
    virtual void init(int sockfd, const std::string &teamName, const std::string &host, int port, int id, int idMessage) = 0;

protected:
    // TODO: How to put it in constant without conflict ?
    std::unordered_map<std::pair<int, int>, std::vector<std::string>, PairHash> movementMap = {
        {{-1, 1}, {"FORWARD", "LEFT", "FORWARD"}},
        {{0, 1}, {"FORWARD"}},
        {{1, 1}, {"FORWARD", "RIGHT", "FORWARD"}},
        {{1, 2}, {"RIGHT", "FORWARD", "LEFT", "FORWARD", "FORWARD"}},
        {{1, 3}, {"RIGHT", "FORWARD", "LEFT", "FORWARD", "FORWARD", "FORWARD"}},
        {{2, 2}, {"RIGHT", "FORWARD", "FORWARD", "LEFT", "FORWARD", "FORWARD"}},
        {{2, 3}, {"RIGHT", "FORWARD", "FORWARD", "LEFT", "FORWARD", "FORWARD", "FORWARD"}},
        {{3, 3}, {"RIGHT", "FORWARD", "FORWARD", "FORWARD", "LEFT", "FORWARD", "FORWARD", "FORWARD"}},
        {{0, 2}, {"FORWARD", "FORWARD"}},
        {{-1, 2}, {"LEFT", "FORWARD", "RIGHT", "FORWARD", "FORWARD"}},
        {{-1, 3}, {"LEFT", "FORWARD", "RIGHT", "FORWARD", "FORWARD", "FORWARD"}},
        {{-2, 2}, {"LEFT", "FORWARD", "FORWARD", "RIGHT", "FORWARD", "FORWARD"}},
        {{-2, 3}, {"LEFT", "FORWARD", "FORWARD", "RIGHT", "FORWARD", "FORWARD", "FORWARD"}},
        {{-3, 3}, {"LEFT", "FORWARD", "FORWARD", "FORWARD", "RIGHT", "FORWARD", "FORWARD", "FORWARD"}},
        {{0, 3}, {"FORWARD", "FORWARD", "FORWARD"}},
    };

    // Client
    int _sockfd = -1;
    std::string _teamName = "";
    std::string _host = "";
    int _port = 0;

    // Game
    unsigned int _iteration = 0;

    // Messages
    Message _message;
    std::string _direction;
    Message _enemyMessage;
    std::vector<Message> _alliesMessage;
    std::string _signature = "bFNneQbXQkyJHGEQd";

    // State
    BotState _state;

    // Actions
    std::vector<std::pair<std::function<void()>, std::string>> queue;

    // Interract with server
    virtual void listen(const std::string &response) = 0;
    void sendMessage(const std::string &message);

    // Actions
    void doAction(Action action, const std::string &parameter);

    // Debug
    void debugInitialisation();
    void debugState();

    // Listeners
    void listenLookResponse(const std::string &response);
    void listenTakeResponse(const std::string &response);
    void listenBroadcastResponse(const std::string &response);
    void listenIncantationResponse(const std::string &response);
    void listenIncantationReturnResponse(const std::string &response);
    void listenConnectNbrResponse(const std::string &response);
    void listenCancel(const std::string &response);
    void listenInventoryResponse(const std::string &response);

    // Listeners Broadcast
    void listenGroup(const std::string &response);
    void listenGroupJoined(const std::string &response);

    // Metrics
    void saveMetrics(ActionInfo actionInfo);
    void saveDataActions(const std::string &filename);
};

#endif // ABot_HPP_
