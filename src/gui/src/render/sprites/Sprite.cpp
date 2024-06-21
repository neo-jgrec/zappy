#include "Sprite.hpp"

int Sprite::update(float fElapsedTime) {
    int ret = 0;
    _time += fElapsedTime;
    if (_time > _frameTime) {
        _time = 0;
        _frame++;
        if (_frame >= _frameCount) {
            if (_looping)
                _frame = 0;
            else {
                ret = 1;
                _frame = _frameCount - 1;
            }
        }
        _sprite.setTextureRect(sf::IntRect(_frame * _frameSize.x, 0, _frameSize.x, _frameSize.y));
    }
    return ret;
}
