#include "Data.hpp"
#include "GuiException.hpp"

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

Player &Data::getPlayerById(int id)
{
    if (this->players.find(id) == this->players.end())
        throw guiException("getPlayerById: Invalid player id(" + std::to_string(id) + ")");
    return this->players.at(id);
};

Incantation &Data::getIncantationByPos(std::vector<int> pos)
{
    if (this->incantations.find(pos) == this->incantations.end())
        throw guiException("getIncantationsByPos: Invalid position");
    return this->incantations.at(pos);
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
    this->players.insert(std::make_pair(
        values[0],
        Player(
            values[0],
            pos,
            values[3],
            values[4],
            teamName
        )
    ));
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
    this->incantations.insert(
        std::make_pair(
            pos,
            Incantation(
                pos,
                lvl,
                playersId
            )
        )
    );
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

