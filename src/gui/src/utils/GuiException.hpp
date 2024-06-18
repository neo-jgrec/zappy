/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GuiException
*/

#ifndef GUIEXCEPTION_HPP
    #define GUIEXCEPTION_HPP

#include "Exception.hpp"

class guiException final : public utils::Exception {
    public:
        guiException(const std::string &message) : Exception("GUI", message) {}
};

#endif // GUIEXCEPTION_HPP
