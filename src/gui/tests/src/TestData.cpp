#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <optional>

#include "../../src/parser/Data.hpp"
#include "../../src/utils/GuiException.hpp"


Test(Data, getTickRate)
{
    Data data;

    cr_assert_eq(data.getTickRate(), 0, "got %d, expected 0", data.getTickRate());
}

Test(Data, setTickRate)
{
    Data data;

    data.setTickRate(10);
    cr_assert_eq(data.getTickRate(), 10, "got %d, expected 10", data.getTickRate());
}

Test(Data, setRunning)
{
    Data data;

    data.setRunning(true);
    cr_assert_eq(data.getRunning(), true, "got %d, expected 1", data.getRunning());
}

Test(Data, getRunning)
{
    Data data;

    cr_assert_eq(data.getRunning(), false, "got %d, expected 0", data.getRunning());
}

Test(Data, setWinner)
{
    Data data;

    data.setWinner("test");
    cr_assert_str_eq(data.getWinner().value().c_str(), "test", "got %s, expected \"test\"", data.getWinner().value().c_str());
}

Test(Data, addEgg)
{
    Data data;

    data.addEgg({1, 1}, 1, 1, HATCHED);
    cr_assert_eq(data.getEggs().size(), 1, "got %li, expected 1", data.getEggs().size());
}

Test(Data, getEggById)
{
    Data data;

    data.addEgg({1, 1}, 1, 1, HATCHED);
    Egg egg = data.getEggById(1);
    cr_assert_eq(egg.getId(), 1, "got %d, expected 1", egg.getId());
}

Test(Data, getEggByIdWrong)
{
    Data data;

    data.addEgg({1, 1}, 1, 1, HATCHED);
    cr_assert_throw(data.getEggById(2), guiException, "getEggById: expected guiException");
}


Test(Data, addTeam)
{
    Data data;

    data.addTeam("test");
    cr_assert_eq(data.getTeams().size(), 1, "got %li, expected 1", data.getTeams().size());
}

Test(Data, getTeamByName)
{
    Data data;

    data.addTeam("test");
    std::string teamName = data.getTeamByName("test");
    cr_assert_str_eq(teamName.c_str(), "test", "got %s, expected \"test\"", teamName.c_str());
}

Test(Data, getTeamByNameWrong)
{
    Data data;

    data.addTeam("test");
    cr_assert_throw(data.getTeamByName("wrong"), guiException, "getTeamByName: expected guiException");
}

Test(Data, addPlayer)
{
    Data data;

    data.addPlayer({1, 1, 1, UP, 1}, "test");
    cr_assert_eq(data.getPlayers().size(), 1, "got %li, expected 1", data.getPlayers().size());
}

Test(Data, getPlayerById)
{
    Data data;

    data.addPlayer({1, 1, 1, UP, 1}, "test");
    std::shared_ptr<Player> player = data.getPlayerById(1);
    cr_assert_eq(player->getPlayerNb(), 1, "got %d, expected 1", player->getPlayerNb());
}

Test(Data, getPlayerByIdWrong)
{
    Data data;

    data.addPlayer({1, 1, 1, UP, 1}, "test");
    cr_assert_throw(data.getPlayerById(2), guiException, "getPlayerById: expected guiException");
}

Test(Data, addIncantation)
{
    Data data;

    data.addIncantation({1, 1}, 1, {1, 2, 3});
    cr_assert_eq(data.getIncantations().size(), 1, "got %li, expected 1", data.getIncantations().size());
}

Test(Data, getIncantationByPos)
{
    Data data;

    data.addIncantation({1, 2}, 1, {1, 2, 3});
    Incantation incantation = data.getIncantationByPos({1, 2});
    cr_assert_eq(incantation.getPosition()[0], 1, "got %d, expected 1", incantation.getPosition()[0]);
    cr_assert_eq(incantation.getPosition()[1], 2, "got %d, expected 2", incantation.getPosition()[1]);
}

Test(Data, getIncantationByPosWrong)
{
    Data data;

    data.addIncantation({1, 2}, 1, {1, 2, 3});
    cr_assert_throw(data.getIncantationByPos({1, 1}), guiException, "getIncantationsByPos: expected guiException");
}

