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
        // TODO: use cpp function
        //  without term
        //   execl("./zappy_ai", "./zappy_ai", "-p", std::to_string(_port).c_str(), "-n", _teamName.c_str(), "-h", _host.c_str(), nullptr);

        // with term that close
        // execl("/usr/bin/gnome-terminal", "/usr/bin/gnome-terminal", "--", "./zappy_ai", "-p", std::to_string(_port).c_str(), "-n", _teamName.c_str(), "-h", _host.c_str(), nullptr);

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
        /*std::string msg = "you_are_bot=" + std::to_string(_idBot) + "your_job=" + jobMap[SIMPLE_BOT] + "currentMessageId=" + std::to_string(_currentMessageId);
        // sleep(1);
        addBroadcastAction(msg);*/

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
    static unsigned int limitFork = 2; // TODO: it is to debug
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
    else if (handleSurvive())
        return;
    else if ((_state.state == FORKED || _state.slot > 0) && limitFork > 0)
    {
        forkNewBot();
        // TODO: try to put a sleep because server doesn't handle multiple fork in chain sleep(2);
        _idBot++;
        _state.slot--;
        limitFork--;
    }
    else if (_state.slot == 0 && limitFork > 0)
    {
        queue.push_back(std::make_pair([&]()
                                       { doAction(FORK, ""); }, "FORK"));
    }
    else {
        for (auto &_allyMessage : _alliesMessage) {
            if (_allyMessage.content.find("i_have_ressources") != std::string::npos)
            {
                std::string ID = getElementBefore(_allyMessage.content, '/');
                ID = getElementAfter(ID, '}');
                std::string type = getElementAfter(_allyMessage.content, '{');
                type = getElementBefore(type, '}');
                std::string resourcesString = _allyMessage.content.substr(_allyMessage.content.find('?') + 1);
                Ressources ressources = parseRessources(resourcesString);
                if (type == "EVOBOT") {
                    evoBotInventory[std::stoi(ID)] = ressources;
                    _evoBot.ressources += ressources;
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

            if (canLevelUp) {
                std::string message = "group";
                NeededResources remainingRequirements;
                std::pair<NeededResources, std::map<int, Ressources>> deposit = calculateAndPrintBotDeposits(evoBotInventory, _evoBot.level, res.second);
                remainingRequirements = deposit.first;
                std::map<int, Ressources> evoBotContributions = deposit.second;
                std::map<int, Ressources> botContributions = identifyEfficientBots(_evoBot.level, remainingRequirements);
                std::string formattedBotContributions = formatBotContributions(botContributions, evoBotContributions);
            } else {
                std::cout << "Les bots ne peuvent pas évoluer au niveau supérieur de manière efficace.\n";
            }
        }
    }
    sharedInventory.clear();
    _evoBot.ressources.clear();
    _alliesMessage.clear();
    queue.push_back(std::make_pair([&]()
                                       { doAction(FORWARD, ""); }, "FORWARD"));
}

std::string Forker::formatBotContributions(const std::map<int, Ressources>& botContributions, const std::map<int, Ressources>& botContributions2)
{
    std::string formattedString;

    for (const auto& entry : botContributions) {
        int botId = entry.first;
        const Ressources& resources = entry.second;
        formattedString += std::to_string(botId);
        if (resources.linemate > 0) {
            formattedString += "%linemate=" + std::to_string(resources.linemate);
        }
        if (resources.deraumere > 0) {
            formattedString += "%deraumere=" + std::to_string(resources.deraumere);
        }
        if (resources.sibur > 0) {
            formattedString += "%sibur=" + std::to_string(resources.sibur);
        }
        if (resources.mendiane > 0) {
            formattedString += "%mendiane=" + std::to_string(resources.mendiane);
        }
        if (resources.phiras > 0) {
            formattedString += "%phiras=" + std::to_string(resources.phiras);
        }
        if (resources.thystame > 0) {
            formattedString += "%thystame=" + std::to_string(resources.thystame);
        }
        formattedString += "$";
    }

    for (const auto& entry : botContributions2) {
        int botId = entry.first;
        const Ressources& resources = entry.second;
        formattedString += std::to_string(botId);
        if (resources.linemate > 0) {
            formattedString += "%linemate=" + std::to_string(resources.linemate);
        }
        if (resources.deraumere > 0) {
            formattedString += "%deraumere=" + std::to_string(resources.deraumere);
        }
        if (resources.sibur > 0) {
            formattedString += "%sibur=" + std::to_string(resources.sibur);
        }
        if (resources.mendiane > 0) {
            formattedString += "%mendiane=" + std::to_string(resources.mendiane);
        }
        if (resources.phiras > 0) {
            formattedString += "%phiras=" + std::to_string(resources.phiras);
        }
        if (resources.thystame > 0) {
            formattedString += "%thystame=" + std::to_string(resources.thystame);
        }
        formattedString += "$";
    }

    // Remove the last '$' character if present
    if (!formattedString.empty() && formattedString.back() == '$') {
        formattedString.pop_back();
    }
    return formattedString;
}

std::pair<bool, NeededResources> Forker::canLevelUp(int currentLevel)
{
    if (currentLevel < 1 || currentLevel >= levelRequirementsShared.size() + 1) {
        return {false, NeededResources()};
    }

    std::map<int, Ressources> combinedInventory = combineInventories(sharedInventory, evoBotInventory);

    const LevelRequirements& req = levelRequirementsShared[currentLevel - 1];
    NeededResources neededResources;
    Ressources totalRessources;

    totalRessources.linemate = 0;
    totalRessources.deraumere = 0;
    totalRessources.sibur = 0;
    totalRessources.mendiane = 0;
    totalRessources.phiras = 0;
    totalRessources.thystame = 0;

    for (const auto& entry : combinedInventory) {
        const Ressources& resources = entry.second;
        totalRessources.linemate += resources.linemate;
        totalRessources.deraumere += resources.deraumere;
        totalRessources.sibur += resources.sibur;
        totalRessources.mendiane += resources.mendiane;
        totalRessources.phiras += resources.phiras;
        totalRessources.thystame += resources.thystame;
    }

    bool enoughResources =
        totalRessources.linemate >= req.linemate &&
        totalRessources.deraumere >= req.deraumere &&
        totalRessources.sibur >= req.sibur &&
        totalRessources.mendiane >= req.mendiane &&
        totalRessources.phiras >= req.phiras &&
        totalRessources.thystame >= req.thystame;

    if (!enoughResources) {
        neededResources.linemate = std::max(0, static_cast<int>(req.linemate) - totalRessources.linemate);
        neededResources.deraumere = std::max(0, static_cast<int>(req.deraumere) - totalRessources.deraumere);
        neededResources.sibur = std::max(0, static_cast<int>(req.sibur) - totalRessources.sibur);
        neededResources.mendiane = std::max(0, static_cast<int>(req.mendiane) - totalRessources.mendiane);
        neededResources.phiras = std::max(0, static_cast<int>(req.phiras) - totalRessources.phiras);
        neededResources.thystame = std::max(0, static_cast<int>(req.thystame) - totalRessources.thystame);
    }

    return {enoughResources, neededResources};
}

std::map<int, Ressources> Forker::identifyEfficientBots(int currentLevel, NeededResources& neededResources)
{
    std::map<int, Ressources> botContributions;
    NeededResources remainingRequirements = neededResources;

    for (auto& entry : sharedInventory) {
        int botId = entry.first;
        Ressources& botResources = entry.second;

        Ressources botContribution;

        if (remainingRequirements.linemate > 0 && botResources.linemate > 0) {
            int contribution = std::min(remainingRequirements.linemate, botResources.linemate);
            remainingRequirements.linemate -= contribution;
            botResources.linemate -= contribution;
            botContribution.linemate += contribution;
        }
        if (remainingRequirements.deraumere > 0 && botResources.deraumere > 0) {
            int contribution = std::min(remainingRequirements.deraumere, botResources.deraumere);
            remainingRequirements.deraumere -= contribution;
            botResources.deraumere -= contribution;
            botContribution.deraumere += contribution;
        }
        if (remainingRequirements.sibur > 0 && botResources.sibur > 0) {
            int contribution = std::min(remainingRequirements.sibur, botResources.sibur);
            remainingRequirements.sibur -= contribution;
            botResources.sibur -= contribution;
            botContribution.sibur += contribution;
        }
        if (remainingRequirements.mendiane > 0 && botResources.mendiane > 0) {
            int contribution = std::min(remainingRequirements.mendiane, botResources.mendiane);
            remainingRequirements.mendiane -= contribution;
            botResources.mendiane -= contribution;
            botContribution.mendiane += contribution;
        }
        if (remainingRequirements.phiras > 0 && botResources.phiras > 0) {
            int contribution = std::min(remainingRequirements.phiras, botResources.phiras);
            remainingRequirements.phiras -= contribution;
            botResources.phiras -= contribution;
            botContribution.phiras += contribution;
        }
        if (remainingRequirements.thystame > 0 && botResources.thystame > 0) {
            int contribution = std::min(remainingRequirements.thystame, botResources.thystame);
            remainingRequirements.thystame -= contribution;
            botResources.thystame -= contribution;
            botContribution.thystame += contribution;
        }

        if (botContribution.linemate > 0 || botContribution.deraumere > 0 || botContribution.sibur > 0 ||
            botContribution.mendiane > 0 || botContribution.phiras > 0 || botContribution.thystame > 0) {
            botContributions[botId] = botContribution;
            if (remainingRequirements.linemate <= 0 && remainingRequirements.deraumere <= 0 &&
                remainingRequirements.sibur <= 0 && remainingRequirements.mendiane <= 0 &&
                remainingRequirements.phiras <= 0 && remainingRequirements.thystame <= 0) {
                break;
            }
        }
    }
    return botContributions;
}

std::pair<NeededResources, std::map<int, Ressources>>  Forker::calculateAndPrintBotDeposits(std::map<int, Ressources>& sharedInventory, int currentLevel, NeededResources& neededResources)
{
    std::map<int, Ressources> botContributions;
    NeededResources remainingRequirements = neededResources;

    for (auto& entry : sharedInventory) {
        int botId = entry.first;
        Ressources& botResources = entry.second;

        Ressources botContribution;
        botContribution.linemate = 0;
        botContribution.deraumere = 0;
        botContribution.sibur = 0;
        botContribution.mendiane = 0;
        botContribution.phiras = 0;
        botContribution.thystame = 0;

        if (remainingRequirements.linemate > 0 && botResources.linemate > 0) {
            int contribution = std::min(remainingRequirements.linemate, botResources.linemate);
            remainingRequirements.linemate -= contribution;
            botResources.linemate -= contribution;
            botContribution.linemate += contribution;
        }
        if (remainingRequirements.deraumere > 0 && botResources.deraumere > 0) {
            int contribution = std::min(remainingRequirements.deraumere, botResources.deraumere);
            remainingRequirements.deraumere -= contribution;
            botResources.deraumere -= contribution;
            botContribution.deraumere += contribution;
        }
        if (remainingRequirements.sibur > 0 && botResources.sibur > 0) {
            int contribution = std::min(remainingRequirements.sibur, botResources.sibur);
            remainingRequirements.sibur -= contribution;
            botResources.sibur -= contribution;
            botContribution.sibur += contribution;
        }
        if (remainingRequirements.mendiane > 0 && botResources.mendiane > 0) {
            int contribution = std::min(remainingRequirements.mendiane, botResources.mendiane);
            remainingRequirements.mendiane -= contribution;
            botResources.mendiane -= contribution;
            botContribution.mendiane += contribution;
        }
        if (remainingRequirements.phiras > 0 && botResources.phiras > 0) {
            int contribution = std::min(remainingRequirements.phiras, botResources.phiras);
            remainingRequirements.phiras -= contribution;
            botResources.phiras -= contribution;
            botContribution.phiras += contribution;
        }
        if (remainingRequirements.thystame > 0 && botResources.thystame > 0) {
            int contribution = std::min(remainingRequirements.thystame, botResources.thystame);
            remainingRequirements.thystame -= contribution;
            botResources.thystame -= contribution;
            botContribution.thystame += contribution;
        }

        if (botContribution.linemate > 0 || botContribution.deraumere > 0 || botContribution.sibur > 0 ||
            botContribution.mendiane > 0 || botContribution.phiras > 0 || botContribution.thystame > 0) {
            botContributions[botId] = botContribution;
            if (remainingRequirements.linemate <= 0 && remainingRequirements.deraumere <= 0 &&
                remainingRequirements.sibur <= 0 && remainingRequirements.mendiane <= 0 &&
                remainingRequirements.phiras <= 0 && remainingRequirements.thystame <= 0) {
                break;
            }
        }
    }
    return {remainingRequirements, botContributions};
}

std::map<int, Ressources> Forker::combineInventories(const std::map<int, Ressources>& inventory1, const std::map<int, Ressources>& inventory2)
{
    std::map<int, Ressources> combinedInventory = inventory1;
    for (const auto& entry : inventory2) {
        int botId = entry.first;
        const Ressources& resources = entry.second;
        combinedInventory[botId].linemate += resources.linemate;
        combinedInventory[botId].deraumere += resources.deraumere;
        combinedInventory[botId].sibur += resources.sibur;
        combinedInventory[botId].mendiane += resources.mendiane;
        combinedInventory[botId].phiras += resources.phiras;
        combinedInventory[botId].thystame += resources.thystame;
        combinedInventory[botId].food += resources.food;
    }
    return combinedInventory;
}

bool Forker::handleSurvive()
{
    static int searchFood = 0;
    const int limitFood = 50;

    if (_iteration % 40 == 0)
    {
        _state.state = STANDARD;
        queue.push_back({[&]()
                         { doAction(INVENTORY, ""); }, "INVENTORY"});
        return true;
    }

    if (_state.ressources.food < limitFood)
    {
        // TODO: we want differant searchFood for each level ?
        searchFood = 250;
    }
    if (searchFood > 0)
    {
        if (searchFood == 1)
            queue.push_back({[&]()
                             { doAction(INVENTORY, ""); }, "INVENTORY"});
        else
            survive();
        _state.state = STANDARD;
        _state.pattern = "survive";
        searchFood--;
        return true;
    }
    return false;
}