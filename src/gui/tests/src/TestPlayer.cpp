#include <criterion/criterion.h>
#include <vector>

#include "../../src/parser/Player.hpp"

Test(Player, Alive)
{
    Player player;

    player.setAlive(true);
    cr_assert(player.getAlive() == true, "set alive true failed");
    player.setAlive(false);
    cr_assert(player.getAlive() == false, "set alive false failed");
}

Test(Player, Inventory_size)
{
    Player player;

    player.setInventory({1, 2, 3, 4, 5, 6, 7});
    cr_assert(player.getInventory().size() == 7, "Inventory size is not 7");
}

Test(Player, Inventorycontent)
{
    Player player;

    player.setInventory({1, 2, 3, 4, 5, 6, 7});
    cr_assert(player.getInventory().at(3) == 4, "Inventory value 4 is not the right one");
}

Test(Player, Position_size)
{
    Player player;

    player.setPosition({1, 2});
    cr_assert(player.getPosition().size() == 2, "Position size is not 2");
}

Test(Player, Position_coordinates)
{
    Player player;
    std::vector<int> newPos = {1, 2};

    player.setPosition(newPos);
    player.getNextEvent();
    std::vector<int> pPos = player.getPosition();
    cr_assert_eq(pPos[0], newPos[0], "Expected %d, got %d", newPos[0], pPos[0]);
    cr_assert_eq(pPos[1], newPos[1], "Expected %d, got %d", newPos[1], pPos[1]);
}

Test(Player, Orientation)
{
    Player player;

    player.setOrientation(1);
    cr_assert(player.getOrientation() == 1, "Orientation is not 1");
}

Test(Player, Lvl)
{
    Player player;

    player.setLvl(1);
    cr_assert(player.getLvl() == 1, "Level is not 1");
}

Test(Player, Team)
{
    Player player;

    player.setTeam("Team A");
    cr_assert(player.getTeam() == "Team A", "Team is not Team A");
}

Test(Player, PlayerNb)
{
    Player player;

    player.setPlayerNb(1);
    cr_assert(player.getPlayerNb() == 1, "Player number is not 1");
}

Test(Player, Incanting)
{
    Player player;

    player.setIncanting();
    cr_assert(player.getNextEvent().action == INCANTATING, "Next event is not Incantation");
}

Test(Player, Egging)
{
    Player player;

    player.setEgging();
    cr_assert(player.getNextEvent().action == EGGING, "Next event is not Egg laying");
}

Test(Player, Pushing)
{
    Player player;

    player.setPushed();
    cr_assert(player.getNextEvent().action == PUSHED, "Next event is not Pushing");
}

Test(Player, Pickup)
{
    Player player;

    player.setPickup(1);
    cr_assert(player.getNextEvent().action == PICKUP, "Next event is not Picking up");
}

Test(Player, Drop)
{
    Player player;

    player.setDrop(1);
    cr_assert(player.getNextEvent().action == DROP, "Next event is not Dropping");
}

Test(Player, getEventActionEmpty)
{
    Player player;

    Actions expected = NONE;
    Actions result = player.getNextEvent().action;

    cr_assert_eq(result, expected, "Expected %d, got %d", expected, result);
}

Test(Player, getEventActionNotEmpty)
{
    Player player;

    player.setEgging();

    Actions expected = NONE;
    Actions result = player.getNextEvent().action;

    cr_assert_neq(result, expected, "Expected not %d, got %d", expected, result);
}

Test(Player, constructor)
{
    Player player(1, {1, 2}, 1, 1, "Team A");

    cr_assert_eq(player.getPlayerNb(), 1, "Expected 1, got %d", player.getPlayerNb());
    cr_assert_eq(player.getPosition()[0], 1, "Expected 1, got %d", player.getPosition()[0]);
    cr_assert_eq(player.getPosition()[1], 2, "Expected 2, got %d", player.getPosition()[1]);
    cr_assert_eq(player.getOrientation(), 1, "Expected 1, got %d", player.getOrientation());
    cr_assert_eq(player.getLvl(), 1, "Expected 1, got %d", player.getLvl());
    cr_assert_eq(player.getTeam(), "Team A", "Expected Team A, got %s", player.getTeam().c_str());

    std::vector<int> inventory = player.getInventory();
    cr_assert_eq(inventory[0], 0, "Expected 0, got %d", inventory[0]);
    cr_assert_eq(inventory[1], 0, "Expected 0, got %d", inventory[1]);
    cr_assert_eq(inventory[2], 0, "Expected 0, got %d", inventory[2]);
    cr_assert_eq(inventory[3], 0, "Expected 0, got %d", inventory[3]);
    cr_assert_eq(inventory[4], 0, "Expected 0, got %d", inventory[4]);
    cr_assert_eq(inventory[5], 0, "Expected 0, got %d", inventory[5]);
    cr_assert_eq(inventory[6], 0, "Expected 0, got %d", inventory[6]);
}

Test(Player, constructorDefault)
{
    Player player;

    cr_assert_eq(player.getPosition()[0], 0, "Expected 0, got %d", player.getPosition()[0]);
    cr_assert_eq(player.getPosition()[1], 0, "Expected 0, got %d", player.getPosition()[1]);
    cr_assert_eq(player.getOrientation(), UP, "Expected UP, got %d", player.getOrientation());
    cr_assert_eq(player.getLvl(), 1, "Expected 1, got %d", player.getLvl());
    cr_assert_eq(player.getTeam(), "default", "Expected default, got %s", player.getTeam().c_str());
    cr_assert_eq(player.getAlive(), true, "Expected true, got %d", player.getAlive());

    std::vector<int> inventory = player.getInventory();
    cr_assert_eq(inventory[0], 0, "Expected 0, got %d", inventory[0]);
    cr_assert_eq(inventory[1], 0, "Expected 0, got %d", inventory[1]);
    cr_assert_eq(inventory[2], 0, "Expected 0, got %d", inventory[2]);
    cr_assert_eq(inventory[3], 0, "Expected 0, got %d", inventory[3]);
    cr_assert_eq(inventory[4], 0, "Expected 0, got %d", inventory[4]);
    cr_assert_eq(inventory[5], 0, "Expected 0, got %d", inventory[5]);
    cr_assert_eq(inventory[6], 0, "Expected 0, got %d", inventory[6]);

    Event event = player.getNextEvent();
    cr_assert_eq(event.action, NONE, "Expected NONE, got %d", event.action);
}

Test(Event, construction)
{
    Event test(DROP, std::vector<int>({1}));
    Event test2(PICKUP);

    cr_assert_eq(test.action, DROP, "Expected DROP, got %d", test.action);
    cr_assert_eq(test.params[0], 1, "Expected , got %d", test.params[0]);
    cr_assert_eq(test2.action, PICKUP, "Expected PICKUP, got %d", test2.action);
}