Test(Data, addBroadcast)
{
    Data data;

    data.addBroadcast(1, {4, 4}, "test");
    cr_assert_eq(data.getBroadcasts().size(), 1, "got %li, expected 1", data.getBroadcasts().size());
}

Test(Data, getNextBroadcast)
{
    Data data;

    data.addBroadcast(1, {4, 4}, "test");
    std::optional<Broadcast> maybeBroadcast = data.getNextBroadcast();
    if (!maybeBroadcast.has_value())
        return;
    Broadcast broadcast = maybeBroadcast.value();
    std::string msg = broadcast.getMessage();
    cr_assert_str_eq(msg.c_str(), "test", "got %s, expected \"test\"", msg.c_str());
    cr_assert_eq(broadcast.getPlayerNb(), 1, "got %d, expected 1", broadcast.getPlayerNb());
    cr_assert_eq(broadcast.getPosition()[0], 4, "got %d, expected 4", broadcast.getPosition()[0]);

    cr_assert_eq(data.getNextBroadcast(), std::nullopt);
}

Test(Data, doesTeamExist)
{
    Data data;

    data.addTeam("test");
    cr_assert_eq(data.doesTeamExist("test"), true, "got %d, expected 1", data.doesTeamExist("test"));
}

Test(Data, doesTeamExistWrong)
{
    Data data;

    data.addTeam("test");
    cr_assert_eq(data.doesTeamExist("wrong"), false, "got %d, expected 0", data.doesTeamExist("wrong"));
}

Test(Data, playerExists)
{
    Data data;

    data.addPlayer({1, 1, 1, UP, 1}, "test");
    cr_assert_eq(data.playerExists(1), true, "got %d, expected 1", data.playerExists(1));
}

Test(Data, playerExistsWrong)
{
    Data data;

    data.addPlayer({1, 1, 1, UP, 1}, "test");
    cr_assert_eq(data.playerExists(2), false, "got %d, expected 0", data.playerExists(2));
}

Test(Data, getMap)
{
    Data data;

    cr_assert_eq(data.getMap().getSize()[0], 0, "got %d, expected 0", data.getMap().getSize()[0]);
    cr_assert_eq(data.getMap().getSize()[1], 0, "got %d, expected 0", data.getMap().getSize()[1]);

    data.getMap().fillMap(5, 5);
    cr_assert_eq(data.getMap().getSize()[0], 5, "got %d, expected 5", data.getMap().getSize()[0]);
    cr_assert_eq(data.getMap().getSize()[1], 5, "got %d, expected 5", data.getMap().getSize()[1]);

    data.getMap().updateTile(1, 1, {1, 2, 3, 4, 5, 6, 7});
    cr_assert_eq(data.getMap().getTileAt(1, 1).getResAt(0), 1, "got %d, expected 1", data.getMap().getTileAt(1, 1).getResAt(0));
    cr_assert_eq(data.getMap().getTileAt(1, 1).getResAt(1), 2, "got %d, expected 2", data.getMap().getTileAt(1, 1).getResAt(1));
    cr_assert_eq(data.getMap().getTileAt(1, 1).getResAt(2), 3, "got %d, expected 3", data.getMap().getTileAt(1, 1).getResAt(2));
    cr_assert_eq(data.getMap().getTileAt(1, 1).getResAt(3), 4, "got %d, expected 4", data.getMap().getTileAt(1, 1).getResAt(3));
    cr_assert_eq(data.getMap().getTileAt(1, 1).getResAt(4), 5, "got %d, expected 5", data.getMap().getTileAt(1, 1).getResAt(4));
    cr_assert_eq(data.getMap().getTileAt(1, 1).getResAt(5), 6, "got %d, expected 6", data.getMap().getTileAt(1, 1).getResAt(5));
    cr_assert_eq(data.getMap().getTileAt(1, 1).getResAt(6), 7, "got %d, expected 7", data.getMap().getTileAt(1, 1).getResAt(6));
}
