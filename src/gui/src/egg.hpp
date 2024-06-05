class Egg
{
private:
    int x;
    int y;
    int Nb;
    int playerNb;
    bool isHatched = false;
public:
    Egg(std::vector<std::string> values);
    ~Egg();
};

Egg::Egg(std::vector<std::string> values)
{
    this->x = std::stoi(values.at(1));
    this->y = std::stoi(values.at(2));
    this->Nb = std::stoi(values.at(3));
    this->playerNb = std::stoi(values.at(4));
}

Egg::~Egg()
{
}
