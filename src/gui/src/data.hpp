#include "map.hpp"
#include "egg.hpp"
#include "player.hpp"

class Data
{
    private:
        int tickRate = 0;
        std::vector<std::string> teamNames;
        bool isRunning = false;
        std::vector<Egg> eggs;
        std::vector<Player> players;

    public:
        Data();
        ~Data();

        Map map;

        void setTickRate(int rate) { this->tickRate = rate; };
        int getTickRate() { return this->tickRate; };

        void addEgg(Egg egg) { this->eggs.push_back(egg); };
        void addTeam(std::string team) { this->teamNames.push_back(team); };
        void addPlayer(Player player) { this->players.push_back(player); };

        Player getPlayer(int n) { return this->players[n]; };
};

Data::Data(/* args */)
{
}

Data::~Data()
{
}
