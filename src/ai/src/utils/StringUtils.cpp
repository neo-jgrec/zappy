/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** DisplayHelp.hpp
*/

#include "StringUtils.hpp"

std::string getElementAfter(const std::string& input, char delimiter)
{
    std::istringstream iss(input);
    std::string token;
    
    while (std::getline(iss, token, delimiter)) {
        if (iss >> token) {
            return token;
        }
    }

    return "";
}

std::string getElementBefore(const std::string& input, char delimiter)
{
    std::istringstream iss(input);
    std::string token;
    
    while (std::getline(iss, token, delimiter)) {
        if (iss >> token) {
            return input.substr(0, input.find(delimiter));
        }
    }

    return "";
}

std::string generateNewNumber(const std::string &oldNumber, int offset)
{
    int num = std::stoi(oldNumber);
    return std::to_string(num + offset);
}

std::string replaceNumbersInString(const std::string &input, int offset)
{
    std::regex numberRegex("\\d+");
    std::string output = input;

    std::sregex_iterator currentMatch(input.begin(), input.end(), numberRegex);
    std::sregex_iterator lastMatch;

    std::vector<std::pair<size_t, std::string>> replacements;

    while (currentMatch != lastMatch) {
        std::smatch match = *currentMatch;
        std::string oldNumber = match.str();
        std::string newNumber = generateNewNumber(oldNumber, offset);
        replacements.push_back(
            {match.position(), newNumber}
        );
        ++currentMatch;
    }

    for (auto it = replacements.rbegin(); it != replacements.rend(); ++it) {
        output.replace(it->first, it->second.length(), it->second);
    }

    return output;
}