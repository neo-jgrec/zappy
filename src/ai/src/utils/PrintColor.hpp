/*
** EPITECH PROJECT, 2024
** zappy/ai/utils
** File description:
** PrintColor.hpp
*/

#ifndef PRINTCOLOR_HPP_
#define PRINTCOLOR_HPP_
#include <iostream>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define BLACK "\x1b[30m"

#define BOLD "\x1b[1m"
#define UNDERLINE "\x1b[4m"

#define COLOR_RESET "\x1b[0m"

void printColor(const std::string &message, const std::string &color);
void printKeyValueColored(const std::string &key, const std::string &value);

#endif /* !PRINTCOLOR_HPP_ */