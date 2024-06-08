#include "parser.hpp"
#include "guiException.hpp"
#include "player.hpp"

#include <string>

void Parser::msz (const std::vector<TokenType>& tokens, Data& gameData) {
    if (std::is_same<std::variant<std::string, int>, std::string>::value)
        throw ParserException("Invalid type for command" + std::string(__func__));
    auto lambda = [tokens, &gameData]() {
        if (gameData.getMap().getSize() > 0)
            return;
        if (tokens.size() < 3)
            throw ParserException("Not enough arguments for command" + std::string(__func__));
        int x = std::get<int>(tokens.at(1));
        int y = std::get<int>(tokens.at(2));
        gameData.getMap().fillMap(x, y);
    };
    _queue.push(lambda);
};

void Parser::bct (const std::vector<TokenType>& tokens, Data& gameData) {
    if (std::is_same<std::variant<std::string, int>, std::string>::value)
        throw ParserException("Invalid type for command" + std::string(__func__));
    auto lambda = [tokens, &gameData]() {
        if (tokens.size() < 10)
            throw ParserException("Not enough arguments for command" + std::string(__func__));
        int x = std::get<int>(tokens.at(1));
        int y = std::get<int>(tokens.at(2));
        std::vector<int> values;
        for (int i = 3; i < 10; i++)
            values.push_back(std::get<int>(tokens.at(i)));
        gameData.getMap().updateTile(x, y, values);
    };
    _queue.push(lambda);
};

void Parser::tna (const std::vector<TokenType>& tokens, Data& gameData) {
    if (std::is_same<std::variant<std::string, int>, int>::value)
        throw ParserException("Invalid type for command" + std::string(__func__));
    auto lambda = [tokens, &gameData]() {
        if (tokens.size() < 2)
            throw ParserException("Not enough arguments for command" + std::string(__func__));
        std::string teamName = std::get<std::string>(tokens.at(1));
        if (!gameData.doesTeamExist(teamName))
            gameData.addTeam(teamName);
    };
    _queue.push(lambda);
};

void Parser::pnw (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        if (tokens.size() < 7)
            throw ParserException("Not enough arguments for command" + std::string(__func__));
        std::vector<int> values;
        for (int i = 1; i < 6; i++)
            values.push_back(std::get<int>(tokens.at(i)));
        std::string teamName = std::get<std::string>(tokens.at(6));
        gameData.addPlayer(values, teamName);
    };
    _queue.push(lambda);
};

void Parser::ppo (const std::vector<TokenType>& tokens, Data& gameData) {
    if (std::is_same<std::variant<std::string, int>, std::string>::value)
        throw ParserException("Invalid type for command" + std::string(__func__));
    auto lambda = [tokens, &gameData]() {
        if (tokens.size() < 4)
            throw ParserException("Not enough arguments for command" + std::string(__func__));
        Player player = gameData.getPlayerAt(std::get<int>(tokens.at(1)));
        int x = std::get<int>(tokens.at(2));
        int y = std::get<int>(tokens.at(3));
        int orientation = std::get<int>(tokens.at(4));
        player.setPosition(x, y);
        player.setOrientation(orientation);
    };
    _queue.push(lambda);
};

void Parser::plv (const std::vector<TokenType>& tokens, Data& gameData) {
    if (std::is_same<std::variant<std::string, int>, std::string>::value)
        throw ParserException("Invalid type for command" + std::string(__func__));
    auto lambda = [tokens, &gameData]() {
        if (tokens.size() < 3)
            throw ParserException("Not enough arguments for command" + std::string(__func__));
        Player player = gameData.getPlayerAt(std::get<int>(tokens.at(1)));
        int lvl = std::get<int>(tokens.at(2));
        player.setLvl(lvl);
    };
    _queue.push(lambda);
};

void Parser::pin (const std::vector<TokenType>& tokens, Data& gameData) {
    if (std::is_same<std::variant<std::string, int>, std::string>::value)
        throw ParserException("Invalid type for command" + std::string(__func__));
    auto lambda = [tokens, &gameData]() {
        if (tokens.size() < 11)
            throw ParserException("Not enough arguments for command" + std::string(__func__));
        Player player = gameData.getPlayerAt(std::get<int>(tokens.at(1)));
        std::vector<int> inventory;
        for (int i = 4; i < 11; i++)
            inventory.push_back(std::get<int>(tokens.at(i)));
        player.setInventory(inventory);
    };
    _queue.push(lambda);
};

