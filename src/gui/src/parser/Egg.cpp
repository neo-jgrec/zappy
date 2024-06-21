#include "Egg.hpp"

Egg::Egg(std::vector<int> pos, int nb, int playerNb, EggStatus state): pos(pos), nb(nb), playerNb(playerNb), state(state) {};

void Egg::setState(EggStatus newState) {
    state = newState;
}

EggStatus Egg::getState() {
    return state;
}

std::vector<int> Egg::getPos() {
    return pos;
}

int Egg::getId() {
    return nb;
}

int Egg::getPlayerNb() {
    return playerNb;
}
