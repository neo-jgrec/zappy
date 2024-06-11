
#ifndef PLAYER_HPP
    #define PLAYER_HPP

    #include <vector>
    #include <string>


enum Actions
{
    EGGING,
    PUSHING,
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

        Event(Actions action, std::vector<int> params) : action(action), params(params) {};
        Event(Actions action) : action(action), params(std::vector<int>()) {};
        ~Event() {};
};

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
        std::vector<std::vector<int>> nextPositions;
        int lvl;
        int orientation = UP;
        std::string team;
        int id;
        std::vector<Event> events;
        bool isAlive = true;
        std::vector<int> inventory = {0, 0, 0, 0, 0, 0, 0};
    public:
        Player() {};
        Player(int id, std::vector<int> position, int orientation, int lvl, std::string team) : id(id), position(position), orientation(orientation), lvl(lvl), team(team) {};
        ~Player() {};

        void setPosition(std::vector<int> newPos) {
            nextPositions.push_back(position);
            events.push_back(Event(MOVING, newPos));
        };
        void setOrientation(int newOrientation) { this->orientation = newOrientation; };
        void setIncanting() { events.push_back(Event(INCANTATING)); };
        void setEgging() { events.push_back(Event(EGGING)); };
        void setPushing() { events.push_back(Event(PUSHING)); };
        void setPickup(int res) { events.push_back(Event(PICKUP, std::vector<int>(res))); };
        void setDrop(int res) { events.push_back(Event(DROP, std::vector<int>(res))); };
        void setAlive(bool alive) { this->isAlive = alive; };
        void setLvl(int newLvl) {
            this->lvl = newLvl;
            events.push_back(Event(LVLUP, std::vector<int>(newLvl)));
        };
        void setTeam(std::string newTeam) { this->team = newTeam; };
        void setPlayerNb(int newId) { this->id = newId; };
        void setInventory(std::vector<int> inventoryVals) { this->inventory = inventoryVals; };
        
        Event getNextEvent() {
            if (events.empty())
                return NONE;
            Event event = events.front();
            if (event.action == MOVING)
                popNextPosition();
            events.erase(events.begin());
            return event;
        };
        void popNextPosition() {
            if (nextPositions.empty())
                return;
            this->position = nextPositions.front();
            nextPositions.erase(nextPositions.begin());
        };
        std::vector<int> getPosition() { return {position}; };
        int getOrientation() { return this->orientation; };
        int getLvl() { return this->lvl; };
        std::string getTeam()  { return this->team; };
        int getPlayerNb() { return this->id; };
        bool getAlive() { return this->isAlive; };
        std::vector<int> getInventory() { return this->inventory; };
};

#endif // PLAYER_HPP
