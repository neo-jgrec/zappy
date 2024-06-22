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

static const std::vector<sf::Color> _teamsColor = {
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Blue,
    sf::Color::Yellow,
    sf::Color(255, 165, 0),
    sf::Color::Magenta,
};


World::World(Core *core)
    : _core(core), _worldUi(WorldUi(this))
{
    _sprite = std::make_shared<Sprite>("./assets/grass.png");
    _diamond = Diamond(sf::Vector2f(TILE_SIZE_X, TILE_SIZE_Y));
    _sprites["halo1"] = std::make_shared<Sprite>("./assets/halo1.png");
    _sprites["hover1"] = std::make_shared<Sprite>("./assets/hover1.png");
    _sprites["aura"] = std::make_shared<Sprite>("./assets/aura.png", 6, 0.1f);
    _sprites["hoverEgg"] = std::make_shared<Sprite>("./assets/hoverEgg.png");
    _sprites["trantorian_run"] = std::make_shared<Sprite>("./assets/trantorian_run.png", 6, 0.1f);
    _sprites["trantorian_spawn"] = std::make_shared<Sprite>("./assets/trantorian_spawn.png", 12, 0.1f);
    _sprites["grass"] = std::make_shared<Sprite>("./assets/grass_detail(1).png");
    _sprites["grass2"] = std::make_shared<Sprite>("./assets/stone(1).png");
    _sprites["tree2"] = std::make_shared<Sprite>("./assets/trees/tree(2).png");
    _sprites["tree4"] = std::make_shared<Sprite>("./assets/trees/tree(4).png");
    _sprites["stone1"] = std::make_shared<Sprite>("./assets/stone(1).png");
    _sprites["lvlbanner"] = std::make_shared<Sprite>("./assets/lvlBanner.png", 8, 0.1f);
    _sprites["bubble"] = std::make_shared<Sprite>("./assets/bubble.png");
    _view.setSize(sf::Vector2f(1920 , 1080));
    _chat = std::make_shared<Chat>(_core->getFont(), 7);
    _chat->setPosition(sf::Vector2f(50, 720 - 50));
    _bubbleText = sf::Text("", _core->getFont(), 15);
    _bubbleText.setFillColor(sf::Color::Black);
}

