/*
** EPITECH PROJECT, 2024
** zappy/ai/utils
** File description:
** initializer.hpp
*/

#ifndef INITIALIZER_HPP_
#define INITIALIZER_HPP_

#include <iostream>
#include "DisplayHelp.hpp"
#include "../constant/Constants.hpp"

class Initializer
{
public:
    Initializer();
    ~Initializer();

    unsigned int port;
    std::string teamName;
    std::string host;
    bool debug; // TODO: use --debug

    void parseArguments(int ac, char **av);

    // Exceptions
    class InitializerException : public std::exception
    {
    public:
        InitializerException(const std::string &msg) : _msg(msg) {}
        const char *what() const noexcept override { return _msg.c_str(); }

    private:
        std::string _msg;
    };
};
#endif // INITIALIZER_HPP_
