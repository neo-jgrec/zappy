
#ifndef BROADCAST_HPP
    #define BROADCAST_HPP

    #include <vector>
    #include <string>

class Broadcast
{
    private:
        std::vector<int> pos;
        std::string message;
        int playerNb;
    public:
        Broadcast(int playerNb, std::string message, std::vector<int> pos) : pos(pos), message(message), playerNb(playerNb) {};
        ~Broadcast() {};

        std::vector<int> getPosition();
        std::string getMessage();
        int getPlayerNb();
};

#endif // BROADCAST_HPP