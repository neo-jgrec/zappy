#ifndef INCANTATION_HPP
    #define INCANTATION_HPP

    #include <vector>

class Incantation
{
enum outcome {IN_PROGRESS, SUCCESS, FAILURE};

private:
    int x;
    int y;
    int lvl;
    outcome status = IN_PROGRESS;
public:
    Incantation(int x, int y, int lvl) : x(x), y(y), lvl(lvl) {};
    ~Incantation() {};

    void setStatus(outcome status) { this->status = status; };
    outcome getStatus() { return this->status; };

    std::vector<int> getPosition() { return {this->x, this->y}; };
    int getLvl() { return this->lvl; };
};


#endif // INCANTATION_HPP
