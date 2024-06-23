/*
** EPITECH PROJECT, 2024
** zappy/ai/utils
** File description:
** PrintColor.cpp
*/

#include "PrintColor.hpp"

void printColor(const std::string &message, const std::string &color)
{
    std::cout << color << message << COLOR_RESET;
}

void printKeyValueColored(const std::string &key, const std::string &value)
{
    printKeyValueColored(key, value, PRINT_STATE_INFO);
}
void printKeyValueColored(const std::string &key, const std::string &value, PRINT_STATE state)
{
    std::string color = "";

    if (state == PRINT_STATE_INFO)
        color = BRIGHT_WHITE;
    else if (state == PRINT_STATE_WARNING)
        color = YELLOW;
    else if (state == PRINT_STATE_SUCESS)
        color = GREEN;
    printColor(key + ": ", YELLOW);
    printColor(value + "\n", color);
}
