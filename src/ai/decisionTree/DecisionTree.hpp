/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** DecisionTree.hpp
*/

#ifndef DECISIONTREE_HPP_
#define DECISIONTREE_HPP_

#include <iostream>
#include <vector>
#include <functional>
#include <memory>

class Node
{
    double probability;
    std::function<void(std::string parameter)> action;
    std::vector<std::shared_ptr<Node>> children;
};

class DecisionTree
{
public:
    DecisionTree(Node root);
    ~DecisionTree();
};
#endif
