#ifndef DATA_HPP
    #define DATA_HPP
    
    #include "Map.hpp"
    #include "Egg.hpp"
    #include "Player.hpp"
    #include "Incantation.hpp"
    #include "Broadcast.hpp"
    #include "GuiException.hpp"

    #include <string>
    #include <vector>
    #include <map>

class Data
{
    private:
        int tickRate = 0;
        std::vector<std::string> teamNames;
        bool isRunning = false;
        std::map<int, Egg> eggs;
        std::map<int, Player> players;
        std::vector<Incantation> incantations;
        std::vector<Broadcast> broadcasts;
        std::string winner = "";
        Map map = Map();

    public:
        Data() {};
        ~Data() {};

        /**
         * @brief Set the tick rate of the game high values will make the game run faster
         * @param rate between 2 and 10000
         * @return void
        */
        void setTickRate(int rate) { this->tickRate = rate; };
        int getTickRate() { return this->tickRate; };


        void setRunning(bool state) { this->isRunning = state; };
        bool getRunning() { return this->isRunning; };

        void setWinner(std::string team) { this->winner = team; };
        std::string getWinner() { return this->winner; };

        /**
        * @brief Add an egg to the game
        * @param values the values of the egg
        * @param playerId the id of the player that laid the egg
        * @param state the state of the egg
        * @return void
        */
        void addEgg(std::vector<int> pos, int eggId, int playerId, EggStatus state) {
            this->eggs.insert(std::make_pair(
                eggId,
                Egg(pos, eggId, playerId, state)
            )); };
        std::map<int, Egg> &getEggs() { return this->eggs; };
        Egg &getEggById(int eggid) {
            if (this->eggs.find(eggid) == this->eggs.end())
                throw guiException("getEggById: Invalid egg id(" + std::to_string(eggid) + ")");
            return this->eggs.at(eggid);
        };


        void addTeam(std::string team) { this->teamNames.push_back(team); };
        /**
         * @brief Get the teams in the game
         * @return a copy of the teams
        */
        std::vector<std::string> getTeams() { return this->teamNames; };
        std::string getTeamAt(int n) { return this->teamNames[n]; };
        /**
         * @brief Check if the team exists
         * @param team the team name
         * @return true if the team exists
        */
        bool doesTeamExist(std::string team) {
            for (auto &t : this->teamNames) {
                if (t.compare(team) == 0)
                    return true;
            }
            return false;
        };


        void addPlayer(std::vector<int> values, std::string teamName) {
            std::vector<int> pos = {values[1], values[2]};
            this->players.insert(std::make_pair(
                values[0],
                Player( values[0], pos, values[3], values[4], teamName)
            ));
        };
        std::map<int, Player> &getPlayers() { return this->players; };
        /**
         * @brief Get the player corresponding to the given id
         * @param id the id of the player (player number)
         * @return a reference to the player
         * @throw guiException if the player does not exist
        */
        Player &getPlayerById(int id) {
            if (this->players.find(id) == this->players.end())
                throw guiException("getPlayerById: Invalid player id(" + std::to_string(id) + ")");
            return this->players.at(id);
        };
        bool playerExists(int id) { return this->players.find(id) != this->players.end(); };

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
        void addBroadcast(int playerNb, std::vector<int> pos, std::string msg) {
            this->broadcasts.push_back(Broadcast(playerNb, msg, pos));
        };

        Map &getMap() { return this->map; };
};

#endif // DATA_HPP
