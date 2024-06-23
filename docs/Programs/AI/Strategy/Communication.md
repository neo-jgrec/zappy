# Communication

## Scope

This documentation covers the communication system, which allows bots to communicate with each other.

## Problematic

In the Zappy project, bots need to be able to communicate with each other in order to coordinate their actions. The problem is that the bots need to broadcast their information to be able to communicate with their allies but that means that the other teams can also hear the information. This can be solved by implementing a communication system that securely allows bots to communicate with each other.

## Security

### Encryption & Decryption

The communication system uses the vignere cipher to encrypt messages. The key is randomly generated at the start of the game and is shared between all the bots on the same team. This ensures that only bots on the same team can decrypt the messages.

```cpp
void Message::vigenereEncrypt()
{
    std::string result = content;
    int keyIndex = 0;
    const std::string &key = generate();

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
    const std::string &key = generate();

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
```

### Authentication

The communication system uses a response authentication system to verify the identity of the bots. When a bot is created the Forker will respond by saying which id he is and what role he has. The bot then has to respond with the correct id and role to authenticate itself.

```cpp
std::cout << "identityMessage: " << identityMessage << std::endl;
std::string job = "";
std::string prefixId = "you_are_bot=";
std::string prefixJob = "your_job=";
std::string prefixCurrentMessageId = "currentMessageId=";
size_t pos = identityMessage.find(prefixId);
size_t posJob = identityMessage.find(prefixJob);
size_t posCurrentMessageId = identityMessage.find(prefixCurrentMessageId);
std::cout << "identify message: " << identityMessage << "\n";
```

### Signature

At the end of each message, the bot will sign the message. This allows the other bots to verify that the message has not been tampered with and that it was sent by an ally.

```cpp
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
```

### Offense

The communication system has a defense mechanism but also a offense mechanism. If a bot receives a message that is not signed by an ally, the bot will store the message and then at an interval it'll modifie the message to corrupt the data and then send it back without signing it so it can't affect our team.

```cpp
if (signature != _signature)
{
    _enemyMessage.content = _message.content;
    std::cout << "Enemy message: " << _enemyMessage.content << std::endl;
    return;
}
std::string trapMessage = replaceNumbersInString(_enemyMessage.content, 1200);
if (trapMessage.empty())
    trapMessage = _enemyMessage.content;
std::cout << "trapMessage: " << trapMessage << std::endl;
addBroadcastAction(trapMessage);
```