#ifndef EGG_HPP
    #define EGG_HPP

    #include <vector>
    #include <string>

    enum EggStatus {
        INCUBATING,
        READY_TO_HATCH,
        HATCHED,
        DEAD
    };

class Egg
{
    private:
        std::vector<int> pos;
        [[maybe_unused]] int nb;
        [[maybe_unused]] int playerNb;
        [[maybe_unused]] std::string team;
        EggStatus state;
    public:
        Egg(std::vector<int> pos, int nb, int playerNb, EggStatus state, std::string team);
        ~Egg() {};

        void setState(EggStatus newState);

        EggStatus getState();
        std::vector<int> getPos();
        int getId();
        int getPlayerNb();
        std::string getTeam();
};


#endif // EGG_HPP
