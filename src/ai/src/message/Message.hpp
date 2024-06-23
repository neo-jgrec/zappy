/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** message.hpp
*/

#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <iostream>
#include <iostream>
#include <string>
#include <map>
#include <ctime>

class Message
{
public:
    Message(const std::string &contentMsg, std::string direction);
    Message(const std::string &contentMsg);
    Message();
    ~Message();
    void vigenereDecrypt();
    void vigenereEncrypt();
    std::string getCurrentTimeAsLetters();
    void generateMessage();
    void format(const std::string &contentMsg);
    std::string convertDigitsToLetters(const std::string &digits);
    std::string content;
    std::string direction;
    int id;

private:
    std::string _conversionTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string _signature = "bFNneQbXQkyJHGEQd";
};

#endif // MESSAGE_HPP_