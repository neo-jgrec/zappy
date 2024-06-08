#ifndef EGG_HPP
    #define EGG_HPP

    #include <vector>

    enum Status {
        INCUBATING,
        READY_TO_HATCH,
        HATCHED,
        DEAD
    };

class Egg
{
    private:
        std::vector<int> pos;
        int nb;
        int playerNb;
        Status state;
    public:
        void setState(Status newState) { state = newState; }

        Egg(std::vector<int> pos, int nb, int playerNb, Status state): pos(pos), nb(nb), playerNb(playerNb), state(state) {};
        ~Egg() {};
};


#endif // EGG_HPP
