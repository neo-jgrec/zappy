#include "Broadcast.hpp"

std::vector<int> Broadcast::getPosition() {
    return this->pos;
};

std::string Broadcast::getMessage() {
    return this->message;
};

int Broadcast::getPlayerNb() { 
    return this->playerNb;
};
