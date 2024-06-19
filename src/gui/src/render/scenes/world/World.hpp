/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world
*/

#ifndef WORLD_HPP_
    #define WORLD_HPP_

    #include <SFML/Graphics.hpp>
    #include <memory>

    #include "../../../utils/PerlinNoise.hpp"
    #include "Chunck.hpp"
    #include "Trantorian.hpp"
    #include "../IScene.hpp"
    #include "shape/diamond.hpp"

    #include "../../sprites/Sprite.hpp"
    #include "../../core/Setting.hpp"
    #include "../../ui/Chat.hpp"

class Core;
class World : public IScene {
    public:
        World(Core *core);
        ~World() {}


        void init() override;
        bool update(sf::Event event, sf::RenderWindow &window) override;
        void update(float fElapsedTime) override;
        void draw(sf::RenderWindow &window) override;

        void drawChunck(sf::RenderWindow &window, int i, int j);
        bool moveMap(sf::Event event);
        void updateTrantorians();

    private:
        std::shared_ptr<Sprite> _sprite;
        std::map<std::string, std::shared_ptr<Sprite>> _sprites;

        sf::Vector2f _worldSize;
        std::vector<Trantorian> _trantorians;
        std::vector<std::vector<Chunck>> _chuncks;

        sf::View _view;
        sf::Vector2f _pos = sf::Vector2f(0, 0);
        sf::Vector2f _offset;
        sf::Vector2f _tmpOffset = sf::Vector2f(0, 0);

        bool _isDragging = false;
        sf::Vector2f _dragStart = sf::Vector2f(0, 0);
        float _zoom = 1;
        float _zoomSpeed = 0.1;
        float _moveSpeed = 10;

        Core *_core;
        sf::Vector2f _hoveredTile;
        sf::Vector2f _selectedTile = sf::Vector2f(-1, -1);
        sf::Vector2f _mousePos;
        std::shared_ptr<Chat> _chat;

        // ----- this is temporary -----
        Diamond _mapDiamond;
        Diamond _diamond;
};


#endif /* !WORLD_HPP_ */
