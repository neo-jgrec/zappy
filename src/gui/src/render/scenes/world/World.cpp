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
    _sprites["background"] = std::make_shared<Sprite>("assets/background.jpg");
    _sprites["background"]->resetOrigin();
    _sprites["starling"] = std::make_shared<Sprite>("assets/trantorian.png");
    _sprites["starling"]->setScale(2);
    _sprites["buildings"] = std::make_shared<Sprite>("./assets/houses.png", 8, 0.1f);
    _view.setSize(sf::Vector2f(1920 , 1080));
    _chat = std::make_shared<Chat>(_core->getFont(), 7);
    _bubbleText = sf::Text("", _core->getFont(), 15);
    _bubbleText.setFillColor(sf::Color::Black);
    initSounds();
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

    for (int i = 0; i < _worldSize.x; i++) {
        std::vector<int> innerVector(_worldSize.y, 0);
        _buildings.push_back(innerVector);
    }

    _pos = sf::Vector2f(
        (int)(_worldSize.x / 2) * TILE_SIZE_MX- (int)(_worldSize.x / 2) * TILE_SIZE_MX - TILE_SIZE_MY,
        (int)(_worldSize.y / 2) * TILE_SIZE_MY + (int)(_worldSize.y / 2) * TILE_SIZE_MY - TILE_SIZE_Y
    );

    _starlings.push_back(Starlings());
    _starlings.push_back(Starlings());
    _starlings.push_back(Starlings());
    _starlings.push_back(Starlings());
    _starlings.push_back(Starlings());
}

void World::reset()
{
    _trantorians.clear();
    _buildings.clear();
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
                    if (event.mouseButton.button == sf::Mouse::Button::Left) {
                        _selectedTile = sf::Vector2f(i, j);
                        _sounds["interact"].stop();
                        _sounds["interact"].play();
                    }
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
    updateIncantation();
    _rankTime += _core->getDeltaTime();
    if (_rankTime > 10)
        Ranking::getRanking(_rankings, _core->_data);
    if (_core->_funMode)
        for (auto &starling : _starlings)
            starling.update(fElapsedTime);
}

void World::draw(sf::RenderWindow &window)
{
    _sprites["background"]->draw(window);
    if (_core->_funMode)
        for (auto &starling : _starlings) {
            _sprites["starling"]->setPosition(starling._pos);
            _sprites["starling"]->setRotation(starling._rotation);
            _sprites["starling"]->draw(window);
        }
    _view.setCenter(_pos + _tmpOffset + _offset);
    _viewRect = sf::FloatRect(
        _view.getCenter().x - _view.getSize().x / 2 - 50,
        _view.getCenter().y - _view.getSize().y / 2 - 50,
        _view.getSize().x + 100,
        _view.getSize().y + 100
    );
    window.setView(_view);

    iterateWorld([&](int i, int j) {
        layer1(i, j);
    });
    iterateWorld([&](int i, int j) {
        layer2(i, j);
    });
    window.setView(window.getDefaultView());
    _worldUi.draw(window);
    _chat->setPosition(sf::Vector2f(
        50,
        window.getSize().y - 50
    ));
    _chat->draw(window);
}

