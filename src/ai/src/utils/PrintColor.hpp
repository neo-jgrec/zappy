/*
** EPITECH PROJECT, 2024
** zappy/ai/utils
** File description:
** PrintColor.hpp
*/

#ifndef PRINTCOLOR_HPP_
#define PRINTCOLOR_HPP_
#include <iostream>

#define BRIGHT "\x1b[1m"
#define DIM "\x1b[2m"
#define UNDERSCORE "\x1b[4m"
#define BLINK "\x1b[5m"
#define REVERSE "\x1b[7m"
#define HIDDEN "\x1b[8m"

#define BRIGHT_BLACK "\x1b[30;1m"
#define BRIGHT_RED "\x1b[31;1m"
#define BRIGHT_GREEN "\x1b[32;1m"
#define BRIGHT_YELLOW "\x1b[33;1m"
#define BRIGHT_BLUE "\x1b[34;1m"
#define BRIGHT_MAGENTA "\x1b[35;1m"
#define BRIGHT_CYAN "\x1b[36;1m"
#define BRIGHT_WHITE "\x1b[37;1m"

#define BG_BLACK "\x1b[40m"
#define BG_RED "\x1b[41m"
#define BG_GREEN "\x1b[42m"
#define BG_YELLOW "\x1b[43m"
#define BG_BLUE "\x1b[44m"
#define BG_MAGENTA "\x1b[45m"
#define BG_CYAN "\x1b[46m"
#define BG_WHITE "\x1b[47m"

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
