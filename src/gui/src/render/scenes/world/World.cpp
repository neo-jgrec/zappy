/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world
*/


#include "World.hpp"
#include "../../core/Core.hpp"
#include "../../../utils/Random.hpp"

#include <iostream>

static const std::vector<std::string> _elements = {
    "tree2", "tree4", "stone1", "grass", "grass2"
};

World::World(Core *core)
    : _core(core)
{

    _sprite = std::make_shared<Sprite>("./assets/grass.png");
    _diamond = Diamond(sf::Vector2f(TILE_SIZE_X, TILE_SIZE_Y));
    _sprites["halo1"] = std::make_shared<Sprite>("./assets/halo1.png");
    _sprites["hover1"] = std::make_shared<Sprite>("./assets/hover1.png");
    _sprites["trantorian"] = std::make_shared<Sprite>("./assets/trantorian.png");
    _sprites["trantorian_run"] = std::make_shared<Sprite>("./assets/trantorian_run.png", 6, 1);
    _sprites["grass"] = std::make_shared<Sprite>("./assets/grass_detail(1).png");
    _sprites["grass2"] = std::make_shared<Sprite>("./assets/stone(1).png");
    _sprites["tree2"] = std::make_shared<Sprite>("./assets/trees/tree(2).png");
    _sprites["tree4"] = std::make_shared<Sprite>("./assets/trees/tree(4).png");
    _sprites["stone1"] = std::make_shared<Sprite>("./assets/stone(1).png");
    _view.setSize(sf::Vector2f(1920 , 1080));
    _chat = std::make_shared<Chat>(_core->getFont(), 7);
    _chat->setPosition(sf::Vector2f(50, 720 - 50));
}

void World::init()
{
    while (_core->_data.getMap().getSize()[0] == 0)
        _core->_parser.updateData(_core->_data, _core->_server);
    _worldSize = sf::Vector2f(
        _core->_data.getMap().getSize()[0],
        _core->_data.getMap().getSize()[1]
    );
    PerlinNoise noise;
    _chat->addMessage("Connection to server established");
    _chat->addMessage("World size: " + std::to_string(_worldSize.x) + "x" + std::to_string(_worldSize.y));

    for (int i = 0; i < _worldSize.x; i++) {
        std::vector<Chunck> chuncks;
        for (int j = 0; j < _worldSize.y; j++) {
            Chunck chunck;
            chunck._pos = sf::Vector2f(
                i * TILE_SIZE_MX - j * TILE_SIZE_MX - TILE_SIZE_X / 4 * 3,
                j * TILE_SIZE_MY + i * TILE_SIZE_MY
            );
            chunck._yOffset = noise.noise(i * 0.1, j * 0.1) * 80;
            int nbElements = rand() % 3;

            if (rand() % 2 == 0)
                chunck.addElement(_sprites[_elements[rand() % _elements.size()]]);
            if (chunck._yOffset > 0 && rand() % 2 == 0)
                chunck.addElement(_sprites[_elements[rand() % 2]]);

            chuncks.push_back(chunck);
        }
        _chuncks.push_back(chuncks);
    }

    _pos = sf::Vector2f(
        (int)(_worldSize.x / 2) * TILE_SIZE_MX- (int)(_worldSize.x / 2) * TILE_SIZE_MX - TILE_SIZE_MY,
        (int)(_worldSize.y / 2) * TILE_SIZE_MY + (int)(_worldSize.y / 2) * TILE_SIZE_MY - TILE_SIZE_Y
    );
}

bool World::update(sf::Event event, [[maybe_unused]] sf::RenderWindow &window)
{
    _mousePos = _core->getMousePos();
    _mousePos = sf::Vector2f(
        (_mousePos.x * _zoom + _view.getCenter().x - _view.getSize().x / 2),
        (_mousePos.y * _zoom + _view.getCenter().y - _view.getSize().y / 2)
    );
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        _core->_upperState = GameState::MENU;
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        _isDragging = false;
        _offset = sf::Vector2f(0, 0);
        _tmpOffset = sf::Vector2f(0, 0);
    }
    if (event.type == sf::Event::MouseMoved ||
        event.type == sf::Event::MouseButtonPressed) {
        for (int i = 0; i < _worldSize.x; i++) {
            for (int j = 0; j < _worldSize.y; j++) {
                _diamond.setPosition(sf::Vector2f(
                    _chuncks[i][j]._pos.x,
                    _chuncks[i][j]._pos.y + _chuncks[i][j]._yOffset
                ));
                if (_diamond.checkCollision(_mousePos)) {
                    _hoveredTile = sf::Vector2f(i, j);
                    if (event.mouseButton.button == sf::Mouse::Button::Left)
                        _selectedTile = sf::Vector2f(i, j);
                    break;
                }

            }
        }
    }
    moveMap(event);
    return true;
}

