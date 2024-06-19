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

#include <memory>
class ABotPattern : public ABot
{
public:
    ABotPattern();
    ~ABotPattern();
    void run(const std::string &response) override;
    virtual void init(int sockfd, const std::string &teamName, bool arg) = 0;

protected:
    std::vector<std::unique_ptr<Pattern>> _patterns;

    // Interract with server
    virtual void listen(const std::string &response);

    // Actions
    virtual void updateStrategy() = 0;

    // Listeners
    void listenLookResponse(const std::string &response);
    void listenTakeResponse(const std::string &response);
    void listenBroadcastResponse(const std::string &response);
    void listenIncantationResponse(const std::string &response);
    void listenIncantationReturnResponse(const std::string &response);

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

    // data
    virtual void saveData(const std::string &path);
};
#endif // ABotPattern_HPP_
