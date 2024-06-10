#ifndef INCANTATION_HPP
    #define INCANTATION_HPP

    #include <vector>

enum IncantationOutcome
{
    FAILURE,
    SUCCESS,
    IN_PROGRESS
};

class Incantation
{
    private:
        std::vector<int> pos;
        int lvl;
        std::vector<int> playersIds;
        IncantationOutcome status = IN_PROGRESS;
    public:
        Incantation(std::vector<int> pos, int lvl, std::vector<int> playersIds) : pos(pos), lvl(lvl), playersIds(playersIds) {};
        ~Incantation() {};

        void setStatus(IncantationOutcome status) { this->status = status; };
        IncantationOutcome getStatus() { return this->status; };

        void addPlayer(int playerId) { this->playersIds.push_back(playerId); };
        std::vector<int> getPlayersId() { return this->playersIds; };

        std::vector<int> getPosition() { return {this->pos}; };
        int getLvl() { return this->lvl; };
};


#endif // INCANTATION_HPP
