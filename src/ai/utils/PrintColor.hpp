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

#define COLOR_RESET "\x1b[0m"

void printColor(const std::string &message, const std::string &color);
void printKeyValueColored(const std::string &key, const std::string &value);

#endif /* !PRINTCOLOR_HPP_ */
