
#ifndef PLAYER_HPP
    #define PLAYER_HPP

    #include <vector>
    #include <string>
    #include <stdexcept>

class Player
{
    enum Orientation
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    private:
        int x;
        int y;
        int lvl;
        int orientation = UP;
        std::string team;
        int playerNb;
        bool isIncanting = false;
        bool isEgging = false;
        bool isAlive = true;
        std::vector<int> inventory = {0, 0, 0, 0, 0, 0, 0};
    public:
        Player() {};
        Player(int nb, int x, int y, int orientation, int lvl, std::string team) : playerNb(nb), x(x), y(y), orientation(orientation), lvl(lvl), team(team) {};
        ~Player() {};

        void setPosition(int x, int y) { this->x = x; this->y = y; };
        void setOrientation(int orientation) { this->orientation = orientation; };
        void setIncanting(bool incanting) { this->isIncanting = incanting; };
        void setEgging(bool egging) { this->isEgging = egging; };
        void setAlive(bool alive) { this->isAlive = alive; };
        void setLvl(int lvl) { this->lvl = lvl; };
        void setTeam(std::string team) { this->team = team; };
        void setPlayerNb(int playerNb) { this->playerNb = playerNb; };
        void setInventory(std::vector<std::string> inventoryVals) {
            if (inventoryVals.size() != 11)
                throw std::invalid_argument("Invalid inventory size");
            this->inventory[0] = std::stoi(inventoryVals.at(4));
            this->inventory[1] = std::stoi(inventoryVals.at(5));
            this->inventory[2] = std::stoi(inventoryVals.at(6));
            this->inventory[3] = std::stoi(inventoryVals.at(7));
            this->inventory[4] = std::stoi(inventoryVals.at(8));
            this->inventory[5] = std::stoi(inventoryVals.at(9));
            this->inventory[6] = std::stoi(inventoryVals.at(10));
        };

        void update(std::vector<std::string> vals) {
            if (vals.size() != 5)
                throw std::invalid_argument("Invalid player size");
            setPosition(std::stoi(vals.at(2)), std::stoi(vals.at(3)));
            setOrientation(std::stoi(vals.at(4)));
        };

        std::vector<int> getPosition() { return {this->x, this->y}; };
        int getOrientation() { return this->orientation; };
        int getLvl() { return this->lvl; };
        std::string getTeam()  { return this->team; };
        int getPlayerNb() { return this->playerNb; };
        bool getIncanting() { return this->isIncanting; };
        bool getAlive() { return this->isAlive; };
        std::vector<int> getInventory() { return this->inventory; };
};

#endif // PLAYER_HPP
