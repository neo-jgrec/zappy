#include "Parser.hpp"
#include "Player.hpp"
#include "Egg.hpp"
#include "Incantation.hpp"
#include "../utils/GuiException.hpp"

#include <cstddef>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>

#include "../utils/Debug.hpp"

// ---------------------------------------------------------------- //
// --------------------------- HANDLERS --------------------------- //
// ---------------------------------------------------------------- //

void Parser::msz (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>(2, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData]() {
        if (gameData.getMap().getMap().size() > 0)
            return;
        int x = std::get<int>(tokens.at(1));
        int y = std::get<int>(tokens.at(2));
        gameData.getMap().fillMap(x, y);
    };
    _queue.push(lambda);
};

void Parser::bct (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>(9, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData]() {
        int x = std::get<int>(tokens.at(1));
        int y = std::get<int>(tokens.at(2));
        std::vector<int> values;
        for (int i = 3; i < 10; i++)
            values.push_back(std::get<int>(tokens.at(i)));
        gameData.getMap().updateTile(x, y, values);
    };
    _queue.push(lambda);
};

void Parser::tna (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>(1, Parser::Type::STRING), __func__);
    auto lambda = [tokens, &gameData]() {
        std::string teamName = std::get<std::string>(tokens.at(1));
        if (!gameData.doesTeamExist(teamName))
            gameData.addTeam(teamName);
    };
    _queue.push(lambda);
};

void Parser::pnw (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>({Parser::Type::INT, Parser::Type::INT, Parser::Type::INT, Parser::Type::INT, Parser::Type::INT, Parser::Type::STRING}), __func__);
    auto lambda = [tokens, &gameData]() {
        debug_print("\npnw", "");
        std::vector<int> values;
        for (int i = 1; i < 6; i++)
            values.push_back(std::get<int>(tokens.at(i)));
        std::string teamName = std::get<std::string>(tokens.at(6));
        gameData.addPlayer(values, teamName);
        debug_print("\\pnw", "");
    };
    _queue.push(lambda);
};

void Parser::ppo (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>(4, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData]() {
        debug_print("\nppo", "");
        Player &player = gameData.getPlayerById(std::get<int>(tokens.at(1)));
        int x = std::get<int>(tokens.at(2));
        int y = std::get<int>(tokens.at(3));
        int orientation = std::get<int>(tokens.at(4));
        player.setPosition(std::vector<int>({x, y}));
        player.setOrientation(orientation);
        debug_print("\\ppo", "");
    };
    _queue.push(lambda);
};

void Parser::plv (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>(2, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData]() {
        debug_print("\nplv", "");
        Player &player = gameData.getPlayerById(std::get<int>(tokens.at(1)));
        int lvl = std::get<int>(tokens.at(2));
        player.setLvl(lvl);
        debug_print("\\plv", "");
    };
    _queue.push(lambda);
};

void Parser::pin (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>(10, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData]() {
        debug_print("\npin", "");
        Player &player = gameData.getPlayerById(std::get<int>(tokens.at(1)));
        std::vector<int> inventory;
        for (int i = 4; i < 11; i++)
            inventory.push_back(std::get<int>(tokens.at(i)));
        player.setInventory(inventory);
        debug_print("\\pin", "");
    };
    _queue.push(lambda);
};

void Parser::pex (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>(1, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData, &server]() {
        int playerNb = std::get<int>(tokens.at(1));
        Player &player = gameData.getPlayerById(playerNb);
        player.setPushed();
        server.sendToServer("ppo " + std::to_string(playerNb) + "\n");
    };
    _queue.push(lambda);
};

void Parser::pbc (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>({Parser::Type::INT, Parser::Type::STRING}), __func__);
    auto lambda = [tokens, &gameData]() {
        debug_print("\npbc", "");
        int playerNb = std::get<int>(tokens.at(1));
        Player player = gameData.getPlayerById(playerNb);
        std::vector<int> pos = player.getPosition();
        std::string msg = std::get<std::string>(tokens.at(2));
        gameData.addBroadcast(playerNb, pos, msg);
        debug_print("\\pbc", "");
    };
    _queue.push(lambda);
};

