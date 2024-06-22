/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenInventoryresponseCopy.cpp
*/

#include "../../bots/ABot.hpp"
#include "../../utils/StringUtils.hpp"

void ABot::listenInventoryResponse(const std::string &response)
{
    const std::string responseCopy = response;

    if (responseCopy.size() < 2 || responseCopy.front() != '[' || responseCopy.back() != ']')
    {
        std::cerr << "Invalid responseCopy format" << std::endl;
        return;
    }

    std::string cleanresponseCopy = responseCopy.substr(1, responseCopy.size() - 2);

    std::vector<std::string> resources = splitByChar(cleanresponseCopy, ',');
    int foodCount = 0;

    for (const auto &resource : resources)
    {
        std::string trimmedResource = resource;
        trimmedResource.erase(trimmedResource.begin(), std::find_if(trimmedResource.begin(), trimmedResource.end(), [](unsigned char ch)
                                                                    { return !std::isspace(ch); }));
        trimmedResource.erase(std::find_if(trimmedResource.rbegin(), trimmedResource.rend(), [](unsigned char ch)
                                           { return !std::isspace(ch); })
                                  .base(),
                              trimmedResource.end());

        std::vector<std::string> parts = splitByChar(trimmedResource, ' ');
        if (parts.size() == 2 && parts[0] == "food")
        {
            try
            {
                foodCount = std::stoi(parts[1]);
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Invalid number format: " << parts[1] << std::endl;
                return;
            }
            catch (const std::out_of_range &e)
            {
                std::cerr << "Number out of range: " << parts[1] << std::endl;
                return;
            }
            break;
        }
    }
    _state.ressources.food = foodCount;
}
