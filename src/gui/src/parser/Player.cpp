#include "Player.hpp"

//-----------------------------------------------------------------//
//----------------------------SETTERS------------------------------//
//-----------------------------------------------------------------//

void Player::setPosition(std::vector<int> newPos) {
    nextPositions.push_back(newPos);
    events.push_back(Event(MOVING, newPos));
};

void Player::setOrientation(int newOrientation) {
    this->orientation = newOrientation;
};

void Player::setIncanting() {
    events.push_back(Event(INCANTATING));
};

void Player::setEgging() {
    events.push_back(Event(EGGING));
};

void Player::setPushing() {
    events.push_back(Event(PUSHING));
};

void Player::setPickup(int res) {
    events.push_back(Event(PICKUP, std::vector<int>({res})));
};

void Player::setDrop(int res) {
    events.push_back(Event(DROP, std::vector<int>({res})));
};

void Player::setAlive(bool alive) {
    this->isAlive = alive;
};

void Player::setLvl(int newLvl) {
    this->lvl = newLvl;
    events.push_back(Event(LVLUP, std::vector<int>({newLvl})));
};

void Player::setTeam(std::string newTeam) {
    this->team = newTeam;
};

void Player::setPlayerNb(int newId) {
    this->id = newId;
};

void Player::setInventory(std::vector<int> inventoryVals) {
    this->inventory = inventoryVals;
};

//-----------------------------------------------------------------//
//----------------------------GETTERS------------------------------//
//-----------------------------------------------------------------//

Event Player::getNextEvent() {
    if (events.empty())
        return NONE;
    Event event = events.front();
    if (event.action == MOVING)
        popNextPosition();
    events.erase(events.begin());
    return event;
};

std::vector<int> Player::getPosition() {
    return {position};
};

int Player::getOrientation() {
    return this->orientation;
};

int Player::getLvl() {
    return this->lvl;
};

std::string Player::getTeam()  {
    return this->team;
};

int Player::getPlayerNb() {
    return this->id;
};

bool Player::getAlive() {
    return this->isAlive;
};

std::vector<int> Player::getInventory() {
    return this->inventory;
};

//-----------------------------------------------------------------//
//---------------------------UTILITIES-----------------------------//
//-----------------------------------------------------------------//

void Player::popNextPosition() {
    if (nextPositions.empty())
        return;
    this->position = nextPositions.front();
    nextPositions.erase(nextPositions.begin());
};
