/*
** EPITECH PROJECT, 2024
** zappy/ai/hash
** File description:
** Pairhash.hpp
*/

#ifndef PAIRHASH_HPP_
#define PAIRHASH_HPP_

#include <iostream>

class PairHash
{
public:
    std::size_t operator()(const std::pair<int, int> &p) const
    {
        auto hash1 = std::hash<int>{}(p.first);
        auto hash2 = std::hash<int>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

#endif // PAIRHASH_HPP_
