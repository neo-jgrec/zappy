#include <vector>
#include <stdexcept>
#include <iostream>
#include "utils/Exception.hpp"

class Tile
{
    private:
        int x;
        int y;
        int q0 = 0;
        int q1 = 0;
        int q2 = 0;
        int q3 = 0;
        int q4 = 0;
        int q5 = 0;
        int q6 = 0;
    public:
        Tile(int x, int y) : x(x), y(y) {};
        ~Tile();

        void setQ0(int q0) { this->q0 = q0; };
        int getQ0() { return this->q0; };
        void setQ1(int q1) { this->q1 = q1; };
        int getQ1() { return this->q1; };
        void setQ2(int q2) { this->q2 = q2; };
        int getQ2() { return this->q2; };
        void setQ3(int q3) { this->q3 = q3; };
        int getQ3() { return this->q3; };
        void setQ4(int q4) { this->q4 = q4; };
        int getQ4() { return this->q4; };
        void setQ5(int q5) { this->q5 = q5; };
        int getQ5() { return this->q5; };
        void setQ6(int q6) { this->q6 = q6; };
        int getQ6() { return this->q6; };

        void update(std::vector<std::string> values)
        {
            try {
                this->q0 = std::stoi(values.at(3));
                this->q1 = std::stoi(values.at(4));
                this->q2 = std::stoi(values.at(5));
                this->q3 = std::stoi(values.at(6));
                this->q4 = std::stoi(values.at(7));
                this->q5 = std::stoi(values.at(8));
                this->q6 = std::stoi(values.at(9));
            } catch (const std::out_of_range& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        };

        std::vector<int> getTile()
        {
            std::vector<int> tile = {this->q0, this->q1, this->q2, this->q3, this->q4, this->q5, this->q6};
            return tile;
        };
};

Tile::~Tile()
{
}


class Map
{
    private:
        std::vector<std::vector<Tile>> map;
    public:
        Map();
        ~Map();
        void fillMap(int x, int y);
        void updateTile(std::vector<std::string> values);
        int getSize() { return this->map.size();};
};

void Map::updateTile(std::vector<std::string> values)
{
    int x = std::stoi(values.at(1));
    int y = std::stoi(values.at(2));
    // std::cout << "updating tile " << x << " " << y << std::endl;
    map[x][y].update(values);
    // std::cout << "update ended" << std::endl;
}

void Map::fillMap(int x, int y)
{
    // std::cout << "Filling map with sizes:" << x << " " << y << std::endl;
    for (; x > 0; x--) {
        std::vector<Tile> row;
        for (int i = 0;i < y; i++) {
            row.push_back(Tile(x, y));
        }
        this->map.push_back(row);
    }
    // std::cout << "Map filled" << std::endl;
}

Map::Map()
{
}

Map::~Map()
{
}
