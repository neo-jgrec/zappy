#include <criterion/criterion.h>
#include <vector>

#include "../../src/Player.hpp"

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

Test(Player, Inventory_content)
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

    player.setPushing();
    cr_assert(player.getNextEvent().action == PUSHING, "Next event is not Pushing");
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
