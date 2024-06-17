
#ifndef PLAYER_HPP
    #define PLAYER_HPP

    #include <vector>
    #include <string>


enum Actions
{
    EGGING,
    PUSHED,
    INCANTATING,
    PICKUP,
    DROP,
    MOVING,
    LVLUP,
    NONE
};


class Event {
    public:
        std::vector<int> params;
        Actions action;

        Event(Actions action, std::vector<int> params) : params(params), action(action) {};
        Event(Actions action) : params(std::vector<int>()), action(action) {};
        ~Event() {};
};

enum Orientation
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

class Player
{
    private:
        std::vector<int> position = {0, 0};
        std::vector<std::vector<int>> nextPositions = {};
        int orientation = UP;

        int lvl = 1;
        int id = 0;
        bool isAlive = true;
        std::string team = "default";

        std::vector<int> inventory = {0, 0, 0, 0, 0, 0, 0};
        std::vector<Event> events = {};

        void popNextPosition();

    public:
        Player() {};
        Player(int id, std::vector<int> position, int orientation, int lvl, std::string team) : position(position), orientation(orientation), lvl(lvl), id(id), team(team) {};
        ~Player() {};

        void setPosition(std::vector<int> newPos);
        void setOrientation(int newOrientation);
        void setIncanting();
        void setEgging();
        void setPushed();
        void setPickup(int res);
        void setDrop(int res);
        void setAlive(bool alive);
        void setLvl(int newLvl);
        void setTeam(std::string newTeam);
        void setPlayerNb(int newId);
        void setInventory(std::vector<int> inventoryVals);
        
        std::vector<int> getInventory();
        std::vector<int> getPosition();
        int getOrientation();
        int getPlayerNb();
        int getLvl();
        std::string getTeam();
        Event getNextEvent();
        bool getAlive();
};

#endif // PLAYER_HPP
