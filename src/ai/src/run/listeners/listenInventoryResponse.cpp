/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenInventoryResponse.cpp
*/

#include "../../bots/ABot.hpp"
#include "../../utils/StringUtils.hpp"

void ABot::listenInventoryResponse(const std::string &response)
{
    std::string cleanResponse = response.substr(1, response.size() - 2);
    cleanResponse.erase(std::remove_if(cleanResponse.begin(), cleanResponse.end(), ::isspace), cleanResponse.end());

    std::vector<std::string> resources = splitByChar(cleanResponse, ',');
    int foodCount = 0;
    // TODO: food is always first so don't need to go through for
    for (const auto &resource : resources)
    {
        std::vector<std::string> parts = splitByChar(resource, ' ');
        if (parts.size() == 2 && parts[0] == "food")
        {
            foodCount = std::stoi(parts[1]);
            break;
        }
    }
    std::cout << "foodCount: " << foodCount << std::endl;
    _state.ressources.food = foodCount;
}
