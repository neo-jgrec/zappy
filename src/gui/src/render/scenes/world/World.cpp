/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world
*/


#include "World.hpp"
#include "../../core/Core.hpp"
#include "../../../utils/Random.hpp"

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
    _sprites["trantorian_death"] = std::make_shared<Sprite>("./assets/trantorian_death.png", 13, 0.1f);
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
    _sprites["lvlup"] = std::make_shared<Sprite>("./assets/lvlup.png", 8, 0.1f);
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
    _core->_tickRate = _core->_data.getTickRate();
    _chat->addMessage("Tick rate: " + std::to_string(_core->_tickRate));
    Ranking::getRanking(_rankings, _core->_data);
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
    _sounds["interact"].setVolume(25);
}

void World::lookTrantorian(int index)
{
    Trantorian trantorian = _trantorians[index];

    sf::Vector2f pos = trantorian.getPos();
    sf::Vector2f viewPos = _pos + _tmpOffset + _offset;
    sf::Vector2f offset = sf::Vector2f(
        pos.x - viewPos.x,
        pos.y - viewPos.y
    );
    _offset += offset;
}

void World::checkWinner()
{
    try {
        std::optional<std::string> winner = _core->_data.getWinner();
        if (winner.has_value()) {
            _core->_winner = winner.value();
            _core->_upperState = GameState::WIN;
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}