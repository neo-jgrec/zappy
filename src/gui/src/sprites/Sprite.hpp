/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** sprite
*/

#ifndef SPRITE_HPP_
    #define SPRITE_HPP_

    #include <SFML/Graphics.hpp>

class Sprite {
    public:
        Sprite(const std::string &path, int frameCount = 1 , float frameTime = 0.1f) : _frame(0), _frameCount(frameCount), _frameTime(frameTime)
        {
            if (!_texture.loadFromFile(path))
                throw std::runtime_error("Cannot load texture");
            _sprite.setTexture(_texture);
        }
        ~Sprite() {};

        void setPosition(sf::Vector2f pos) { _sprite.setPosition(pos); }
        void setSize(sf::Vector2f size) { _sprite.setScale(size); }
        void draw(sf::RenderWindow &window) { window.draw(_sprite); }
        void update();
        void setFrame(int frame);

        sf::Sprite _sprite;
    private:
        sf::Texture _texture;

        int _frame;
        int _frameCount;
        float _frameTime;
        sf::Clock _clock;

};

#endif /* !SPRITE_HPP_ */
