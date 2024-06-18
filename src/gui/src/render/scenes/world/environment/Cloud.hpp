/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** clouds
*/

#ifndef CLOUD_HPP_
#define CLOUD_HPP_

#include "../../../sprites/Sprite.hpp"

class Cloud {
    public:
        Cloud(Sprite *sprite, sf::Vector2f pos, sf::Vector2f speed);
        ~Cloud();

    protected:
    private:
};

#endif /* !CLOUD_HPP_ */
