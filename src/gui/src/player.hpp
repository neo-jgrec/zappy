
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
        std::vector<int> position = {0, 0};
        int lvl;
        int orientation = UP;
        std::string team;
        int id;
        bool isIncanting = false;
        bool isEgging = false;
        bool isAlive = true;
        std::vector<int> inventory = {0, 0, 0, 0, 0, 0, 0};
    public:
        Player() {};
        Player(int id, std::vector<int> position, int orientation, int lvl, std::string team) : id(id), position(position), orientation(orientation), lvl(lvl), team(team) {};
        ~Player() {};

        void setPosition(std::vector<int> newPos) { this->position = newPos; };
        void setOrientation(int newOrientation) { this->orientation = newOrientation; };
        void setIncanting(bool incanting) { this->isIncanting = incanting; };
        void setEgging(bool egging) { this->isEgging = egging; };
        void setAlive(bool alive) { this->isAlive = alive; };
        void setLvl(int newLvl) { this->lvl = newLvl; };
        void setTeam(std::string newTeam) { this->team = newTeam; };
        void setPlayerNb(int newId) { this->id = newId; };
        void setInventory(std::vector<int> inventoryVals) { this->inventory = inventoryVals; };

        void update(std::vector<std::string> vals) {
            if (vals.size() != 5)
                throw std::invalid_argument("Invalid player size");
            // setPosition();
            setOrientation(std::stoi(vals.at(4)));
        };

        std::vector<int> getPosition() { return {position}; };
        int getOrientation() { return this->orientation; };
        int getLvl() { return this->lvl; };
        std::string getTeam()  { return this->team; };
        int getPlayerNb() { return this->id; };
        bool getIncanting() { return this->isIncanting; };
        bool getAlive() { return this->isAlive; };
        std::vector<int> getInventory() { return this->inventory; };
};

#endif // PLAYER_HPP