void World::init()
{
    reset();
    _chat->addMessage("Connection to server established");
    getServerInit();

    PerlinNoise noise;

    for (int i = 0; i < _worldSize.x; i++) {
        std::vector<Chunck> chuncks;
        for (int j = 0; j < _worldSize.y; j++) {
            Chunck chunck;
            chunck._pos = sf::Vector2f(
                i * TILE_SIZE_MX - j * TILE_SIZE_MX - TILE_SIZE_X / 4 * 3,
                j * TILE_SIZE_MY + i * TILE_SIZE_MY
            );
            chunck._yOffset = noise.noise(i * 0.1, j * 0.1) * 80;
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

void World::reset()
{
    _trantorians.clear();
    _chuncks.clear();
    _worldSize = sf::Vector2f(0, 0);
    _selectedTile = sf::Vector2f(-1, -1);
    _hoveredTile = sf::Vector2f(-1, -1);
    _offset = sf::Vector2f(0, 0);
    _tmpOffset = sf::Vector2f(0, 0);
    _isDragging = false;
    _zoom = 1;
    _view.setSize(sf::Vector2f(1920, 1080));
    _view.setCenter(sf::Vector2f(1920 / 2, 1080 / 2));
    _pos = sf::Vector2f(0, 0);
    _dragStart = sf::Vector2f(0, 0);
}

void World::getServerInit()
{
    while (_core->_data.getMap().getSize()[0] == 0)
        _core->_parser.updateData(_core->_data, _core->_server);
    _worldSize = sf::Vector2f(_core->_data.getMap().getSize()[0], _core->_data.getMap().getSize()[1]);
    _chat->addMessage("World size: " + std::to_string((int)_worldSize.x) + "x" + std::to_string((int)_worldSize.y));
    while (_core->_data.getTeams().size() == 0)
        _core->_parser.updateData(_core->_data, _core->_server);
    _chat->addMessage("Teams: ");
    for (auto &team : _core->_data.getTeams()) {
        _teams.push_back(team);
        _chat->addMessage(" - " + team);
    }

    Ranking::getRanking(_rankings, _core->_data);
}

bool World::update(sf::Event event, [[maybe_unused]] sf::RenderWindow &window)
{
    _worldUi.update(event, window);
    _mousePos = _core->getMousePos() * _zoom + _view.getCenter() - _view.getSize() * (1.f/2.f);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        _core->_upperState = GameState::MENU;
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        _isDragging = false;
        _offset = sf::Vector2f(0, 0);
        _tmpOffset = sf::Vector2f(0, 0);
        _selectedTile = sf::Vector2f(-1, -1);
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
    int i = 0;
    for (auto &bubble : _bubbles) {
        bubble.update(fElapsedTime);
        if (bubble.isFinished())
            _bubbles.erase(_bubbles.begin() + i);
        i++;
    }
    if (_core->_server.connectionState == ServerConnect::ConnectionState::SERVERDOWN
        || _core->_server.connectionState == ServerConnect::ConnectionState::NOTCONNECTED) {
        _core->backToHome();
        return;
    }
    if (_worldUi.getPanelState() != WorldUi::panelState::NONE)
        _sprites["aura"]->update(_core->getDeltaTime());
    updateTrantorians();
    updateChuncks();
    _rankTime += _core->getDeltaTime();
    if (_rankTime > 10)
        Ranking::getRanking(_rankings, _core->_data);
}

void World::draw(sf::RenderWindow &window)
{
    _view.setCenter(_pos + _tmpOffset + _offset);
    window.setView(_view);

    iterateWorld([&](int i, int j) {
        layer1(i, j);
    });
    iterateWorld([&](int i, int j) {
        layer2(i, j);
    });
    window.setView(window.getDefaultView());
    _worldUi.draw(window);
    _chat->draw(window);
}

void World::layer1(int i, int j)
{
    sf::RenderWindow &window = _core->getWindow();
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

    std::map<int, Egg> eggs = _core->_data.getEggs();
    for (auto &egg : eggs) {
        if (egg.second.getState() != EggStatus::HATCHED &&
            egg.second.getPos()[0] == i && egg.second.getPos()[1] == j) {
            _sprites["hoverEgg"]->_sprite.setPosition(
                _chuncks[i][j]._pos.x,
                _chuncks[i][j]._pos.y + _chuncks[i][j]._yOffset
            );
            _sprites["hoverEgg"]->setColor(sf::Color(98, 151, 50));
            window.draw(_sprites["hoverEgg"]->_sprite);
        }
    }
}

void World::layer2(int i, int j)
{
    sf::RenderWindow &window = _core->getWindow();
    bool isThereTrantorian = false;
    int index = 0;
    for (auto &trantorian : _trantorians) {
        if (trantorian.getTile().x == i && trantorian.getTile().y == j) {
            trantorian.draw(window);
            if (trantorian.isDead())
                continue;
            isThereTrantorian = true;
            if (trantorian.getTile().x == i && trantorian.getTile().y == j) {
                if (_worldUi.getPanelState() == WorldUi::panelState::FLAG) {
                    _sprites["aura"]->_sprite.setPosition(trantorian.getPos());
                    _sprites["aura"]->setColor(_teamsColor[_worldUi._idTeam]);
                    if (trantorian._team == _teams[_worldUi._idTeam]) {
                        window.draw(_sprites["aura"]->_sprite);
                    }
                }
                if (_worldUi.getPanelState() == WorldUi::panelState::TRANTORIAN) {
                    if (index == _worldUi._idPlayer) {
                        _sprites["aura"]->_sprite.setPosition(trantorian.getPos());
                        _sprites["aura"]->setColor(_teamsColor[trantorian._teamIndex]);
                        window.draw(_sprites["aura"]->_sprite);
                    }
                }
            }
            if (_zoom > 0.6f)
                continue;
            _sprites["lvlbanner"]->_sprite.setPosition(trantorian.getPos());
            _sprites["lvlbanner"]->setFrame(trantorian._level - 1);
            _sprites["lvlbanner"]->setColor(_teamsColor[trantorian._teamIndex]);
            window.draw(_sprites["lvlbanner"]->_sprite);
        }
        index++;
    }
    if (!isThereTrantorian)
        _chuncks[i][j].draw(window);
    if (_selectedTile.x == i && _selectedTile.y == j) {
        _sprites["halo1"]->_sprite.setPosition(
            _chuncks[i][j]._pos.x,
            _chuncks[i][j]._pos.y + _chuncks[i][j]._yOffset - TILE_SIZE_Y / 2
        );
        window.draw(_sprites["halo1"]->_sprite);
    }
    for (auto &bubble : _bubbles) {
        if (i == bubble.getPos().x && j == bubble.getPos().y) {
            _sprites["bubble"]->_sprite.setPosition(
                _chuncks[i][j].getMiddle());
            window.draw(_sprites["bubble"]->_sprite);
            _bubbleText.setString(bubble.getMessage());
            _bubbleText.setPosition(
                _chuncks[i][j].getMiddle().x + 25,
                _chuncks[i][j].getMiddle().y + -50
            );
            window.draw(_bubbleText);
        }
    }
}

bool World::moveMap(sf::Event event)
{
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0)
            _zoom -= 65 * _core->getDeltaTime();
        else
            _zoom += 65 * _core->getDeltaTime();
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
                trantorian.setTile(tile, _chuncks[tile.x][tile.y].getMiddle());
                trantorian._level = player.second->getLvl();
                trantorian._inventory = player.second->getInventory();
                if (player.second->getAlive() == false)
                    trantorian.kill();
                break;
            }
        }
        if (!exisitingPlayers) {
            std::vector<Sprite> trantorianSprites;

            Trantorian trantorian(tile, _chuncks[tile.x][tile.y].getMiddle());
            trantorian._id = player.first;
            trantorian._team = player.second->getTeam();
            int teamIndex = 0;
            for (auto &team : _teams) {
                if (team == trantorian._team)
                    break;
                teamIndex++;
            }
            trantorian._teamIndex = teamIndex;
            _trantorians.push_back(trantorian);
        }
    }
    for (auto &trantorian : _trantorians)
        trantorian.update(_core->getDeltaTime());
    std::optional<Broadcast> broadcast = _core->_data.getNextBroadcast();
    if (broadcast.has_value()) {
        _chat->addMessage(std::to_string(broadcast.value().getPlayerNb()) + " : " + broadcast.value().getMessage());
        Bubble bubble = Bubble(broadcast.value().getMessage(), sf::Vector2f(broadcast.value().getPosition()[0], broadcast.value().getPosition()[1]));
        _bubbles.push_back(bubble);
    }

}

void World::updateChuncks()
{
    auto &map = _core->_data.getMap();
    for (int i = 0; i < _worldSize.x; i++) {
        for (int j = 0; j < _worldSize.y; j++) {
            _chuncks[i][j]._food = map.getTileAt(i, j).getRessources()[0];
            _chuncks[i][j]._linemate = map.getTileAt(i, j).getRessources()[1];
            _chuncks[i][j]._deraumere = map.getTileAt(i, j).getRessources()[2];
            _chuncks[i][j]._sibur = map.getTileAt(i, j).getRessources()[3];
            _chuncks[i][j]._mendiane = map.getTileAt(i, j).getRessources()[4];
            _chuncks[i][j]._phiras = map.getTileAt(i, j).getRessources()[5];
            _chuncks[i][j]._thystame = map.getTileAt(i, j).getRessources()[6];
            _chuncks[i][j]._nbTrantorians = 0;
            for (auto &trantorian : _trantorians) {
                if (trantorian.getTile().x == i && trantorian.getTile().y == j) {
                    _chuncks[i][j]._nbTrantorians++;
                }
            }
        }
    }
}
