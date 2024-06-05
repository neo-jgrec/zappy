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
        Map map = Map();

    public:
        Data();
        ~Data();

        /**
         * @brief Set the tick rate of the game high values will make the game run faster
         * @param rate between 2 and 10000
         * @return void
        */
        void setTickRate(int rate) { this->tickRate = rate; };
        int getTickRate() { return this->tickRate; };


        void setRunning(bool state) { this->isRunning = state; };
        bool getRunning() { return this->isRunning; };


        void addEgg(Egg egg) { this->eggs.push_back(egg); };
        std::vector<Egg> &getEggs() { return this->eggs; };


        void addTeam(std::string team) { this->teamNames.push_back(team); };
        /**
         * @brief Get the teams in the game
         * @return a copy of the teams
        */
        std::vector<std::string> getTeams() { return this->teamNames; };
        std::string getTeamAt(int n) { return this->teamNames[n]; };


        void addPlayer(Player player) { this->players.push_back(player); };
        std::vector<Player> &getPlayers(int n) { return this->players; };
        /**
         * @brief Get the player at the given index
         * @param n the index of the player
         * @return a copy of the player
         * @throw guiException if the index is out of range
        */
        Player getPlayerAt(int n) {
            if (n >= this->players.size())
                throw guiException("The player index is out of range");
            return this->players.at(n);
        };


        Map &getMap() { return this->map; };
};

Data::Data()
{
}

Data::~Data()
{
}
