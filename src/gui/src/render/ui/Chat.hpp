/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Chat
*/

#ifndef CHAT_HPP_
#define CHAT_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <list>

class Chat {
    public:
        Chat(sf::Font font, int maxMsg) : _font(font), _maxMsg(maxMsg)
        {
            _text.setFont(_font);
            _text.setCharacterSize(17);
            _text.setFillColor(sf::Color::White);
            _text.setPosition(0, 0);
        }
        ~Chat() {

        }

        void addMessage(std::string msg, sf::Color color = sf::Color::White) {
            msg = msg.substr(0, 25);
            if ((int)_messages.size() >= _maxMsg) {
                _messages.pop_back();
            }
            _messages.push_front(std::make_pair(msg, color));
        }

        void draw(sf::RenderWindow &window) {
            int i = 0;
            for (auto msg : _messages) {
                _text.setString(msg.first);
                _text.setPosition(_pos.x, _pos.y -  i * 20);
                _text.setFillColor(msg.second);
                if (i == _maxMsg - 1)
                    _text.setFillColor(sf::Color(msg.second.r, msg.second.g, msg.second.b, 35));
                if (i == _maxMsg - 2)
                    _text.setFillColor(sf::Color(msg.second.r, msg.second.g, msg.second.b, 100));
                if (i == _maxMsg - 3)
                    _text.setFillColor(sf::Color(msg.second.r, msg.second.g, msg.second.b, 200));
                window.draw(_text);
                i++;
            }
        }

        void setPosition(sf::Vector2f pos) {
            _pos = pos;
        }

    protected:
    private:
        sf::Text _text;
        sf::Font _font;
        std::list<std::pair<std::string, sf::Color>> _messages;
        int _maxMsg;
        sf::Vector2f _pos;
};

#endif /* !CHAT_HPP_ */
