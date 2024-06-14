#ifndef EGG_HPP
    #define EGG_HPP

    #include <vector>

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
        EggStatus state;
    public:
        Egg(std::vector<int> pos, int nb, int playerNb, EggStatus state): pos(pos), nb(nb), playerNb(playerNb), state(state) {};
        ~Egg() {};

        void setState(EggStatus newState) { state = newState; }
        
        EggStatus getState() { return state; }
        std::vector<int> getPos() { return pos; }
        int getId() { return nb; }
        int getPlayerNb() { return playerNb; }
};


#endif // EGG_HPP
