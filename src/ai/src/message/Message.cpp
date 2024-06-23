/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** message.hpp
*/

#include "Message.hpp"

Message::Message(const std::string &contentMsg, std::string direction)
{
    content = contentMsg;
    this->direction = direction;
}

Message::Message(const std::string &contentMsg)
{
    content = contentMsg;
}

Message::Message()
{
}

Message::~Message()
{
}

std::string Message::convertDigitsToLetters(const std::string &digits)
{
    const std::string conversionTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::string letters;
    for (char digit : digits)
    {
        if (isdigit(digit))
        {
            unsigned int index = digit - '0';

            if (index < conversionTable.size())
            {
                letters += conversionTable[index];
            }
        }
    }
    for (unsigned int i = 0; i < letters.length() / 2; i++)
        std::swap(letters[i], letters[letters.length() - i - 1]);
    return letters;
}

std::string Message::getCurrentTimeAsLetters()
{
    std::time_t now = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y%m%d%H%M", std::localtime(&now));
    std::string digits(buf);
    return convertDigitsToLetters(digits);
}

void Message::generateMessage()
{
    content = content + ":" + _signature;
}

void Message::format(const std::string &contentToFormat)
{
    content = contentToFormat;
    vigenereEncrypt();
    generateMessage();
}

void Message::vigenereEncrypt()
{
    std::string result = content;
    int keyIndex = 0;
    const std::string &key = "KIMUCHI";

    for (unsigned int i = 0; i < content.length(); ++i)
    {
        if (isalpha(content[i]))
        {
            char base = islower(content[i]) ? 'a' : 'A';
            char shiftedChar = (content[i] - base + tolower(key[keyIndex]) - 'a') % 26 + base;
            result[i] = shiftedChar;
            keyIndex = (keyIndex + 1) % key.length();
        }
    }
    content = result;
}

void Message::vigenereDecrypt()
{
    std::string result = content;
    int keyIndex = 0;
    const std::string &key = "KIMUCHI";

    for (unsigned int i = 0; i < content.length(); ++i)
    {
        if (isalpha(content[i]))
        {
            char base = islower(content[i]) ? 'a' : 'A';
            char shiftedChar = content[i] - base;
            char keyOffset = tolower(key[keyIndex]) - 'a';

            char originalChar = (shiftedChar - keyOffset + 26) % 26 + base;
            result[i] = originalChar;

            keyIndex = (keyIndex + 1) % key.length();
        }
    }
    content = result;
}