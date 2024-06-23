/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Forker.cpp
*/

#include "Forker.hpp"
#include "SimpleBot.hpp"

void Forker::initChild()
{
    std::cout << "🍴✅ Forker initialized" << std::endl;
}

void Forker::forkNewBot()
{
    pid_t pid = fork();

    if (pid == -1)
    {
        std::cerr << "Fork failed" << std::endl;
        return;
    }

    if (pid == 0)
    {
        // without term
        //  execl("./zappy_ai", "./zappy_ai", "-p", std::to_string(_port).c_str(), "-n", _teamName.c_str(), "-h", _host.c_str(), nullptr);

        // with term that close
        //  execl("/usr/bin/gnome-terminal", "/usr/bin/gnome-terminal", "--", "./zappy_ai", "-p", std::to_string(_port).c_str(), "-n", _teamName.c_str(), "-h", _host.c_str(), nullptr);

        //  with term that stay open
        execl("/usr/bin/gnome-terminal", "/usr/bin/gnome-terminal", "--", "bash", "-c",
          ("trap 'echo \"[DEBUG]\"; kill -INT $$' SIGINT; ./zappy_ai -p " + std::to_string(_port) + " -n " + _teamName + " -h " + _host + "; exec bash").c_str(), nullptr);

        std::cerr << "execl failed" << std::endl;
        while (1)
            ;
    }
    else
    {
        _message.format("you_are_bot=" + std::to_string(_idBot) + "your_job=" + jobMap[SLAVE] + "currentMessageId=" + std::to_string(_currentMessageId));
        queue.push_back(std::make_pair([&]()
                                       { doAction(BROADCAST, _message.content); }, "FORK"));

        wait(nullptr);
    }
}

Ressources Forker::parseRessources(const std::string& ressourcesString)
{
    Ressources ressources;
    std::istringstream stream(ressourcesString);
    std::string pair;

    while (std::getline(stream, pair, '|'))
    {
        size_t equalSignPos = pair.find('=');
        if (equalSignPos != std::string::npos)
        {
            std::string key = pair.substr(0, equalSignPos);
            size_t value = std::stoul(pair.substr(equalSignPos + 1));
            ressources.addRessourceByQuantity(key, value);
        }
    }

    return ressources;
}


void Forker::updateStrategy()
{
    //Todo fix when 2 bot are init
    static unsigned int canFork = 2; // TODO: it is to debug
    static bool verifySlot = true;
    bool done = false;
    bool canProcess = false;

    std::cout << "🍴 Forker updateStrategy" << std::endl;
    if (canFork > 0)
    {
        forkNewBot();
        _idBot++;
        _state.slot--;
        canFork--;
        done = true;
        return;
    } else 

    if (_iteration >= 10 && _iteration % 5 == 0)
    {
        _message.format("send_ressources");
        queue.push_back(std::make_pair([&]()
                                       { doAction(BROADCAST, _message.content); }, "BROADCAST"));
        done = true;
        return;
    }
    else if (verifySlot)
    {
        _state.slot = 0;
        queue.push_back(std::make_pair([&]()
                                       { doAction(CONNECT_NBR, ""); }, "CONNECT_NBR"));
        verifySlot = false;
        done = true;
        return;
    }
    else if (_state.ressources.food < 5)
    {
        survive();
        done = true;
        return;
    }
    else if (_state.slot == 0 && canFork > 0)
    {
        queue.push_back(std::make_pair([&]()
                                       { doAction(FORK, ""); }, "FORK"));
        done = true;
        return;
    }
    else {
        for (auto &_allyMessage : _alliesMessage) {
            if (_allyMessage.content.find("i_have_ressources") != std::string::npos)
            {
                std::string ID = getElementBefore(_allyMessage.content, '/');
                std::string resourcesString = _allyMessage.content.substr(_allyMessage.content.find('?') + 1);
                Ressources ressources = parseRessources(resourcesString);
                if (ID == "1") {
                    _evoBot.ressources = ressources;
                    _evoBot.level = stoi(getElementAfter(resourcesString, '&'));
                } else {
                    sharedInventory[std::stoi(ID)] = ressources;
                }
                canProcess = true;
            }
        }
        if (canProcess) {
            std::pair<bool, NeededResources> res = canLevelUp(_evoBot.level);
            bool canLevelUp = res.first;
            NeededResources neededResources = res.second;

            if (canLevelUp)
            {
                std::cout << "Les bots peuvent évoluer au niveau supérieur de manière efficace.\n";
                std::vector<int> efficientBots = identifyEfficientBots(_evoBot.level, neededResources);

                std::cout << "Bots efficaces pour aider : ";
                for (int bot : efficientBots) {
                    std::cout << bot << " ";
                }
                std::cout << "\n";
            } else {
                for (const auto& entry : sharedInventory) {
                    int botId = entry.first;
                    const Ressources& botResources = entry.second;
                    std::cout << "Bot " << botId << " : linemate=" << botResources.linemate << " deraumere=" << botResources.deraumere << " sibur=" << botResources.sibur << " mendiane=" << botResources.mendiane << " phiras=" << botResources.phiras << " thystame=" << botResources.thystame << "\n";
                }
                std::cout << "Les bots ne peuvent pas évoluer au niveau supérieur de manière efficace.\n";
            }
        }
    }
    sharedInventory.clear();
    _alliesMessage.clear();
    queue.push_back(std::make_pair([&]()
                                       { doAction(FORWARD, ""); }, "FORWARD"));
}