void World::layer1(int i, int j)
{
    if (_viewRect.contains(_chuncks[i][j].getMiddle()) == false)
        return;
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
    if (_viewRect.contains(_chuncks[i][j].getMiddle()) == false)
        return;
    sf::RenderWindow &window = _core->getWindow();
    if (!drawBuilding(window, i, j) && !drawTrantorian(window, i, j))
        _chuncks[i][j].draw(window);
    bool incantation = false;
    for (auto &lvlUpAnim : _lvlUpAnims)
        if (lvlUpAnim.getTile().x == i && lvlUpAnim.getTile().y == j) {
            lvlUpAnim.draw(window);
            incantation = true;
        }
    if (!incantation && _selectedTile.x == i && _selectedTile.y == j) {
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

bool World::drawBuilding(sf::RenderWindow &window, int i, int j)
{
    bool ret = false;
    if (_buildings[i][j] != 0 &&
        _worldUi.getPanelState() != WorldUi::panelState::FLAG &&
        _worldUi.getPanelState() != WorldUi::panelState::TRANTORIAN) {
        _sprites["buildings"]->_sprite.setPosition(
            _chuncks[i][j]._pos.x,
            _chuncks[i][j]._pos.y + _chuncks[i][j]._yOffset - TILE_SIZE_Y / 2
        );
        _sprites["buildings"]->setFrame(_buildings[i][j] - 1);
        window.draw(_sprites["buildings"]->_sprite);
        ret = true;
    }
    return ret;
}

bool World::drawTrantorian(sf::RenderWindow &window, int i, int j)
{
    bool ret = false;
    int index = 0;

    for (auto &trantorian : _trantorians) {
        if (trantorian.getTile().x == i && trantorian.getTile().y == j) {
            trantorian.draw(window);
            if (trantorian.isDead())
                continue;
            ret = true;
            if (trantorian.getTile().x == i && trantorian.getTile().y == j) {
                if (_worldUi.getPanelState() == WorldUi::panelState::FLAG) {
                    if (trantorian._team == _teams[_worldUi._idTeam]) {
                        _sprites["aura"]->_sprite.setPosition(trantorian.getPos());
                        _sprites["aura"]->setColor(_teamsColor[_worldUi._idTeam]);
                        _sprites["aura"]->setScale(_zoom);
                        window.draw(_sprites["aura"]->_sprite);
                    }
                }
                if (_worldUi.getPanelState() == WorldUi::panelState::TRANTORIAN) {
                    if (index == _worldUi._idPlayer) {
                        _sprites["aura"]->_sprite.setPosition(trantorian.getPos());
                        _sprites["aura"]->setColor(_teamsColor[trantorian._teamIndex]);
                        _sprites["aura"]->setScale(_zoom);

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
    return ret;
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
                trantorian._facing = player.second->getOrientation();
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
        if (_bubbles.size() > 6)
            return;
        sf::Color color = sf::Color::White;
        for (auto &trantorian : _trantorians) {
            if (trantorian._id == broadcast.value().getPlayerNb()) {
                color = _teamsColor[trantorian._teamIndex];
                break;
            }
        }
        int random = rand() % 2;
        _sounds["talk1"].stop();
        _sounds["talk2"].stop();
        if (random == 0)
            _sounds["talk1"].play();
        else
            _sounds["talk2"].play();
        _chat->addMessage(std::to_string(broadcast.value().getPlayerNb()) + " : " + broadcast.value().getMessage(), color);
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
            for (auto &trantorian : _trantorians)
                if (trantorian.getTile().x == i && trantorian.getTile().y == j)
                    _chuncks[i][j]._nbTrantorians++;
        }
    }
}

void World::updateIncantation()
{
    auto incantations = _core->_data.getIncantations();

    if ((int)incantations.size() != _nbIncantations) {
        _chat->addMessage("Incantation started");
        _sounds["wololo"].stop();
        _sounds["wololo"].play();
        auto incantation = incantations[incantations.size() - 1];
        sf::Vector2f tile = sf::Vector2f(incantation->getPosition()[0], incantation->getPosition()[1]);
        sf::Vector2f pos = _chuncks[tile.x][tile.y].getMiddle();
        _lvlUpAnims.push_back(LvlUpAnim(incantations.size() - 1,
            pos, tile,
            incantation->getLvl()));
        _nbIncantations = incantations.size();
    }
    for (auto &lvlUpAnim : _lvlUpAnims) {
        int state = incantations[lvlUpAnim.getId()]->getStatus();
        if (state == IncantationOutcome::SUCCESS)
            if (lvlUpAnim.setSuccess()) {
                _chat->addMessage("Incantation success");
                _sounds["hourray"].stop();
                _sounds["hourray"].play();
                _buildings[lvlUpAnim.getTile().x][lvlUpAnim.getTile().y] = lvlUpAnim.getLvl();
            }
        if (state == IncantationOutcome::FAILURE)
            lvlUpAnim.setFailure();
        lvlUpAnim.update(_core->getDeltaTime());
        if (lvlUpAnim.isFinished())
            _lvlUpAnims.erase(_lvlUpAnims.begin());
    }
}

void World::initSounds()
{
    _sounds["talk1"].openFromFile("./assets/audio/talk1.ogg");
    _sounds["talk1"].setVolume(100);
    _sounds["talk2"].openFromFile("./assets/audio/talk2.ogg");
    _sounds["talk2"].setVolume(100);
    _sounds["hourray"].openFromFile("./assets/audio/hourray.ogg");
    _sounds["hourray"].setVolume(100);
    _sounds["wololo"].openFromFile("./assets/audio/wololo.ogg");
    _sounds["wololo"].setVolume(100);
    _sounds["interact"].openFromFile("./assets/audio/interact.ogg");
    _sounds["interact"].setVolume(50);
}