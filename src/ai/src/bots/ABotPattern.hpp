/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ABotPattern.hpp
*/

#ifndef ABotPattern_HPP_
#define ABotPattern_HPP_

#include "ABot.hpp"
#include "../pattern/Pattern.hpp"
#include "../constant/Constants.hpp"

#include <memory>

class ABotPattern : public ABot
{
public:
    ABotPattern();
    ~ABotPattern();
    void run(const std::string &response) override;
    void init(int sockfd, const std::string &teamName, bool arg, const std::string &host, int port, int id, int idMessage);
    virtual void initChild() = 0;

    virtual void updateStrategy() = 0;

protected:
    std::vector<std::unique_ptr<Pattern>> _patterns;
    unsigned int _id = 0;
    unsigned int _currentMessageId = 0;
    std::string filenameSave = "";

    // Interract with server
    virtual void listen(const std::string &response);

    // Actions
    void act();

    // Listeners
    void listenLookResponse(const std::string &response);
    void listenTakeResponse(const std::string &response);
    void listenBroadcastResponse(const std::string &response);
    void listenIncantationResponse(const std::string &response);
    void listenIncantationReturnResponse(const std::string &response);
    void listenConnectNbrResponse(const std::string &response);

    // Paterns
    void testPatern();
    void survive();
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

    // Data
    virtual void saveData(const std::string &path);
};
#endif // ABotPattern_HPP_
