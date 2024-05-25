/*
** EPITECH PROJECT, 2024
** zappy/utils
** File description:
** DisplayHelp.cpp
*/

#include <fstream>
#include <iostream>

static void printFileContentError(const std::string &filePath)
{
    std::ifstream file(filePath);

    if (file.is_open())
    {
        std::string line;

        while (std::getline(file, line))
        {
            std::cerr << line << '\n';
        }
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << filePath << '\n';
    }
}

void displayHelp()
{
    printFileContentError("../assets/help.txt");
}