void Parser::pic (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    auto lambda = [tokens, &gameData]() {
        int x = std::get<int>(tokens.at(1));
        int y = std::get<int>(tokens.at(2));
        std::vector<int> pos = std::vector<int>({x, y});
        int lvl = std::get<int>(tokens.at(3));
        std::vector<int> playersId;

        for (size_t i = 4; i < tokens.size(); i++) {
            int playerNb = std::get<int>(tokens.at(i));
            Player &player = gameData.getPlayerById(playerNb);
            player.setIncanting();
            playersId.push_back(playerNb);
        }
        gameData.addIncantation(pos, lvl, playersId);
    };
    _queue.push(lambda);
};

void Parser::pie (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>(3, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData]() {
        int x = std::get<int>(tokens.at(1));
        int y = std::get<int>(tokens.at(2));
        int result = std::get<int>(tokens.at(3));
        std::vector<int> pos = std::vector<int>({x, y});

        Incantation incantation = gameData.getIncantationByPos(pos);
        incantation.setStatus(result == 0 ? FAILURE : SUCCESS);
    };
    _queue.push(lambda);
};

void Parser::pfk (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>(1, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData]() {
        debug_print("\npfk", "");
        int playerNb = std::get<int>(tokens.at(1));
        Player &player = gameData.getPlayerById(playerNb);
        player.setEgging();
        debug_print("\\pfk", "");
    };
    _queue.push(lambda);
};

void Parser::pdr (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>(2, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData, &server]() {
        int playerNb = std::get<int>(tokens.at(1));
        int resource = std::get<int>(tokens.at(2));
        Player &player = gameData.getPlayerById(playerNb);
        player.setDrop(resource);
        server.sendToServer("pin " + std::to_string(playerNb) + "\n");
        server.sendToServer("ppo " + std::to_string(playerNb) + "\n");
    };
    _queue.push(lambda);
};

void Parser::pgt (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>(2, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData, &server]() {
        int playerNb = std::get<int>(tokens.at(1));
        int resource = std::get<int>(tokens.at(2));
        Player& player = gameData.getPlayerById(playerNb);
        player.setPickup(resource);
        server.sendToServer("pin " + std::to_string(playerNb) + "\n");
        server.sendToServer("ppo " + std::to_string(playerNb) + "\n");
    };
    _queue.push(lambda);
};

void Parser::pdi (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>(1, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData]() {
        debug_print("\npdi", "");
        int playerNb = std::get<int>(tokens.at(1));
        Player& player = gameData.getPlayerById(playerNb);
        player.setAlive(false);
        debug_print("\\pdi", "");
    };
    _queue.push(lambda);
};

void Parser::enw (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>(4, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData]() {
        debug_print("\nenw , """ + std::to_string((std::get<int>(tokens.at(2)))), "");
        int eggNb = std::get<int>(tokens.at(1));
        int playerNb = std::get<int>(tokens.at(2));
        int x = std::get<int>(tokens.at(3));
        int y = std::get<int>(tokens.at(4));
        std::vector<int> pos = std::vector<int>({x, y});
        gameData.addEgg(pos, eggNb, playerNb, INCUBATING);
        debug_print("\\enw", "");
    };
    _queue.push(lambda);
};

void Parser::ebo (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>(1, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData]() {
        int eggNb = std::get<int>(tokens.at(1));
        gameData.getEggById(eggNb).setState(HATCHED);
    };
    _queue.push(lambda);
};

void Parser::edi (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>(1, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData]() {
        int eggNb = std::get<int>(tokens.at(1));
        gameData.getEggById(eggNb).setState(DEAD);
    };
    _queue.push(lambda);
};

void Parser::sst(const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>(1, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData]() {
        gameData.setTickRate(std::get<int>(tokens.at(1)));
    };
    _queue.push(lambda);
};

