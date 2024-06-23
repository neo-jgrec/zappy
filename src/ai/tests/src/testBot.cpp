/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Bot.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../../src/utils/StringUtils.hpp"
#include "../../src/utils/PrintColor.hpp"
#include "../../src/bots/Forker.hpp"
#include "../../src/bots/ABot.hpp"
#include "../../src/utils/Initializer.hpp"
#include "../../src/utils/DisplayHelp.hpp"
#include "../../src/bots/SimpleBot.hpp"
#include "../../src/utils/StringUtils.hpp"
#include "../../src/environment/Environment.hpp"
#include "../../src/environment/Tile.hpp"
#include "../../src/message/Message.hpp"

Test(strings_utils, replaceNumbersInString)
{
    std::string str = "Hello 32";
    std::string res = replaceNumbersInString(str, 10);
    cr_assert_str_eq(res.c_str(), "Hello 42");
}

Test(strings_utils, getElementAfter)
{
    std::string str = "Hello:World";
    std::string res = getElementAfter(str, ':');
    cr_assert_str_eq(res.c_str(), "World");
}

Test(strings_utils, getElementBefore)
{
    std::string str = "Hello:World";
    std::string res = getElementBefore(str, ':');
    cr_assert_str_eq(res.c_str(), "Hello");
}

Test(strings_utils, generateNewNumber)
{
    std::string str = "32";
    std::string res = generateNewNumber(str, 10);
    cr_assert_str_eq(res.c_str(), "42");
}

Test(message, vignereEncrypt)
{
    Message message;

    message.content = "group";
    message.vigenereEncrypt();
    cr_assert_str_eq(message.content.c_str(), "qzaor");
}

Test(message, vignereDecrypt)
{
    Message message;

    message.content = "qzaor";
    message.vigenereDecrypt();
    cr_assert_str_eq(message.content.c_str(), "group");
}

Test(message, generateMessage)
{
    Message message;

    message.content = "group";
    message.generateMessage();
    cr_assert_str_eq(message.content.c_str(), "group:bFNneQbXQkyJHGEQd");
}

Test(message, convertDigitsToLetters)
{
    Message message;

    std::string res = message.convertDigitsToLetters("123");
    cr_assert_str_eq(res.c_str(), "DCB");
}

Test(StringUtils, cleanCarriageReturnRemovesNewline)
{
    std::string input = "test\n";
    std::string expected = "test";
    cr_assert_eq(cleanCarriageReturn(input), expected, "Expected the newline to be removed.");
}

Test(StringUtils, cleanCarriageReturnNoNewlineUnchanged)
{
    std::string input = "test";
    std::string expected = "test";
    cr_assert_eq(cleanCarriageReturn(input), expected, "Expected the string to remain unchanged.");
}

Test(StringUtils, cleanCarriageReturnEmptyString)
{
    std::string input = "";
    std::string expected = "";
    cr_assert_eq(cleanCarriageReturn(input), expected, "Expected the empty string to remain unchanged.");
}

Test(StringUtils, splitByCharMultipleDelimiters)
{
    std::string input = "a,b,c";
    char delimiter = ',';
    std::vector<std::string> expected = {"a", "b", "c"};
    std::vector<std::string> result = splitByChar(input, delimiter);
    cr_assert_eq(result.size(), expected.size(), "Expected vector sizes to match.");
    for (size_t i = 0; i < expected.size(); ++i) {
        cr_assert_str_eq(result[i].c_str(), expected[i].c_str(), "Expected element %zu to match.", i);
    }
}

Test(StringUtils, splitByCharNoDelimiter)
{
    std::string input = "abc";
    char delimiter = ',';
    std::vector<std::string> expected = {"abc"};
    std::vector<std::string> result = splitByChar(input, delimiter);
    cr_assert_eq(result.size(), expected.size(), "Expected vector sizes to match.");
    cr_assert_str_eq(result[0].c_str(), expected[0].c_str(), "Expected the single element to match.");
}

Test(StringUtils, splitByCharEmptyString)
{
    std::string input = "";
    char delimiter = ',';
    std::vector<std::string> expected = {};
    std::vector<std::string> result = splitByChar(input, delimiter);
    cr_assert_eq(result.size(), expected.size(), "Expected vector sizes to match.");
}

Test(initializer_tests, correct_arguments)
{
    Initializer init;
    int argc = 7;
    const char *argv[] = {"program", "-p", "8080", "-n", "TeamName", "-h", "localhost"};
    init.parseArguments(argc, const_cast<char**>(argv));
    cr_assert_eq(init.port, 8080, "Le port devrait être défini à 8080");
    cr_assert_str_eq(init.teamName.c_str(), "TeamName", "Le nom de l'équipe devrait être 'TeamName'");
    cr_assert_str_eq(init.host.c_str(), "localhost", "L'hôte devrait être 'localhost'");
}

