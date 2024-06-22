/*
** EPITECH PROJECT, 2024
** zappy/ai/verification
** File description:
** IsConcernedByIncantation.hpp
*/

#include "../ABotPattern.hpp"

bool ABotPattern::isConcernedByIncantation()
{
    return (_state.lastAction.action == INCANTATION || _state.metadata["wait_incant"] == "true");
}