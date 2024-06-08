#include "map.hpp"
#include "guiException.hpp"


void Map::updateTile(int x, int y, std::vector<int> values)
{
    if (x >= this->map.size() || y >= this->map.at(0).size()) {
        throw guiException("Invalid tile position");
    }
    map[x][y].setRessources(values);
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
