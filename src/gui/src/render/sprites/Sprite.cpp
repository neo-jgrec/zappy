#include "Sprite.hpp"

void Sprite::update(float fElapsedTime) {
    _time += fElapsedTime;
    std::cout << _time << std::endl;
        // std::cout << _frame << std::endl;
    if (_time > _frameTime) {
        _time = 0;
        _frame++;
        std::cout << _frame << std::endl;
        if (_frame >= _frameCount)
            _frame = 0;
        _sprite.setTextureRect(
            sf::IntRect(
                _frame * _frameSize.x, 0,
                _frameSize.x, _frameSize.y
            )
        );

    }
}
