#include "Data.hpp"
#include "../utils/GuiException.hpp"

#include <memory>
#include <utility>

// ------------------------------------------------------------------ //
// ---------------------------- GETTERS ----------------------------- //
// ------------------------------------------------------------------ //

Egg &Data::getEggById(int eggid) {
    if (this->eggs.find(eggid) == this->eggs.end())
        throw guiException("getEggById: Invalid egg id(" + std::to_string(eggid) + ")");
    return this->eggs.at(eggid);
};

std::string Data::getTeamByName(std::string name)
{
    for (std::string &team : this->teamNames) {
        if (team.compare(name) == 0)
            return team;
    }
    throw guiException("getTeamByName: Invalid team name(" + name + ")");
};

std::shared_ptr<Player> Data::getPlayerById(int id)
{
    if (this->players.find(id) == this->players.end())
        throw guiException("getPlayerById: Invalid player id(" + std::to_string(id) + ")");
    return this->players.at(id);
};

std::shared_ptr<Incantation> Data::getIncantationByPos(std::vector<int> pos)
{
    for (std::shared_ptr<Incantation> &incantation : this->incantations) {
        if (incantation->getPosition() == pos)
            return incantation;
    }
    throw guiException("getIncantationByPos: Invalid position(" + std::to_string(pos[0]) + ", " + std::to_string(pos[1]) + ")");
};

std::optional<Broadcast> Data::getNextBroadcast() {
    if (this->broadcasts.size() <= 0)
        return std::nullopt;
    Broadcast b = this->broadcasts.back();
    this->broadcasts.pop_back();
    return b;
};

// ------------------------------------------------------------------ //
// ---------------------------- SETTERS ----------------------------- //
// ------------------------------------------------------------------ //


void Data::addPlayer(std::vector<int> values, std::string teamName)
{
    std::vector<int> pos = {values[1], values[2]};
    std::shared_ptr<Player> player = std::make_shared<Player>(
            values[0],
            pos,
            values[3],
            values[4],
            teamName
        );
    players.insert(
        std::pair<int, std::shared_ptr<Player>>(
            values[0],
            player
        )
    );
};


void Data::addEgg(std::vector<int> pos, int eggId, int playerId, EggStatus state)
{
    this->eggs.insert(
        std::make_pair(
            eggId,
            Egg(pos, eggId, playerId, state)
        )
    );
};

void Data::addIncantation(std::vector<int> pos, int lvl, std::vector<int> playersId)
{
    std::shared_ptr<Incantation> incantation = std::make_shared<Incantation>(
        pos,
        lvl,
        playersId
    );
    this->incantations.push_back(incantation);
};

void Data::addBroadcast(int playerNb, std::vector<int> pos, std::string msg)
{
    this->broadcasts.push_back(
        Broadcast(
            playerNb,
            msg,
            pos
        )
    );
};

// ------------------------------------------------------------------ //
// ---------------------------- BOOLEAN ----------------------------- //
// ------------------------------------------------------------------ //

bool Data::doesTeamExist(std::string name)
{
    for (std::string &team : this->teamNames) {
        if (team.compare(name) == 0)
            return true;
    }
    return false;
};


bool Data::playerExists(int id)
{
    if (this->players.find(id) == this->players.end())
        return false;
    return true;
};

// ------------------------------------------------------------------ //
// ----------------------------  RESET ------------------------------ //
// ------------------------------------------------------------------ //

void Data::resetGame()
{
    this->eggs.clear();
    this->players.clear();
    this->incantations.clear();
    this->broadcasts.clear();
    this->winner = std::nullopt;
    this->teamNames.clear();
    this->map.resetMap();
    this->tickRate = 100;
};
