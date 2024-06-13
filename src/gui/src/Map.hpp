#ifndef MAP_HPP
    #define MAP_HPP

    #include <vector>

class Tile
{
    private:
        [[ maybe_unused ]] std::vector<int> pos = {0, 0};
        std::vector<int> ressources = std::vector<int>(7, 0);
    public:
        Tile(int x, int y) : pos(std::vector<int>(x, y)) {};
        ~Tile() {};

        void setRessources(std::vector<int> values) { this->ressources = values; };
        std::vector<int> getRessources() { return ressources; };
        int getResAt(int index) { return ressources.at(index); };
};



class Map
{
    private:
        std::vector<std::vector<Tile>> map = {};
    public:
        Map() {};
        ~Map() {};
        int getSize() { return this->map.size();};
        /**
        * @brief Updates a tile on the map
        * @param x The x position of the tile
        * @param y The y position of the tile
        * @param values The values to update the tile with
        * @return void
        */
        void updateTile(int x, int y, std::vector<int> values);
        /**
        * @brief Fills the map with empty tiles
        * @param x The heigth of the map
        * @param y The width of the map
        * @return void
        */
        void fillMap(int x, int y);

};

#endif // MAP_HPP
