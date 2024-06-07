#ifndef MAP_HPP
    #define MAP_HPP

    #include <vector>
    #include <stdexcept>


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
        ~Tile() {};

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
            if (values.size() != 10) {
                throw std::invalid_argument("Invalid tile size");
            }
            this->q0 = std::stoi(values.at(3));
            this->q1 = std::stoi(values.at(4));
            this->q2 = std::stoi(values.at(5));
            this->q3 = std::stoi(values.at(6));
            this->q4 = std::stoi(values.at(7));
            this->q5 = std::stoi(values.at(8));
            this->q6 = std::stoi(values.at(9));
        };

        std::vector<int> getTileValues()
        {
            std::vector<int> tile = {
                this->q0,
                this->q1,
                this->q2,
                this->q3,
                this->q4,
                this->q5,
                this->q6
            };
            return tile;
        };
};



class Map
{
    private:
        std::vector<std::vector<Tile>> map;
    public:
        Map() {};
        ~Map() {};
        int getSize() { return this->map.size();};
        /**
        * @brief Updates a tile on the map
        * @param values The values to update the tile with
        * @return void
        */
        void updateTile(std::vector<std::string> values);
        /**
        * @brief Fills the map with empty tiles
        * @param x The heigth of the map
        * @param y The width of the map
        * @return void
        */
        void fillMap(int x, int y);

};

#endif // MAP_HPP
