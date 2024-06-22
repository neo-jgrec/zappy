/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** LvlUpAnim
*/

#ifndef LVLUPANIM_HPP_
#define LVLUPANIM_HPP_

#include "../../../sprites/Sprite.hpp"

class LvlUpAnim {
    public:
        LvlUpAnim(int id, sf::Vector2f pos)
            : _id(id), _pos(pos), _sprite(Sprite("./assets/lvlup.png", 8, 0.1f))
        {
            _sprite.setPosition(_pos);
        }
        ~LvlUpAnim();

        enum class LvlUpAnimState {
            START,
            FINISHING,
        };

        void update(float fElapsedTime) {
            if (_state == LvlUpAnimState::FINISHING)
                _sprite.update(fElapsedTime);
        }

        void draw(sf::RenderWindow &window) {
            _sprite.draw(window);
        }

        bool isFinished() {
            return _state == LvlUpAnimState::FINISHING && _sprite.isFinished();
        }

    protected:
    private:
        int _id;
        sf::Vector2f _pos;
        Sprite _sprite;
        LvlUpAnimState _state = LvlUpAnimState::START;
};

#endif /* !LVLUPANIM_HPP_ */
