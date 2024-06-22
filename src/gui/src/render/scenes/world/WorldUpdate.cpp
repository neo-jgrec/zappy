#include "World.hpp"
#include "../../core/Core.hpp"
#include "../../../utils/Random.hpp"

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
                color = _teamsColor[trantorian._teamIndex > 5 ? 5 : trantorian._teamIndex];
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
            _chuncks[i][j]._inventory = map.getTileAt(i, j).getRessources();
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
