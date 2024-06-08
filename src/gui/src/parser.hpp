#ifndef PARSER_HPP
    #define PARSER_HPP

    #include <iostream>
    #include <map>
    #include <functional>
    #include <variant>
    #include <vector>
    #include <string>
    #include <queue>

    #include "data.hpp"

class Parser
{
private:

    using TokenType = std::variant<std::string, int>;
    using Handler = std::function<void(const std::vector<TokenType>&, Data&)>;

    std::queue<std::function<void()>> _queue;

    void msz(const std::vector<TokenType>& values, Data& gameData);
    void bct(const std::vector<TokenType>& tokens, Data& gameData);
    void tna(const std::vector<TokenType>& tokens, Data& gameData);
    void pnw(const std::vector<TokenType>& tokens, Data& gameData);
    void ppo(const std::vector<TokenType>& tokens, Data& gameData);
    void plv(const std::vector<TokenType>& tokens, Data& gameData);
    void pin(const std::vector<TokenType>& tokens, Data& gameData);
    void pex(const std::vector<TokenType>& tokens, Data& gameData);
    void pbc(const std::vector<TokenType>& tokens, Data& gameData);
    void pic(const std::vector<TokenType>& tokens, Data& gameData);
    void pie(const std::vector<TokenType>& tokens, Data& gameData);
    void pfk(const std::vector<TokenType>& tokens, Data& gameData);
    void pdr(const std::vector<TokenType>& tokens, Data& gameData);
    void pgt(const std::vector<TokenType>& tokens, Data& gameData);
    void pdi(const std::vector<TokenType>& tokens, Data& gameData);
    void enw(const std::vector<TokenType>& tokens, Data& gameData);
    void ebo(const std::vector<TokenType>& tokens, Data& gameData);
    void edi(const std::vector<TokenType>& tokens, Data& gameData);
    void sst(const std::vector<TokenType>& tokens, Data& gameData);
    void sgt(const std::vector<TokenType>& tokens, Data& gameData);
    void seg(const std::vector<TokenType>& tokens, Data& gameData);
    void smg(const std::vector<TokenType>& tokens, Data& gameData);
    void suc(const std::vector<TokenType>& tokens, Data& gameData);
    void sbp(const std::vector<TokenType>& tokens, Data& gameData);


    std::map<std::string, Handler> handlers = {
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

    class ParserException : public std::exception
    {
    public:
        ParserException(const std::string& message) : _message(message) {};
        const char* what() const noexcept override { return _message.c_str(); };
    private:
        std::string _message;
    };

    void parse(std::vector<std::variant<std::string, int>> values, Data& gameData)
    {
        if (values.empty() || !std::holds_alternative<std::string>(values.at(0))) {
            throw ParserException("Invalid command format");
            return;
        }

        const std::string& command = std::get<std::string>(values.at(0));
        auto it = handlers.find(command);

        if (it != handlers.end()) {
            it->second(values, gameData);
        } else {
            std::cerr << "Command not found: " << command << std::endl;
        }
    };

    void execute();
};

#endif // PARSER_HPP