void Parser::sgt(const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    checkType(tokens, std::vector<Type>(1, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData]() {
        int tickRate = std::get<int>(tokens.at(1));
        gameData.setTickRate(tickRate);
    };
    _queue.push(lambda);
};

void Parser::seg (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]] ServerConnect &server) {
    
    checkType(tokens, std::vector<Type>(1, Parser::Type::STRING), __func__);
    auto lambda = [tokens, &gameData]() {
        std::string teamName = std::get<std::string>(tokens.at(1));
        gameData.setWinner(teamName);
    };
    _queue.push(lambda);
};

void Parser::smg (const std::vector<TokenType>& tokens, [[maybe_unused]] Data& gameData, [[maybe_unused]] ServerConnect &server) {
    
    checkType(tokens, std::vector<Type>(1, Parser::Type::STRING), __func__);
    auto lambda = [tokens]() {
        std::string msg = std::get<std::string>(tokens.at(1));
        std::cout << "server sent: " << msg << std::endl;
    };
    _queue.push(lambda);
};

void Parser::suc (const std::vector<TokenType>& tokens, [[maybe_unused]] Data& gameData, [[maybe_unused]] ServerConnect &server) {
    auto lambda = [tokens]() {
        std::cout << "Unknown command response from the server" << std::endl;
    };
    _queue.push(lambda);
};

void Parser::sbp (const std::vector<TokenType>& tokens, [[maybe_unused]] Data& gameData, [[maybe_unused]] ServerConnect &server) {
    auto lambda = [tokens]() {
        std::cout << "server sent sbp. what for ?" << std::endl;
    };
    _queue.push(lambda);
};


// ---------------------------------------------------------------- //
// -------------------------- EXECUTION --------------------------- //
// ---------------------------------------------------------------- //


void Parser::execute() {
    while (!_queue.empty()) {
        _queue.front()();
        _queue.pop();
    }
};

void Parser::updateData(Data &gameData, ServerConnect &server)
{
    std::string data;
    try {
        data = server.readFromServer();
    } catch (const guiException& e) {
        std::cerr << e.what() << std::endl;
    }

    if (data.compare(std::string("WELCOME\n")) == 0) {
        server.sendToServer("GRAPHIC\n");
        return;
    }

    std::istringstream dataStream(data);
    std::string line;

    while (std::getline(dataStream, line)) {
        boost::tokenizer<> tok(line);
        std::vector<std::string> tokens(tok.begin(), tok.end());
        std::vector<std::variant<std::string, int>> vals;

        for (auto& token : tokens) {
            try {
                int numVal = std::stoi(token);
                vals.push_back(numVal);
            } catch (const std::exception& e) {
                vals.push_back(token);
            }
        }
        parse(vals, gameData, server);
    }
    execute();
}

void Parser::parse(std::vector<TokenType> values, Data& gameData, ServerConnect &server)
{
    if (values.empty() || !std::holds_alternative<std::string>(values.at(0))) {
        throw ParserException("Invalid command format");
    }

    const std::string& command = std::get<std::string>(values.at(0));
    auto it = handlers.find(command);

    if (it != handlers.end()) {
        it->second(values, gameData, server);
    } else {
        std::cerr << "Command not found: " << command << std::endl;
    }
};

void Parser::checkType(const std::vector<TokenType>& tokens, const std::vector<Type>& expectedTypes, const std::string &name) {
    if (tokens.size() != (expectedTypes.size() + 1))
        throw ParserException("Invalid number of arguments for command " + name);
    for (size_t i = 1; i < tokens.size(); i++) {
        if (expectedTypes.at(i - 1) == Parser::Type::INT && !std::holds_alternative<int>(tokens.at(i)))
            throw ParserException("Invalid type for argument " + std::to_string(i) + " in command " + name);
        if (expectedTypes.at(i - 1) == Parser::Type::STRING && !std::holds_alternative<std::string>(tokens.at(i)))
            throw ParserException("Invalid type for argument " + std::to_string(i) + " in command " + name);
    }
};
