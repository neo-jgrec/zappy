/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Constants.hpp
*/

#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

#include <array>
#include <unordered_map>
#include <vector>

/*const std::array<std::array<unsigned int, 6>, 9> levelRequirements = {{
    {0, 0, 0, 0, 0, 0}, // Level 0
    {0, 0, 0, 0, 0, 0}, // Level 1
    {1, 0, 0, 0, 0, 0}, // Level 2
    {1, 1, 1, 0, 0, 0}, // Level 3
    {2, 0, 1, 0, 2, 0}, // Level 4
    {1, 1, 2, 0, 1, 0}, // Level 5
    {1, 2, 1, 3, 0, 0}, // Level 6
    {1, 2, 3, 0, 1, 0}, // Level 7
    {2, 2, 2, 2, 2, 1}  // Level 8
}};*/

struct LevelRequirements {
    size_t nbPlayers;
    size_t linemate;
    size_t deraumere;
    size_t sibur;
    size_t mendiane;
    size_t phiras;
    size_t thystame;
};

const std::vector<LevelRequirements> levelRequirementsShared = {
    {1, 1, 1, 0, 0, 0, 0}, // Level 1 -> 2
    {2, 1, 1, 1, 0, 0, 0}, // Level 2 -> 3
    {2, 2, 0, 1, 0, 2, 0}, // Level 3 -> 4
    {4, 1, 1, 2, 0, 1, 0}, // Level 4 -> 5
    {4, 1, 2, 1, 3, 0, 0}, // Level 5 -> 6
    {6, 1, 2, 3, 0, 1, 0}, // Level 6 -> 7
    {6, 2, 2, 2, 2, 2, 1}  // Level 7 -> 8
};

struct NeededResources {
    size_t linemate = 0;
    size_t deraumere = 0;
    size_t sibur = 0;
    size_t mendiane = 0;
    size_t phiras = 0;
    size_t thystame = 0;
};

#define PRINT_ERROR(errorMsg) std::cerr << "\033[31mError: " << errorMsg << " occurred in file " << __FILE__ << " at line " << __LINE__ << "\033[0m" << std::endl;

#define PRINT_ALERT(infoMsg) printColor(std::string("🚨🚨🚨") + (infoMsg), RED);

#define SUCCESS 0
#define FAILURE 84

#endif // CONSTANTS_HPP_
