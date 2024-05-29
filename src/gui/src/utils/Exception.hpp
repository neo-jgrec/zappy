/*
** EPITECH PROJECT, 2024
** Zappy GUI
** File description:
** Exceptions
*/

#ifndef EXCEPTIONS_HPP
    #define EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace utils
{
    class Exception : public std::exception {
    public:
        Exception(const std::string &name, const std::string &message) : _message(name + ": " + message) {}
        [[nodiscard]] const char *what() const noexcept override { return _message.c_str(); }

    private:
        std::string _message;
    };
} // namespace utils

#endif // EXCEPTIONS_HPP
