/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** serverConnect
*/

#ifndef GUIEXCEPTION_HPP
    #define GUIEXCEPTION_HPP

#include "utils/Exception.hpp"

class guiException final : public utils::Exception {
    public:
        guiException(const std::string &message) : Exception("GUI", message) {}
};

#endif // GUIEXCEPTION_HPP
