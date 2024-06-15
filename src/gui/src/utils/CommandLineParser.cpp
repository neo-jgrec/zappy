#include "CommandLineParser.hpp"

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <tuple>

void CommandLineParser::addOption(const std::string &longOpt, const std::string &shortOpt, const std::string &description)
{
    options[longOpt] = std::make_tuple(shortOpt, description, std::nullopt);
}

void CommandLineParser::parse()
{
    for (std::size_t i = 1; i < args.size(); ++i) {
        if (args[i][0] != '-')
            continue;
        std::string option = args[i];
        std::string argument;

        bool optionFound = false;
        for (const auto &[fst, snd] : options) {
            if (option == fst || std::get<0>(snd) == option) {
                option = (fst == option) ? option : (std::get<0>(snd) == option) ? fst : option;
                if (i + 1 < args.size() && args[i + 1][0] != '-') {
                    argument = args[i + 1];
                    ++i;
                }
                optionFound = true;
                break;
            }
        }

        if (!optionFound)
            throw std::runtime_error("Unknown option: " + option);

        options[option] = std::make_tuple(std::get<0>(options[option]), std::get<1>(options[option]), argument);
    }
}

[[nodiscard]] std::optional<std::string> CommandLineParser::getOption(const std::string &longOpt) const
{
    if (options.count(longOpt) == 0)
        return std::nullopt;
    return std::get<2>(options.at(longOpt));
}

void CommandLineParser::displayHelp(const std::string &binaryName) const
{
    std::cout << "Usage: " << binaryName;
    for (const auto &[fst, snd] : options) {
        std::string longOpt = fst;
        std::string shortOpt = std::get<0>(snd);
        std::string description = std::get<1>(snd);
        std::cout << " ";
        if (!shortOpt.empty())
            std::cout << std::setw(2) << shortOpt << ", ";
        std::cout << std::setw(10) << std::left << longOpt << " [";
        if (!description.empty())
            std::cout << description;
        std::cout << "]\n";
    }
}
