
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
    Broadcast(int playerNb, std::string message, std::vector<int> pos) : playerNb(playerNb), message(message), pos(pos) {};
    ~Broadcast() {};

    std::vector<int> getPosition() { return this->pos; };
    std::string getMessage() { return this->message; };
    int getPlayerNb() { return this->playerNb; };
};

#endif // BROADCAST_HPP