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
        void setState(EggStatus newState) { state = newState; }

        Egg(std::vector<int> pos, int nb, int playerNb, EggStatus state): pos(pos), nb(nb), playerNb(playerNb), state(state) {};
        ~Egg() {};
};


#endif // EGG_HPP
