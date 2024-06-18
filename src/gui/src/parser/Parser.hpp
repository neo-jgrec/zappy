#ifndef PARSER_HPP
    #define PARSER_HPP

    #include <functional>
    #include <variant>
    #include <vector>
    #include <string>
    #include <queue>

    #include "Data.hpp"
    #include "ServerConnect.hpp"

class Parser
{
private:
    enum class Type
    {
        INT,
        STRING
    };

    using TokenType = std::variant<std::string, int>;
    using Handler = std::function<void(const std::vector<TokenType>&, Data&, ServerConnect&)>;

    std::queue<std::function<void()>> _queue;

    void msz(const std::vector<TokenType>& values, Data& gameData, ServerConnect &server);
    void bct(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void tna(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void pnw(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void ppo(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void plv(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void pin(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void pex(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void pbc(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void pic(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void pie(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void pfk(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void pdr(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void pgt(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void pdi(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void enw(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void ebo(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void edi(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void sst(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void sgt(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void seg(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void smg(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void suc(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);
    void sbp(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);


    std::map<std::string, Handler> handlers = {
        {"msz", std::bind(&Parser::msz, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"bct", std::bind(&Parser::bct, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"tna", std::bind(&Parser::tna, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"pnw", std::bind(&Parser::pnw, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"ppo", std::bind(&Parser::ppo, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"plv", std::bind(&Parser::plv, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"pin", std::bind(&Parser::pin, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"pex", std::bind(&Parser::pex, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"pbc", std::bind(&Parser::pbc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"pic", std::bind(&Parser::pic, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"pie", std::bind(&Parser::pie, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"pfk", std::bind(&Parser::pfk, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"pdr", std::bind(&Parser::pdr, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"pgt", std::bind(&Parser::pgt, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"pdi", std::bind(&Parser::pdi, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"enw", std::bind(&Parser::enw, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"ebo", std::bind(&Parser::ebo, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"edi", std::bind(&Parser::edi, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"sst", std::bind(&Parser::sst, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"sgt", std::bind(&Parser::sgt, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"seg", std::bind(&Parser::seg, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"smg", std::bind(&Parser::smg, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"suc", std::bind(&Parser::suc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)},
        {"sbp", std::bind(&Parser::sbp, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)}
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

    void parse(std::vector<TokenType> values, Data& gameData, ServerConnect &server);

    void execute();

    void updateData(Data& gameData, ServerConnect &server);

    void checkType(const std::vector<TokenType>& tokens, const std::vector<Type>& expectedTypes, const std::string& name);
};

#endif // PARSER_HPP
