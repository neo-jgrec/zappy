#ifndef DATA_HPP
    #define DATA_HPP
    
    #include "Map.hpp"
    #include "Egg.hpp"
    #include "Player.hpp"
    #include "Incantation.hpp"
    #include "Broadcast.hpp"
#include "ServerConnect.hpp"

    #include <memory>
    #include <string>
    #include <vector>
    #include <map>
    #include <optional>

class Data
{
    private:
        int tickRate = 0;
        std::vector<std::string> teamNames = {};
        bool isRunning = false;
        std::map<int, Egg> eggs = {};
        std::map<int, std::shared_ptr<Player>> players = {};
        std::map<std::vector<int>, Incantation> incantations = {};
        std::vector<Broadcast> broadcasts = {};
        std::optional<std::string> winner = std::nullopt;
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
        void requestNewTickRate(int rate, ServerConnect server) { server.sendToServer("sst" + std::to_string(rate)); };


        void setRunning(bool state) { this->isRunning = state; };
        bool getRunning() { return this->isRunning; };

        void setWinner(std::string team) { this->winner = team; };
        std::optional<std::string> getWinner() { return this->winner; };

        /**
        * @brief Add an egg to the game
        * @param values the values of the egg
        * @param playerId the id of the player that laid the egg
        * @param state the state of the egg
        * @return void
        */
        void addEgg(std::vector<int> pos, int eggId, int playerId, EggStatus state);
        std::map<int, Egg> &getEggs() { return this->eggs; };
        Egg &getEggById(int eggid);


        void addTeam(std::string team) { this->teamNames.push_back(team); };
        std::vector<std::string> getTeams() { return this->teamNames; };
        std::string getTeamByName(std::string name);
        bool doesTeamExist(std::string team);


        void addPlayer(std::vector<int> values, std::string teamName);
        std::map<int, std::shared_ptr<Player>> getPlayers() { return players; };

        /**
         * @brief Get the player corresponding to the given id
         * @param id the id of the player (player number)
         * @return a reference to the player
         * @throw guiException if the player does not exist
        */
        std::shared_ptr<Player> getPlayerById(int id);
        bool playerExists(int id);

        std::map<std::vector<int>, Incantation> &getIncantations() { return this->incantations; };
        Incantation &getIncantationByPos(std::vector<int> pos);
        void addIncantation(std::vector<int> pos, int lvl, std::vector<int> playersId);

        std::vector<Broadcast> &getBroadcasts() { return this->broadcasts; };
        std::optional<Broadcast> getNextBroadcast();
        void addBroadcast(int playerNb, std::vector<int> pos, std::string msg);

        Map &getMap() { return this->map; };
};

#endif // DATA_HPP
