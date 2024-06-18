#include <criterion/criterion.h>
#include <vector>

#include "../../src/parser/Broadcast.hpp"

Test(Broadcast, constructor)
{
    Broadcast broadcast(1, "message", {1, 2});

    std::string message = broadcast.getMessage();
    std::string expectedMessage = "message";

    cr_assert_eq(message, expectedMessage, "message is %s, expected %s", message.c_str(), expectedMessage.c_str());
}

Test(Broadcast, getPosition)
{
    Broadcast broadcast(1, "message", {1, 2});

    std::vector<int> pos = broadcast.getPosition();
    std::vector<int> expectedPos = {1, 2};

    cr_assert_eq(pos, expectedPos, "pos is {%d, %d}, expected {%d, %d}", pos[0], pos[1], expectedPos[0], expectedPos[1]);
}

Test(Broadcast, getPlayerNb)
{
    Broadcast broadcast(1, "message", {1, 2});

    int playerNb = broadcast.getPlayerNb();
    int expectedPlayerNb = 1;

    cr_assert_eq(playerNb, expectedPlayerNb, "playerNb is %d, expected %d", playerNb, expectedPlayerNb);
}

Test(Broadcast, getMessage)
{
    Broadcast broadcast(1, "message", {1, 2});

    std::string message = broadcast.getMessage();
    std::string expectedMessage = "message";

    cr_assert_eq(message, expectedMessage, "message is %s, expected %s", message.c_str(), expectedMessage.c_str());
}

Test(Broadcast, destructor)
{
    Broadcast *broadcast = new Broadcast(1, "message", {1, 2});

    delete broadcast;
    cr_assert(1, "Destructor called");
}
