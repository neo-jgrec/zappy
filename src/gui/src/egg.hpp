#ifndef EGG_HPP
    #define EGG_HPP

#include <vector>
#include <string>

class Egg
{
private:
    int x;
    int y;
    int Nb;
    int playerNb;
    bool isHatched = false;
    bool isAlive = true;
public:
    void setHatched(bool hatched) { isHatched = hatched; }
    void setAlive(bool alive) { isAlive = alive; }

    Egg(std::vector<std::string> values) {
    this->x = std::stoi(values.at(1));
    this->y = std::stoi(values.at(2));
    this->Nb = std::stoi(values.at(3));
    this->playerNb = std::stoi(values.at(4));
    }
    ~Egg() {};
};


#endif // EGG_HPP
