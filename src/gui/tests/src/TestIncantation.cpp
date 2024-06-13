#include <criterion/criterion.h>
#include <vector>

#include "../../src/Incantation.hpp"

Test(Incantation, setStatus)
{
    Incantation incantation({1, 2}, 1, {1, 2, 3});

    incantation.setStatus(SUCCESS);
    IncantationOutcome status = incantation.getStatus();
    IncantationOutcome expectedStatus = SUCCESS;

    cr_assert_eq(status, expectedStatus, "status is %d, expected %d", status, expectedStatus);
}

Test(Incantation, addPlayer)
{
    Incantation incantation({1, 2}, 1, {1, 2, 3});

    incantation.addPlayer(4);
    std::vector<int> playersIds = incantation.getPlayersId();
    std::vector<int> expectedPlayersIds = {1, 2, 3, 4};

    cr_assert_eq(playersIds, expectedPlayersIds, "playersIds is {%d, %d, %d, %d}, expected {%d, %d, %d, %d}", playersIds[0], playersIds[1], playersIds[2], playersIds[3], expectedPlayersIds[0], expectedPlayersIds[1], expectedPlayersIds[2], expectedPlayersIds[3]);
}

Test(Incantation, getPosition)
{
    Incantation incantation({1, 2}, 1, {1, 2, 3});

    std::vector<int> pos = incantation.getPosition();
    std::vector<int> expectedPos = {1, 2};

    cr_assert_eq(pos, expectedPos, "pos is {%d, %d}, expected {%d, %d}", pos[0], pos[1], expectedPos[0], expectedPos[1]);
}

Test(Incantation, getLvl)
{
    Incantation incantation({1, 2}, 1, {1, 2, 3});

    int lvl = incantation.getLvl();
    int expectedLvl = 1;

    cr_assert_eq(lvl, expectedLvl, "lvl is %d, expected %d", lvl, expectedLvl);
}

Test(Incantation, getStatus)
{
    Incantation incantation({1, 2}, 1, {1, 2, 3});

    IncantationOutcome status = incantation.getStatus();
    IncantationOutcome expectedStatus = IN_PROGRESS;

    cr_assert_eq(status, expectedStatus, "status is %d, expected %d", status, expectedStatus);
}

Test(Incantation, getStatusFailure)
{
    Incantation incantation({1, 2}, 1, {1, 2, 3});

    incantation.setStatus(FAILURE);
    IncantationOutcome status = incantation.getStatus();
    IncantationOutcome expectedStatus = FAILURE;

    cr_assert_eq(status, expectedStatus, "status is %d, expected %d", status, expectedStatus);
}

Test(Incantation, setStatusMultiple) {
    Incantation incantation({1, 2}, 1, {1, 2, 3});

    incantation.setStatus(SUCCESS);
    cr_assert_eq(incantation.getStatus(), SUCCESS, "Status should be SUCCESS");

    incantation.setStatus(FAILURE);
    cr_assert_eq(incantation.getStatus(), FAILURE, "Status should be FAILURE");

    incantation.setStatus(IN_PROGRESS);
    cr_assert_eq(incantation.getStatus(), IN_PROGRESS, "Status should be IN_PROGRESS");
}
