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
        LvlUpAnim(int id, sf::Vector2f pos, sf::Vector2f tile, int lvl)
            : _id(id), _pos(pos), _tile(tile), _lvl(lvl)
        {
            _lvlup = std::make_shared<Sprite>("./assets/lvlup.png", 8, 0.1f);
            _lvlup->setPosition(_pos);
        }
        ~LvlUpAnim() {}

        enum class LvlUpAnimState {
            START,
            FINISHING,
            FAILURE
        };

        void update(float fElapsedTime) {
            if (_state == LvlUpAnimState::FINISHING)
                _lvlup->update(fElapsedTime);
        }

        void draw(sf::RenderWindow &window) {
            _lvlup->draw(window);
        }

        bool setSuccess() {
            bool ret = false;
            if (_state == LvlUpAnimState::START)
                ret = true;
            _state = LvlUpAnimState::FINISHING;
            return ret;
        }

        void setFailure() {
            _state = LvlUpAnimState::FAILURE;
        }

        bool isFinished() {
            return (_state == LvlUpAnimState::FINISHING && _lvlup->isFinished()) || _state == LvlUpAnimState::FAILURE;
        }

        int getId() {
            return _id;
        }

        sf::Vector2f getTile() {
            return _tile;
        }

        int getLvl() {
            return _lvl;
        }

    protected:
    private:
        int _id;
        sf::Vector2f _pos;
        sf::Vector2f _tile;
        std::shared_ptr<Sprite> _lvlup;
        LvlUpAnimState _state = LvlUpAnimState::START;
        int _lvl;
};

#endif /* !LVLUPANIM_HPP_ */