void World::update(float fElapsedTime)
{
    updateTrantorians();
}

void World::draw(sf::RenderWindow &window)
{
    _view.setCenter(sf::Vector2f(
        _pos.x + _tmpOffset.x + _offset.x,
        _pos.y + _tmpOffset.y + _offset.y
    ));
    window.setView(_view);
    for (int i = 0; i < _worldSize.x; i++) {
        for (int j = 0; j < _worldSize.y; j++) {
            drawChunck(window, i, j);
        }
    }
    window.setView(window.getDefaultView());
    _chat->draw(window);
}

void World::drawChunck(sf::RenderWindow &window, int i, int j)
{
    _sprite->_sprite.setPosition(
                _chuncks[i][j]._pos.x,
                _chuncks[i][j]._pos.y + _chuncks[i][j]._yOffset
            );
    window.draw(_sprite->_sprite);
    if (i == _hoveredTile.x && j == _hoveredTile.y && !_isDragging) {
        _sprites["hover1"]->_sprite.setPosition(
            _chuncks[i][j]._pos.x,
            _chuncks[i][j]._pos.y + _chuncks[i][j]._yOffset
        );
        window.draw(_sprites["hover1"]->_sprite);
    }
    _chuncks[i][j].draw(window);
    for (auto &trantorian : _trantorians)
        if (trantorian.getTile().x == i && trantorian.getTile().y == j)
            trantorian.draw(window);
    if (_selectedTile.x == i && _selectedTile.y == j) {
        _sprites["halo1"]->_sprite.setPosition(
            _chuncks[i][j]._pos.x,
            _chuncks[i][j]._pos.y + _chuncks[i][j]._yOffset - TILE_SIZE_Y / 2
        );
        window.draw(_sprites["halo1"]->_sprite);
    }
}

bool World::moveMap(sf::Event event)
{
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {
            _zoom -= 65 * _core->getDeltaTime();
        } else {
            _zoom += 65 * _core->getDeltaTime();
        }
        if (_zoom < 0.25f)
            _zoom = 0.25f;
        if (_zoom > 2)
            _zoom = 2;
        _view.setSize(sf::Vector2f(1920 * _zoom, 1080 * _zoom));
    }
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Button::Left) {
            _isDragging = true;
            _dragStart = _core->getMousePos();
    }
    if (event.type == sf::Event::MouseButtonReleased &&
        event.mouseButton.button == sf::Mouse::Button::Left) {
            _isDragging = false;
            _offset += _tmpOffset;
            _tmpOffset = sf::Vector2f(0, 0);
    }
    if (_isDragging) {
        if (_core->getMousePos().x < 0 || _core->getMousePos().x > 1920 ||
            _core->getMousePos().y < 0 || _core->getMousePos().y > 1080) {
                _isDragging = false;
                _offset += _tmpOffset;
                _tmpOffset = sf::Vector2f(0, 0);
                return true;
            }
        _tmpOffset = (- _core->getMousePos() + _dragStart) * _zoom;
    }
    return true;
}

void World::updateTrantorians()
{
    std::map<int, std::shared_ptr<Player>> players;
    bool exisitingPlayers = false;

    players = _core->_data.getPlayers();
    for (auto &player : players) {
        exisitingPlayers = false;
        auto tile = sf::Vector2f(player.second->getPosition()[0], player.second->getPosition()[1]);
        for (auto &trantorian : _trantorians) {
            if (trantorian._id == player.first) {
                exisitingPlayers = true;
                trantorian.setTile(
                    tile,
                    _chuncks[tile.x][tile.y].getMiddle()
                );
                break;
            }
        }
        if (!exisitingPlayers) {
            Trantorian trantorian(*_sprites["trantorian"], *_sprites["trantorian_run"],
                tile,
                _chuncks[tile.x][tile.y].getMiddle()
            );
            trantorian._id = player.first;
            _trantorians.push_back(trantorian);
        }
    }
    for (auto &trantorian : _trantorians) {
        trantorian.update(_core->getDeltaTime());
    }
}
