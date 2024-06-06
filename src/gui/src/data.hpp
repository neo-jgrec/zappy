#include "map.hpp"
#include "egg.hpp"
#include "player.hpp"
#include "incantation.hpp"
#include "broadcast.hpp"

class Data
{
    private:
        int tickRate = 0;
        std::vector<std::string> teamNames;
        bool isRunning = false;
        std::vector<Egg> eggs;
        std::vector<Player> players;
        std::vector<Incantation> incantations;
        std::vector<Broadcast> broadcasts;
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


        void addPlayer(std::vector<std::string> playerVals) {
            if (playerVals.size() != 7)
                throw guiException("Invalid player size");
            this->players.push_back(Player(
                std::stoi(playerVals[1]),
                std::stoi(playerVals[2]),
                std::stoi(playerVals[3]),
                std::stoi(playerVals[4]),
                std::stoi(playerVals[5]),
                playerVals[6]));
        };
        std::vector<Player> &getPlayers() { return this->players; };
        /**
         * @brief Get the player at the given index
         * @param n the index of the player
         * @return a reference to the player
         * @throw guiException if the index is out of range
        */
        Player &getPlayerAt(int n) {
            if (n >= this->players.size())
                throw guiException("The player index is out of range");
            return this->players.at(n);
        };

        std::vector<Incantation> &getIncantations() { return this->incantations; };
        void addIncantation(std::vector<std::string> incVals) {
            if (incVals.size() < 4)
                throw guiException("Invalid incantation size");
            this->incantations.push_back(Incantation(
                std::stoi(incVals[1]),
                std::stoi(incVals[2]),
                std::stoi(incVals[3])));
        };

        std::vector<Broadcast> &getBroadcasts() { return this->broadcasts; };
        void addBroadcast(std::vector<std::string> broadcastVals) {
            if (broadcastVals.size() != 3)
                throw guiException("Invalid broadcast size");
            this->broadcasts.push_back(Broadcast(
                std::stoi(broadcastVals[1]),
                broadcastVals[2],
                players.at(std::stoi(broadcastVals[1])).getPosition()));
        };

        Map &getMap() { return this->map; };
};

Data::Data()
{
}

Data::~Data()
{
}
