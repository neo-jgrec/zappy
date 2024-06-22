/*
** EPITECH PROJECT, 2024
** zappy/ai/bots
** File description:
** ABotPattern.hpp
*/

#ifndef ABotPattern_HPP_
#define ABotPattern_HPP_

#include "ABot.hpp"
#include "../pattern/Pattern.hpp"
#include "../constant/Constants.hpp"
#include "../utils/StringUtils.hpp"

#include <memory>

class ABotPattern : public ABot
{
public:
    void run(const std::string &response) override;
    void init(int sockfd, const std::string &teamName, bool arg, const std::string &host, int port, int id, int idMessage) override;

    virtual void initChild() = 0;
    virtual void updateStrategy() = 0;
    // TODO: do updateStrategyServer and updateStrategyBroadcast ?
protected:
    unsigned int _id = 0;
    unsigned int _currentMessageId = 0;

    // Interract with server
    void verifyServerIsRunning(const std::string &response);
    virtual void listen(const std::string &response);
    virtual void listenBroadcast(const std::string &response);

    // Act
    void react(const std::string &responseServer, const std::string &responseBroadcast);
    void act();

    // Paterns
    void testPatern();
    void survive();
    void runToLinemate();
    void searchAndTakeRessource(const std::string &ressource);
    void group();
    void searchLinemate();
    void searchDeraumere();
    void searchSibur();
    void searchMendiane();
    void searchPhiras();
    void searchThystame();
    void trapMessage();
    void incantation(std::vector<std::string> objs);
    void joinGroup();
    void forkBot(unsigned int idBot);
    void incantationLvl1();
    void incantationLvl2();

    // Debug
    void debugResponses(const std::string &responseServer, const std::string &responseBroadcast);
    void debugBotRun();
    void debugMetadata();

    // Utils
    void separateServerBroadcast(const std::string &response, std::string &responseServer, std::string &responseBroadcast);

private:
    std::string saveActionsFile = "./src/ai/dataSaved/actions";
    bool _canAct = false;
};
#endif // ABotPattern_HPP_
