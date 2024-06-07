#ifndef PARSER_HPP
    #define PARSER_HPP

    #include <map>
    #include <functional>
    #include <variant>
    #include <vector>
    #include <string>
    #include <queue>
    #include <iostream>


    #include "data.hpp"

class Parser
{
private:

    
    std::queue<std::function<void()>> _queue;
    void msz (std::vector<std::variant<std::string, int>> values, Data& gameData);
    void bct (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void tna (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void pnw (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void ppo (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void plv (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void pin (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void pex (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void pbc (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void pic (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void pie (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void pfk (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void pdr (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void pgt (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void pdi (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void enw (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void ebo (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void edi (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void sst (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void sgt (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void seg (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void smg (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void suc (std::vector<std::variant<std::string, int>> tokens, Data& gameData);
    void sbp (std::vector<std::variant<std::string, int>> tokens, Data& gameData);


    std::map<std::string, std::function<void(std::vector<std::variant<std::string, int>>, Data&)>> handlers = {
        {"msz", std::bind(&Parser::msz, this, std::placeholders::_1, std::placeholders::_2)},
        {"bct", std::bind(&Parser::bct, this, std::placeholders::_1, std::placeholders::_2)},
        {"tna", std::bind(&Parser::tna, this, std::placeholders::_1, std::placeholders::_2)},
        {"pnw", std::bind(&Parser::pnw, this, std::placeholders::_1, std::placeholders::_2)},
        {"ppo", std::bind(&Parser::ppo, this, std::placeholders::_1, std::placeholders::_2)},
        {"plv", std::bind(&Parser::plv, this, std::placeholders::_1, std::placeholders::_2)},
        {"pin", std::bind(&Parser::pin, this, std::placeholders::_1, std::placeholders::_2)},
        {"pex", std::bind(&Parser::pex, this, std::placeholders::_1, std::placeholders::_2)},
        {"pbc", std::bind(&Parser::pbc, this, std::placeholders::_1, std::placeholders::_2)},
        {"pic", std::bind(&Parser::pic, this, std::placeholders::_1, std::placeholders::_2)},
        {"pie", std::bind(&Parser::pie, this, std::placeholders::_1, std::placeholders::_2)},
        {"pfk", std::bind(&Parser::pfk, this, std::placeholders::_1, std::placeholders::_2)},
        {"pdr", std::bind(&Parser::pdr, this, std::placeholders::_1, std::placeholders::_2)},
        {"pgt", std::bind(&Parser::pgt, this, std::placeholders::_1, std::placeholders::_2)},
        {"pdi", std::bind(&Parser::pdi, this, std::placeholders::_1, std::placeholders::_2)},
        {"enw", std::bind(&Parser::enw, this, std::placeholders::_1, std::placeholders::_2)},
        {"ebo", std::bind(&Parser::ebo, this, std::placeholders::_1, std::placeholders::_2)},
        {"edi", std::bind(&Parser::edi, this, std::placeholders::_1, std::placeholders::_2)},
        {"sst", std::bind(&Parser::sst, this, std::placeholders::_1, std::placeholders::_2)},
        {"sgt", std::bind(&Parser::sgt, this, std::placeholders::_1, std::placeholders::_2)},
        {"seg", std::bind(&Parser::seg, this, std::placeholders::_1, std::placeholders::_2)},
        {"smg", std::bind(&Parser::smg, this, std::placeholders::_1, std::placeholders::_2)},
        {"suc", std::bind(&Parser::suc, this, std::placeholders::_1, std::placeholders::_2)},
        {"sbp", std::bind(&Parser::sbp, this, std::placeholders::_1, std::placeholders::_2)}
    };
public:
    Parser() = default;
    ~Parser() = default;

    void parse(std::vector<std::variant<std::string, int>> values, Data& gameData)
    {
        if(handlers.find(std::get<std::string>(values.at(0))) == handlers.end()) {
            std::cout << "command not found: " << std::get<std::string>(values.at(0)) << std::endl;
            return;
        }
        handlers.at(std::get<std::string>(values.at(0)))(values, gameData);
    };
    void execute();
};

#endif // PARSER_HPP
