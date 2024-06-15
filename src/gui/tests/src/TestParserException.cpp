#include <criterion/criterion.h>
#include <criterion/internal/assert.h>

#include "../../src/parser/Parser.hpp"

Test(ParserException, constructor)
{
    Parser::ParserException exception("test");
    Parser::ParserException exception2("");

    const char *what = exception.what();
    const char *expectedWhat = "test";

    cr_assert_str_eq(what, expectedWhat, "got %s, expected %s", what, expectedWhat);
    cr_assert_str_eq(exception2.what(), "", "got %s, expected \"\"", exception2.what());
}

Test(ParserException, what)
{
    Parser parser;
    Data gameData;

    std::vector<std::variant<std::string, int>> values = {"msz"};

    try {
        parser.parse(values, gameData);
    } catch (const Parser::ParserException &e) {
        cr_assert_str_eq(e.what(), "Invalid number of arguments for command msz", "got %s, expected \"Invalid number of arguments for command msz\"", e.what());
    }
}