std::pair<bool, NeededResources> Forker::canLevelUp(int currentLevel)
{
    if (currentLevel < 1 || currentLevel >= levelRequirementsShared.size() + 1) {
        return {false, NeededResources()};
    }

    const LevelRequirements& req = levelRequirementsShared[currentLevel - 1];
    NeededResources neededResources;

    neededResources.linemate = std::max(0, static_cast<int>(req.linemate) - static_cast<int>(_evoBot.ressources.linemate));
    neededResources.deraumere = std::max(0, static_cast<int>(req.deraumere) - static_cast<int>(_evoBot.ressources.deraumere));
    neededResources.sibur = std::max(0, static_cast<int>(req.sibur) - static_cast<int>(_evoBot.ressources.sibur));
    neededResources.mendiane = std::max(0, static_cast<int>(req.mendiane) - static_cast<int>(_evoBot.ressources.mendiane));
    neededResources.phiras = std::max(0, static_cast<int>(req.phiras) - static_cast<int>(_evoBot.ressources.phiras));
    neededResources.thystame = std::max(0, static_cast<int>(req.thystame) - static_cast<int>(_evoBot.ressources.thystame));

    Ressources totalRessources;

    totalRessources.linemate = 0;
    totalRessources.deraumere = 0;
    totalRessources.sibur = 0;
    totalRessources.mendiane = 0;
    totalRessources.phiras = 0;
    totalRessources.thystame = 0;

    int playerCount = 0;

    for (const auto& entry : sharedInventory) {
        const Ressources& resources = entry.second;
        totalRessources.linemate += resources.linemate;
        totalRessources.deraumere += resources.deraumere;
        totalRessources.sibur += resources.sibur;
        totalRessources.mendiane += resources.mendiane;
        totalRessources.phiras += resources.phiras;
        totalRessources.thystame += resources.thystame;
        playerCount++;
    }

    bool enoughPlayers = playerCount >= req.nbPlayers;

    bool enoughResources =
        totalRessources.linemate >= req.linemate &&
        totalRessources.deraumere >= req.deraumere &&
        totalRessources.sibur >= req.sibur &&
        totalRessources.mendiane >= req.mendiane &&
        totalRessources.phiras >= req.phiras &&
        totalRessources.thystame >= req.thystame;
    if (enoughResources && !enoughPlayers) {
        int bestBotId = -1;
        int bestScore = std::numeric_limits<int>::max();

        for (const auto& entry : sharedInventory) {
            int botId = entry.first;
            const Ressources& resources = entry.second;
            if (!(resources.linemate >= req.linemate &&
                  resources.deraumere >= req.deraumere &&
                  resources.sibur >= req.sibur &&
                  resources.mendiane >= req.mendiane &&
                  resources.phiras >= req.phiras &&
                  resources.thystame >= req.thystame)) {
                int score =
                    std::abs(static_cast<int>(resources.linemate) - static_cast<int>(req.linemate)) +
                    std::abs(static_cast<int>(resources.deraumere) - static_cast<int>(req.deraumere)) +
                    std::abs(static_cast<int>(resources.sibur) - static_cast<int>(req.sibur)) +
                    std::abs(static_cast<int>(resources.mendiane) - static_cast<int>(req.mendiane)) +
                    std::abs(static_cast<int>(resources.phiras) - static_cast<int>(req.phiras)) +
                    std::abs(static_cast<int>(resources.thystame) - static_cast<int>(req.thystame));
                if (score < bestScore) {
                    bestScore = score;
                    bestBotId = botId;
                }
            }
        }

        if (bestBotId != -1) {
            return {true, neededResources};
        }
    }
    return {enoughPlayers && enoughResources, neededResources};
}

