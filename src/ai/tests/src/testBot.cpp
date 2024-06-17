/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Bot.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../../src/utils/StringUtils.hpp"
#include "../../src/Bot.hpp"

Test(strings_utils, replaceNumbersInString)
{
    std::string str = "Hello 32";
    std::string res = replaceNumbersInString(str, 10);
    cr_assert_str_eq(res.c_str(), "Hello 42");
}

Test(strings_utils, getElementAfter)
{
    std::string str = "Hello:World";
    std::string res = getElementAfter(str, ':');
    cr_assert_str_eq(res.c_str(), "World");
}

Test(strings_utils, getElementBefore)
{
    std::string str = "Hello:World";
    std::string res = getElementBefore(str, ':');
    cr_assert_str_eq(res.c_str(), "Hello");
}

Test(strings_utils, generateNewNumber)
{
    std::string str = "32";
    std::string res = generateNewNumber(str, 10);
    cr_assert_str_eq(res.c_str(), "42");
}

Test(message, vignereEncrypt)
{
    Message message;

    message._content = "group";
    message.vigenereEncrypt();
    cr_assert_str_eq(message._content.c_str(), "qzaor");
}

Test(message, vignereDecrypt)
{
    Message message;

    message._content = "qzaor";
    message.vigenereDecrypt();
    cr_assert_str_eq(message._content.c_str(), "group");
}

Test(message, generateMessage)
{
    Message message;

    message._content = "group";
    message.generateMessage();
    cr_assert_str_eq(message._content.c_str(), "group:bFNneQbXQkyJHGEQd");
}

Test(message, convertDigitsToLetters)
{
    Message message;

    std::string res = message.convertDigitsToLetters("123");
    cr_assert_str_eq(res.c_str(), "DCB");
}