/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** chunck
*/

#ifndef CHUNCK_HPP_
    #define CHUNCK_HPP_

    #include <SFML/Graphics.hpp>

class Chunck {
    public:
        Chunck() {}
        ~Chunck() {}

        sf::Vector2i _pos;
        float _yOffset;
        bool _hover = false;

    private:
        int _food;
        int _linemate;
        int _deraumere;
        int _sibur;
        int _mendiane;
        int _phiras;
        int _thystame;

};

#endif /* !CHUNCK_HPP_ */
