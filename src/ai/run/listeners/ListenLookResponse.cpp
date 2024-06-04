/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenLookResponse.cpp
*/

#include "../../Bot.hpp"

void Bot::listenLookResponse(const std::string &response)
{
    // Remove brackets
    std::string cleanedResponse = response.substr(1, response.size() - 2);

    std::istringstream iss(cleanedResponse);
    std::string firstTile;
    std::getline(iss, firstTile, ',');

    state.environment.clear();

    std::istringstream tileStream(firstTile);
    std::string item;

    // print first tile result
    // while (tileStream >> item)
    // {
    //     std::cout << "first tile: " << item << std::endl;
    // }
}
