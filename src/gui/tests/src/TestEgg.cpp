#include <criterion/criterion.h>
#include <vector>

#include "../../src/Egg.hpp"

Test(Egg, constructor)
{
    Egg egg({1, 2}, 1, 1, INCUBATING);

    int id = egg.getId();
    int expectedId = 1;

    cr_assert_eq(id, expectedId, "id is %d, expected %d", id, expectedId);
}

Test(Egg, getState)
{
    Egg egg({1, 2}, 1, 1, INCUBATING);

    EggStatus state = egg.getState();
    EggStatus expectedState = INCUBATING;

    cr_assert_eq(state, expectedState, "state is %d, expected %d", state, expectedState);
}

Test(Egg, setState)
{
    Egg egg({1, 2}, 1, 1, INCUBATING);

    egg.setState(READY_TO_HATCH);

    EggStatus state = egg.getState();
    EggStatus expectedState = READY_TO_HATCH;

    cr_assert_eq(state, expectedState, "state is %d, expected %d", state, expectedState);
}

Test(Egg, getPos)
{
    Egg egg({1, 2}, 1, 1, INCUBATING);

    std::vector<int> pos = egg.getPos();
    std::vector<int> expectedPos = {1, 2};

    cr_assert_eq(pos.at(0), expectedPos.at(0), "pos[0] is %d, expected %d", pos.at(0), expectedPos.at(0));
    cr_assert_eq(pos.at(1), expectedPos.at(1), "pos[1] is %d, expected %d", pos.at(1), expectedPos.at(1));
}

Test(Egg, getPlayerNb)
{
    Egg egg({1, 2}, 1, 1, INCUBATING);

    int playerNb = egg.getPlayerNb();
    int expectedPlayerNb = 1;

    cr_assert_eq(playerNb, expectedPlayerNb, "playerNb is %d, expected %d", playerNb, expectedPlayerNb);
}

Test(Egg, eggStatus)
{
    EggStatus status = INCUBATING;

    cr_assert_eq(status, 0, "status is %d, expected %d", status, 0);
    status = READY_TO_HATCH;
    cr_assert_eq(status, 1, "status is %d, expected %d", status, 1);
    status = HATCHED;
    cr_assert_eq(status, 2, "status is %d, expected %d", status, 2);
    status = DEAD;
    cr_assert_eq(status, 3, "status is %d, expected %d", status, 3);
}

Test(Egg, destructor)
{
    Egg *egg = new Egg({1, 2}, 1, 1, INCUBATING);

    delete egg;
    cr_assert(1, "Destructor called");
}
