#include "parser.hpp"
#include "guiException.hpp"

#include <string>

void Parser::msz (const std::vector<TokenType>& tokens, Data& gameData) {
    if (std::is_same<std::variant<std::string, int>, std::string>::value)
        throw ParserException("Invalid type for command" + std::string(__func__));
    auto lambda = [tokens, &gameData]() {
        if (gameData.getMap().getSize() > 0)
            return;
        if (tokens.size() < 3)
            throw guiException("Not enough arguments");
        int x = std::get<int>(tokens.at(1));
        int y = std::get<int>(tokens.at(2));
        gameData.getMap().fillMap(x, y);
    };
    _queue.push(lambda);
};

void Parser::bct (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // gameData.getMap().updateTile(tokens);
    };
    _queue.push(lambda);
};

void Parser::tna (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        std::string teamName = std::get<std::string>(tokens.at(1));
        if (!gameData.doesTeamExist(teamName))
            gameData.addTeam(teamName);
    };
    _queue.push(lambda);
};

void Parser::pnw (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // gameData.addPlayer(tokens);
    };
    _queue.push(lambda);
};

void Parser::ppo (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // std::cout << tokens.at(1) << std::endl;
        // gameData.getPlayerAt(std::stoi(tokens.at(1))).move(std::stoi(tokens.at(2)), std::stoi(tokens.at(3)));
    };
    _queue.push(lambda);
};

void Parser::plv (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // std::cout << tokens.at(1) << std::endl;
        // gameData.getPlayerAt(std::stoi(tokens.at(1))).setLevel(std::stoi(tokens.at(2)));
    };
    _queue.push(lambda);
};

void Parser::pin (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // std::cout << tokens.at(1) << std::endl;
        // gameData.getPlayerAt(std::stoi(tokens.at(1))).setInventory(std::stoi(tokens.at(2)), std::stoi(tokens.at(3)), std::stoi(tokens.at(4)), std::stoi(tokens.at(5)), std::stoi(tokens.at(6)), std::stoi(tokens.at(7)), std::stoi(tokens.at(8)), std::stoi(tokens.at(9)));
    };
    _queue.push(lambda);
};

void Parser::pex (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // n | player n is pushing someone
    };
    _queue.push(lambda);
};

void Parser::pbc (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // std::cout << tokens.at(1) << std::endl;
        // gameData.getPlayerAt(std::stoi(tokens.at(1))).broadcast(tokens.at(2));
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
    auto lambda = [tokens, &gameData]() {
        // if (tokens.size() < 2)
        //     return;
        // std::string msg = tokens.at(1);
        // std::cout << "server sent: " << msg << std::endl;
    };
    _queue.push(lambda);
};

void Parser::suc (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // unknown command
    };
    _queue.push(lambda);
};

void Parser::sbp (const std::vector<TokenType>& tokens, Data& gameData) {
    auto lambda = [tokens, &gameData]() {
        // command parameter
    };
    _queue.push(lambda);
};

void Parser::execute() {
    while (!_queue.empty()) {
        _queue.front()();
        _queue.pop();
    }
};

