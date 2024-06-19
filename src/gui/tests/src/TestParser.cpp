#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/redirect.h>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "../../src/parser/Parser.hpp"
#include "../../src/parser/Incantation.hpp"
#include "../../src/utils/GuiException.hpp"

Test(Parser, mszNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "msz", 10, 10 };

    parser.parse(args, data, server);
    parser.execute();
    cr_assert_eq(data.getMap().getMap().size(), 10);
}

Test(Parser, mszWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "msz", "a", "arg" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, mszWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "msz" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, bctNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> prep = { "msz", 10, 10 };
    parser.parse(prep, data, server);

    std::vector<std::variant<std::string, int>> args = { "bct", 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    parser.parse(args, data, server);
    parser.execute();
    cr_assert_eq(data.getMap().getTileAt(1, 1).getResAt(0), 1);
}

Test(Parser, bctWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "bct", "a", "arg" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, bctWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "bct" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, tnaNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "tna", "team1" };

    parser.parse(args, data, server);
    parser.execute();
    cr_assert_eq(data.getTeams().size(), 1);
}

Test(Parser, tnaWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "tna", 1, 2 };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, tnaWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "tna" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, pnwNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pnw", 1, 1, 1, 1, 1, "team1" };

    parser.parse(args, data, server);
    parser.execute();
    cr_assert_eq(data.getPlayers().size(), 1);
}

Test(Parser, pnwWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pnw", "a", "arg" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, pnwWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pnw" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, ppoNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pnw", 1, 1, 1, 1, 1, "team1" };
    parser.parse(args, data, server);

    std::vector<std::variant<std::string, int>> args2 = { "ppo", 1, 2, 2, 1 };

    parser.parse(args2, data, server);
    parser.execute();
    std::shared_ptr<Player> p = data.getPlayerById(1);
    p->getNextEvent();
    std::vector<int> position = p->getPosition();
    cr_assert_eq(position[0], 2, "Expected 2, got %d", position[0]);
    cr_assert_eq(position[1], 2, "Expected 2, got %d", position[1]);

    cr_assert_eq(p->getNextEvent().action, NONE);
}

Test(Parser, ppoWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "ppo", "a", "arg" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, ppoWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "ppo" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, plvNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pnw", 1, 1, 1, 1, 1, "team1" };
    parser.parse(args, data, server);

    std::vector<std::variant<std::string, int>> args2 = { "plv", 1, 3 };

    parser.parse(args2, data, server);
    parser.execute();
    // cr_assert_eq(data.getPlayerById(1).getLvl(), 3);
}

Test(Parser, plvWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "plv", "a", "arg" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, plvWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "plv" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, pinNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> prep = { "msz", 10, 10 };
    parser.parse(prep, data, server);

    std::vector<std::variant<std::string, int>> args = { "pnw", 1, 1, 1, 1, 1, "team1" };
    parser.parse(args, data, server);

    std::vector<std::variant<std::string, int>> args2 = { "pin", 1, 1, 1, 0, 1, 2, 3, 4, 5, 6};
    parser.parse(args2, data, server);

    parser.execute();
    int q0 = data.getPlayerById(1)->getInventory().at(0);
    int q1 = data.getPlayerById(1)->getInventory().at(1);
    int q2 = data.getPlayerById(1)->getInventory().at(2);
    int q3 = data.getPlayerById(1)->getInventory().at(3);
    int q4 = data.getPlayerById(1)->getInventory().at(4);
    int q5 = data.getPlayerById(1)->getInventory().at(5);
    int q6 = data.getPlayerById(1)->getInventory().at(6);

    
    cr_assert_eq(q0, 0, "Expected 0, got %d", q0);
    cr_assert_eq(q1, 1, "Expected 1, got %d", q1);
    cr_assert_eq(q2, 2, "Expected 2, got %d", q2);
    cr_assert_eq(q3, 3, "Expected 3, got %d", q3);
    cr_assert_eq(q4, 4, "Expected 4, got %d", q4);
    cr_assert_eq(q5, 5, "Expected 5, got %d", q5);
    cr_assert_eq(q6, 6, "Expected 6, got %d", q6);
}

Test(Parser, pinWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pin", "a", "arg" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, pinWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pin" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, pexNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pnw", 1, 1, 1, 1, 1, "team1" };
    parser.parse(args, data, server);

    std::vector<std::variant<std::string, int>> args2 = { "pex", 1 };

    parser.parse(args2, data, server);
    parser.execute();
    cr_assert_eq(data.getPlayerById(1)->getNextEvent().action, PUSHED);
}

Test(Parser, pexWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pex", "a" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, pexWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pex" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, pbcNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pnw", 1, 1, 1, 1, 1, "team1" };
    parser.parse(args, data, server);

    std::vector<std::variant<std::string, int>> args2 = { "pbc", 1, "Hello" };

    parser.parse(args2, data, server);
    parser.execute();
    cr_assert_eq(data.getNextBroadcast().value().getMessage(), "Hello");
}

Test(Parser, pbcWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pbc", "a", "arg" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, pbcWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pbc" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, picNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pnw", 1, 1, 1, 1, 1, "team1" };
    parser.parse(args, data, server);

    std::vector<std::variant<std::string, int>> args2 = { "pic", 1, 1, 4, 1 };

    parser.parse(args2, data, server);
    parser.execute();
    cr_assert_eq(data.getIncantationByPos(std::vector<int>({1, 1}))->getLvl(), 4);
}

