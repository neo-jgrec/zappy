/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Trantorien
*/

#ifndef TRANTORIEN_HPP_
#define TRANTORIEN_HPP_

#include "../../sprites/Sprite.hpp"

class Trantorien {
    public:
        Trantorien(Sprite sprite)
            : _sprite(sprite)
        {
        }
        ~Trantorien() {
        }

    protected:
    private:
        Sprite _sprite;
};

#endif /* !TRANTORIEN_HPP_ */
