/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** DisplayHelp.hpp
*/

#ifndef STRINGUTILS_HPP_
#define STRINGUTILS_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <regex>

std::string replaceNumbersInString(const std::string &input, int offset);
std::string generateNewNumber(const std::string &oldNumber, int offset);
std::string getElementAfter(const std::string &input, char delimiter);
std::string getElementBefore(const std::string &input, char delimiter);
std::string cleanCarriageReturn(const std::string &input);

#endif // STRINGUTILS_HPP_