---
sidebar_position: 5
---

# Time

Active waiting is not tolerated: there should not be any blocking when the clients are stopped,
nor in any phase of the game.

Trantorians have adopted an international time unit.  
The time unit is seconds.  
An action’s execution time is calculated with the following formula: action / f, where **f** is an integer representing the reciprocal (multiplicative inverse) of time unit.

For instance, if f=1, “forward” takes 7 / 1 = 7 seconds.
By default **f=100**.