Test(Parser, pieNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pnw", 1, 1, 1, 1, 1, "team1" };
    parser.parse(args, data, server);

    std::vector<std::variant<std::string, int>> args2 = { "pic", 1, 1, 4, 1 };
    parser.parse(args2, data, server);

    std::vector<std::variant<std::string, int>> args3 = { "pie", 1, 1, SUCCESS };

    parser.parse(args3, data, server);
    parser.execute();
    std::map <std::vector<int>, std::shared_ptr<Incantation>> incantations = data.getIncantations();
    std::shared_ptr<Incantation> incantation = incantations.at(std::vector<int>({1, 1}));
    cr_assert_eq(incantation->getStatus(), SUCCESS, "Expected %d, got %d", SUCCESS, incantation->getStatus());
}

Test(Parser, pieWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pie", "a", "arg" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, pieWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pie" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, pfkNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pnw", 1, 1, 1, 1, 1, "team1" };
    parser.parse(args, data, server);

    std::vector<std::variant<std::string, int>> args2 = { "pfk", 1 };

    parser.parse(args2, data, server);
    parser.execute();
    cr_assert_eq(data.getPlayerById(1)->getNextEvent().action, EGGING);
}

Test(Parser, pfkWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pfk", "a" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, pfkWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pfk" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, pdrNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pnw", 1, 1, 1, 1, 1, "team1" };
    parser.parse(args, data, server);

    std::vector<std::variant<std::string, int>> args2 = { "pdr", 1, 1 };

    parser.parse(args2, data, server);
    cr_assert_throw(parser.execute(), guiException);
}

Test(Parser, pdrWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pdr", "a" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, pdrWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pdr" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, cmdNotFound)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "ezbavhrj" };

    parser.parse(args, data, server);

    cr_assert(1);
}

Test(Parser, pgtNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pnw", 1, 1, 1, 1, 1, "team1" };
    parser.parse(args, data, server);

    std::vector<std::variant<std::string, int>> args2 = { "pgt", 1, 1 };

    parser.parse(args2, data, server);
    cr_assert_throw(parser.execute(), guiException);
}

Test(Parser, pgtWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pgt", "a" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, pgtWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pgt" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, pdiNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pnw", 1, 1, 1, 1, 1, "team1" };
    parser.parse(args, data, server);

    std::vector<std::variant<std::string, int>> args2 = { "pdi", 1 };

    parser.parse(args2, data, server);
    parser.execute();
    cr_assert_eq(data.getPlayerById(1)->getAlive(), false);
}

Test(Parser, pdiWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pdi", "a" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, pdiWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "pdi" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, enwNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "enw", 1, 1, 1, 1 };

    parser.parse(args, data, server);
    parser.execute();
    cr_assert_eq(data.getEggs().size(), 1);
}

Test(Parser, enwWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "enw", "a", "arg", "arg", "arg" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, enwWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "enw" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, eboNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "enw", 1, 1, 1, 1 };
    parser.parse(args, data, server);

    std::vector<std::variant<std::string, int>> args2 = { "ebo", 1 };

    parser.parse(args2, data, server);
    parser.execute();
    cr_assert_eq(data.getEggs().at(1).getState(), HATCHED);
}

Test(Parser, eboWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "ebo", "a" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, eboWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "ebo" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, ediNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "enw", 1, 1, 1, 1 };
    parser.parse(args, data, server);

    std::vector<std::variant<std::string, int>> args2 = { "edi", 1 };

    parser.parse(args2, data, server);
    parser.execute();
    cr_assert_eq(data.getEggs().at(1).getState(), DEAD);
}

Test(Parser, ediWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "edi", "a" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, ediWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "edi" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, sstNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "sst", 1 };

    parser.parse(args, data, server);
    parser.execute();
    cr_assert_eq(data.getTickRate(), 1);
}

Test(Parser, sstWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "sst", "a" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, sstWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "sst" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, sgtNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "sgt", 1 };

    parser.parse(args, data, server);
    parser.execute();
    cr_assert_eq(data.getTickRate(), 1);
}

Test(Parser, sgtWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "sgt", "a" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, sgtWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "sgt" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, segNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "seg", "team1" };

    parser.parse(args, data, server);
    parser.execute();
    cr_assert_eq(data.getWinner(), "team1");
}

Test(Parser, segWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "seg", 1 };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, segWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "seg" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, smgNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "smg", "Hello" };

    parser.parse(args, data, server);
    parser.execute();
    cr_assert(1);
}

Test(Parser, smgWrongArgs)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "smg", 1 };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, smgWrongSize)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "smg" };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}

Test(Parser, sucNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "suc" };

    parser.parse(args, data, server);
    parser.execute();
    cr_assert(1);
}

Test(Parser, sbpNormal)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { "sbp" };

    parser.parse(args, data, server);
    parser.execute();
    cr_assert(1);
}

Test(Parser, Throw)
{
    Parser parser;
    Data data;
    ServerConnect server;

    std::vector<std::variant<std::string, int>> args = { 12 };

    cr_assert_throw(parser.parse(args, data, server), Parser::ParserException);
}
