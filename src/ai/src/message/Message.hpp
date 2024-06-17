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
        Message(const std::string &content);
        Message();
        ~Message();
        void vigenereDecrypt();
        void vigenereEncrypt();
        std::string getCurrentTimeAsLetters();
        void generateMessage();
        std::string convertDigitsToLetters(const std::string& digits);
        std::string _content;
        int _id;
    private:
        std::string _conversionTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string _signature = "bFNneQbXQkyJHGEQd";
};

#endif // MESSAGE_HPP_