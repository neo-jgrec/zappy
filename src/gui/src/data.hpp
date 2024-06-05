#include "map.hpp"
#include "egg.hpp"

class Data
{
    private:
        int tickRate = 0;
        std::vector<std::string> teamNames;
        bool isRunning = false;
        std::vector<Egg> eggs;
    public:
        Data();
        ~Data();

        Map map;

        void setTickRate(int rate) { this->tickRate = rate; };
        int getTickRate() { return this->tickRate; };

        void addEgg(Egg egg) { this->eggs.push_back(egg); };
        void addTeam(std::string team) { this->teamNames.push_back(team); };
};

Data::Data(/* args */)
{
}

Data::~Data()
{
}
