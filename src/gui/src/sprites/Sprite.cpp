#include "Sprite.hpp"

void Sprite::update() {
    if (_clock.getElapsedTime().asSeconds() > _frameTime) {
        _frame++;
        if (_frame >= _frameCount)
            _frame = 0;
        _sprite.setTextureRect(
            sf::IntRect(
            _frame * _texture.getSize().x / _frameCount,
            0, _texture.getSize().x / _frameCount,
            _texture.getSize().y
            )
        );
        _clock.restart();
    }
}

void Sprite::setFrame(int frame) {
    if (frame >= _frameCount)
        frame = 0;
    _frame = frame;
    _sprite.setTextureRect(
        sf::IntRect(
            _frame * _texture.getSize().x / _frameCount, 0,
            _texture.getSize().x / _frameCount, _texture.getSize().y
        )
    );
}
