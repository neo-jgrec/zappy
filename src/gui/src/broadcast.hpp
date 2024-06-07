
#ifndef BROADCAST_HPP
    #define BROADCAST_HPP

    #include <vector>
    #include <string>

class Broadcast
{
private:
    int x;
    int y;
    std::string message;
    int playerNb;
public:
    Broadcast(int playerNb, std::string message, std::vector<int> pos) : playerNb(playerNb), message(message), x(pos.at(0)), y(pos.at(1)) {};
    ~Broadcast() {};

    std::vector<int> getPosition() { return {this->x, this->y}; };
    std::string getMessage() { return this->message; };
    int getPlayerNb() { return this->playerNb; };
};

#endif // BROADCAST_HPP