struct CoutRedirect
{
    std::streambuf* old = nullptr;
    std::ostringstream ss;

    CoutRedirect() {
        old = std::cout.rdbuf(ss.rdbuf());
    }

    ~CoutRedirect() {
        std::cout.rdbuf(old);
    }

    std::string str() {
        return ss.str();
    }
};

Test(ressources_initialization, test_initialization)
{
    Ressources res;
    cr_expect_eq(res.getRessource("food"), 0, "Expected food to be initialized to 0");
    cr_expect_eq(res.getRessource("linemate"), 0, "Expected linemate to be initialized to 0");
}

Test(ressources_operations, test_add_ressource)
{
    Ressources res;
    res.addRessource("food");
    cr_expect_eq(res.getRessource("food"), 1, "Expected food count to be 1 after adding food");
}

Test(ressources_operations, test_get_ressource)
{
    Ressources res;
    res.addRessource("linemate");
    res.addRessource("linemate");
    cr_expect_eq(res.getRessource("linemate"), 2, "Expected linemate count to be 2 after adding twice");
}

Test(ressources_operations, test_invalid_ressource)
{
    Ressources res;
    res.addRessource("invalid");
    cr_expect_eq(res.getRessource("invalid"), 0, "Expected invalid resource count to remain 0");
}

Test(environment_operations, test_clear)
{
    Environment env;
    env.tiles.push_back(Tile());
    env.clear();
    cr_expect_eq(env.tiles.size(), 0, "Expected tiles to be empty after clear");
}

Test(environment_operations, test_contains)
{
    Environment env;
    Tile tileWithFood;
    tileWithFood.ressources.food = 1;
    env.tiles.push_back(tileWithFood);
    cr_expect(env.contains("food"), "Expected environment to contain food");
    cr_expect_not(env.contains("linemate"), "Expected environment not to contain linemate");
}

Test(environment_operations, test_getDistance)
{
    Environment env;
    Tile tileWithFood;
    tileWithFood.ressources.food = 1;
    tileWithFood.distance = 2;
    env.tiles.push_back(tileWithFood);
    cr_expect_eq(env.getDistance("food"), 2, "Expected distance to food to be 2");
}

Test(environment_operations, test_getTileByRessource)
{
    Environment env;
    Tile tileWithFood;
    tileWithFood.ressources.food = 1;
    tileWithFood.distance = 2;
    env.tiles.push_back(tileWithFood);
    auto tile = env.getTileByRessource("food");
    cr_expect_not_null(tile.get(), "Expected to get a tile");
    cr_expect_eq(tile->ressources.food, 1, "Expected tile to contain food");
    cr_expect_eq(tile->distance, 2, "Expected tile distance to be 2");
}

Test(tile_constructor, initialization)
{
    Ressources testRessources;
    testRessources.food = 1;
    testRessources.linemate = 2;
    testRessources.deraumere = 3;
    testRessources.sibur = 4;
    testRessources.mendiane = 5;
    testRessources.phiras = 6;
    testRessources.thystame = 7;
    Tile testTile(10, 20, 5, testRessources);
    cr_expect_eq(testTile.x, 10, "Expected x to be 10");
    cr_expect_eq(testTile.y, 20, "Expected y to be 20");
    cr_expect_eq(testTile.distance, 5, "Expected distance to be 5");
    cr_expect_eq(testTile.ressources.food, 1, "Expected food to be 1");
    cr_expect_eq(testTile.ressources.linemate, 2, "Expected linemate to be 2");
    cr_expect_eq(testTile.ressources.deraumere, 3, "Expected deraumere to be 3");
    cr_expect_eq(testTile.ressources.sibur, 4, "Expected sibur to be 4");
    cr_expect_eq(testTile.ressources.mendiane, 5, "Expected mendiane to be 5");
    cr_expect_eq(testTile.ressources.phiras, 6, "Expected phiras to be 6");
    cr_expect_eq(testTile.ressources.thystame, 7, "Expected thystame to be 7");
}

void setup(void)
{
    cr_redirect_stdout();
}

Test(print_color, basic_output, .init = setup)
{
    printColor("Hello, World!", BRIGHT_RED);
    fflush(stdout);
    cr_expect_stdout_eq_str("\x1b[31;1mHello, World!\x1b[0m");
}

Test(print_key_value_colored, info_state, .init = setup)
{
    printKeyValueColored("Key", "Value", PRINT_STATE_INFO);
    fflush(stdout);
    cr_expect_stdout_eq_str("\x1b[33mKey: \x1b[0m\x1b[37;1mValue\n\x1b[0m");
}