std::vector<int> Forker::identifyEfficientBots(int currentLevel, const NeededResources& neededResources)
{
    std::vector<int> efficientBots;
    NeededResources remainingRequirements = neededResources;

    for (const auto& entry : sharedInventory) {
        int botId = entry.first;
        const Ressources& botResources = entry.second;

        bool canContribute = false;

        if (remainingRequirements.linemate > 0 && botResources.linemate > 0) {
            remainingRequirements.linemate -= std::min(remainingRequirements.linemate, botResources.linemate);
            canContribute = true;
        }
        if (remainingRequirements.deraumere > 0 && botResources.deraumere > 0) {
            remainingRequirements.deraumere -= std::min(remainingRequirements.deraumere, botResources.deraumere);
            canContribute = true;
        }
        if (remainingRequirements.sibur > 0 && botResources.sibur > 0) {
            remainingRequirements.sibur -= std::min(remainingRequirements.sibur, botResources.sibur);
            canContribute = true;
        }
        if (remainingRequirements.mendiane > 0 && botResources.mendiane > 0) {
            remainingRequirements.mendiane -= std::min(remainingRequirements.mendiane, botResources.mendiane);
            canContribute = true;
        }
        if (remainingRequirements.phiras > 0 && botResources.phiras > 0) {
            remainingRequirements.phiras -= std::min(remainingRequirements.phiras, botResources.phiras);
            canContribute = true;
        }
        if (remainingRequirements.thystame > 0 && botResources.thystame > 0) {
            remainingRequirements.thystame -= std::min(remainingRequirements.thystame, botResources.thystame);
            canContribute = true;
        }

        if (canContribute) {
            efficientBots.push_back(botId);
            if (remainingRequirements.linemate <= 0 && remainingRequirements.deraumere <= 0 &&
                remainingRequirements.sibur <= 0 && remainingRequirements.mendiane <= 0 &&
                remainingRequirements.phiras <= 0 && remainingRequirements.thystame <= 0) {
                break;
            }
        }
    }
    int neededPlayers = levelRequirementsShared[currentLevel - 1].nbPlayers;
    if (efficientBots.size() < neededPlayers) {
        std::vector<int> remainingBots;
        for (const auto& entry : sharedInventory) {
            if (std::find(efficientBots.begin(), efficientBots.end(), entry.first) == efficientBots.end()) {
                remainingBots.push_back(entry.first);
            }
        }
        int nextLevel = currentLevel + 1;
        std::vector<std::pair<int, int>> botScores;
        for (int botId : remainingBots) {
            const Ressources& botResources = sharedInventory.at(botId);

            int score =
                std::abs(static_cast<int>(botResources.linemate) - static_cast<int>(levelRequirementsShared[nextLevel - 1].linemate)) +
                std::abs(static_cast<int>(botResources.deraumere) - static_cast<int>(levelRequirementsShared[nextLevel - 1].deraumere)) +
                std::abs(static_cast<int>(botResources.sibur) - static_cast<int>(levelRequirementsShared[nextLevel - 1].sibur)) +
                std::abs(static_cast<int>(botResources.mendiane) - static_cast<int>(levelRequirementsShared[nextLevel - 1].mendiane)) +
                std::abs(static_cast<int>(botResources.phiras) - static_cast<int>(levelRequirementsShared[nextLevel - 1].phiras)) +
                std::abs(static_cast<int>(botResources.thystame) - static_cast<int>(levelRequirementsShared[nextLevel - 1].thystame));

            botScores.push_back(std::make_pair(botId, score));
        }

        std::sort(botScores.begin(), botScores.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.second < rhs.second;
        });

        for (const auto& botScore : botScores) {
            if (efficientBots.size() < neededPlayers) {
                efficientBots.push_back(botScore.first);
            } else {
                break;
            }
        }
    }

    return efficientBots;
}
