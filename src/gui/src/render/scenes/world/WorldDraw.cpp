/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world
*/

#include "World.hpp"
#include "../../core/Core.hpp"
#include "../../../utils/Random.hpp"

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
                if ((_worldUi.getPanelState() == WorldUi::panelState::TRANTORIAN &&
                    index == _worldUi._idPlayer) ||
                    (_worldUi.getPanelState() == WorldUi::panelState::FLAG &&
                    trantorian._team == _teams[_worldUi._idTeam])) {
                    _sprites["aura"]->_sprite.setPosition(trantorian.getPos() + sf::Vector2f(0, -40));
                    _sprites["aura"]->setColor(_teamsColor[trantorian._teamIndex > 5 ? 5 : trantorian._teamIndex]);
                    _sprites["aura"]->setScale(_zoom);

                    window.draw(_sprites["aura"]->_sprite);
                }
            }
            if (_zoom > 0.6f)
                continue;
            _sprites["lvlbanner"]->_sprite.setPosition(trantorian.getPos());
            _sprites["lvlbanner"]->setFrame(trantorian._level - 1);
            _sprites["lvlbanner"]->setColor(_teamsColor[trantorian._teamIndex > 5 ? 5 : trantorian._teamIndex]);
            window.draw(_sprites["lvlbanner"]->_sprite);
        }
        index++;
    }
    return ret;
}