void Parser::pex (const std::vector<TokenType>& tokens, Data& gameData) {
    if (std::is_same<std::variant<std::string, int>, std::string>::value)
        throw ParserException("Invalid type for command" + std::string(__func__));
    auto lambda = [tokens, &gameData]() {
        // n | player n is pushing someone
    };
    _queue.push(lambda);
};

void Parser::pbc (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        if (tokens.size() < 3)
            throw ParserException("Not enough arguments for command" + std::string(__func__));
        int playerNb = std::get<int>(tokens.at(1));
        Player player = gameData.getPlayerAt(playerNb);
        std::vector<int> pos = player.getPosition();
        std::string msg = std::get<std::string>(tokens.at(2));
        gameData.addBroadcast(playerNb, pos, msg);
    };
    _queue.push(lambda);
};

void Parser::pic (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // X Y L n n n ... | start of incantation on tile X Y by players n n n ...
    };
    _queue.push(lambda);
};

void Parser::pie (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // // X Y R | end of incantation on tile X Y with result R
        // std::vector<Player> pls = gameData.getPlayers();
        // // int result = std::stoi(tokens.at(3));
        // // int x = std::stoi(tokens.at(1));
        // // int y = std::stoi(tokens.at(2));

        // for (auto &pl : pls) {
        //     if (pl.getPosition() == std::vector(x, y)) {
        //         pl.setIncanting(false);
        //         //server.sendToServer("plv " + std::to_string(pl.getPlayerNb()) + "\n");
        //     }
        // }
    };
    _queue.push(lambda);
};

void Parser::pfk (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // int playerNb = std::stoi(tokens.at(1));
        // Player& player = gameData.getPlayerAt(playerNb);
        // player.setEgging(true);
    };
    _queue.push(lambda);
};

void Parser::pdr (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // n i | player n drops object i
        //std::vector<int> pos = gameData.getPlayerAt(std::stoi(tokens.at(1))).getPosition();
        //server.sendToServer("bct " + std::to_string(pos.at(0)) + " " + std::to_string(pos.at(1)) + "\n");
    };
    _queue.push(lambda);
};

void Parser::pgt (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // n i | player n takes object i
        //std::vector<int> pos = gameData.getPlayerAt(std::stoi(tokens.at(1))).getPosition();
        //server.sendToServer("bct " + std::to_string(pos.at(0)) + " " + std::to_string(pos.at(1)) + "\n");
    };
    _queue.push(lambda);
};

void Parser::pdi (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // int playerNb = std::stoi(tokens.at(1));
        // Player& player = gameData.getPlayerAt(playerNb);
        // player.setAlive(false);
    };
    _queue.push(lambda);
};

void Parser::enw (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // Egg egg(tokens);
        // gameData.addEgg(egg);
        // try {
        //     int playerNb = std::stoi(tokens.at(1));
        //     Player& player = gameData.getPlayerAt(playerNb);
        //     player.setEgging(false);
        // } catch (const guiException& e) {}
    };
    _queue.push(lambda);
};

void Parser::ebo (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // int eggNb = std::stoi(tokens.at(1));
        // gameData.getEggAt(eggNb).setHatched(true);
    };
    _queue.push(lambda);
};

void Parser::edi (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // int eggNb = std::stoi(tokens.at(1));
        // gameData.getEggAt(eggNb).setAlive(false);
    };
    _queue.push(lambda);
};

void Parser::sst(const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // T | set the time unit
    };
    _queue.push(lambda);
};

void Parser::sgt(const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // if (tokens.size() < 2)
        //     return;
        // int tickRate = tokens.at(1);
        // gameData.setTickRate(tickRate);
    };
    _queue.push(lambda);
};

void Parser::seg (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // N | team N won
    };
    _queue.push(lambda);
};

void Parser::smg (const std::vector<TokenType>& tokens, Data& gameData) {
    if (std::is_same<std::variant<std::string, int>, int>::value)
        throw ParserException("Invalid type for command" + std::string(__func__));
    auto lambda = [tokens, &gameData]() {
        if (tokens.size() < 2)
            throw ParserException("Not enough arguments for command" + std::string(__func__));
        std::string msg = std::get<std::string>(tokens.at(1));
        std::cout << "server sent: " << msg << std::endl;
    };
    _queue.push(lambda);
};

void Parser::suc (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        std::cout << "Unknown command response from the server" << std::endl;
    };
    _queue.push(lambda);
};

void Parser::sbp (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        std::cout << "server sent sbp. what for ?" << std::endl;
    };
    _queue.push(lambda);
};

void Parser::execute() {
    while (!_queue.empty()) {
        _queue.front()();
        _queue.pop();
    }
};

