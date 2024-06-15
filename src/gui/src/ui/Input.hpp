/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** button
*/

#ifndef INPUT_HPP_
    #define INPUT_HPP_

    #include <SFML/Graphics.hpp>
    #include <string>

class Input {
    public:
        Input(sf::Vector2f pos, sf::Vector2f size, std::string text, sf::Font &font);
        ~Input() {};

        bool update(sf::Event event, sf::RenderWindow &window);
        void draw(sf::RenderWindow &window, float deltaTime);


        std::string getInput() {
            return _input;
        }

    protected:
    private:
        bool _isFocused = false;
        std::string _input = "";
        std::string _placeHolder = "";
        sf::Text _text;

        float _time = 0;
};

#endif /* !INPUT_HPP_ */
