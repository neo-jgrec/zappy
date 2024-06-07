#include "map.hpp"


void Map::updateTile(std::vector<std::string> values)
{
    int x = std::stoi(values.at(1));
    int y = std::stoi(values.at(2));

    if (x >= this->map.size() || y >= this->map.at(0).size()) {
        throw std::invalid_argument("Invalid tile position");
    }
    map[x][y].update(values);
}


void Map::fillMap(int x, int y)
{
    for (; x > 0; x--) {
        std::vector<Tile> row;
        for (int i = 0;i < y; i++) {
            row.push_back(Tile(x, y));
        }
        this->map.push_back(row);
    }
}
