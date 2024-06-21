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

protected:
    unsigned int _id = 0;
    unsigned int _currentMessageId = 0;

    // Interract with server
    virtual void listen(const std::string &response);
    virtual void listenBroadcast(const std::string &response);

    // Act
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

private:
    std::string saveActionsFile = "./src/ai/dataSaved/actions";
    bool _canAct = false;

    bool isServerResponse(const std::string &response) const;
};
#endif // ABotPattern_HPP_
