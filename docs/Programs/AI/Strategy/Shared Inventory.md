# Shared Inventory

*code not implemented in the main program. If u want to check it go in the github repository and in the branch feat/ia-sharedInvAlgo*

## Scope

This documentation covers the shared inventory system, which allows multiple agents to interact with a shared inventory.

## Problematic

In the Zappy project, all of the AI's have their own inventory. This can lead to inefficiencies, as bots may not be able to perform certain actions due to a lack of resources. This can be solved by implementing a shared inventory system so that bots can share resources.

## Hierarchy

- 1 **Forker**
- 6 **Evo Bots**
- Infinite **Slave Bots**

## Roles

### Forker

- **Role**: 
    - Create new bots.
    - Assigns roles to newly created bots.
    - Acts as a medium, providing instructions to other bots to facilitate their coordination and grouping.
    - Master of the communication system.

### Evo Bots

- **Role**: 
    - Collect resources.
    - Deposit resources.
    - Interact with the environment.
    - Communicate with other bots.
    - Group to perform Incantation and Evolve.

### Slave Bots

- **Role**: 
    - Collect resources.
    - Deposit resources.
    - Interact with the environment.
    - If call then come and give resources to Evo Bots.

## Algorithm

- Each 10 iterations, Forker broadcast to all the bots a message to ask about the content of their iventory.
```cpp
if (_iteration > 10 && _iteration % 10 == 0)
{
    _message.format("send_ressources");
    queue.push_back(std::make_pair([&]()
                                   { doAction(BROADCAST, _message.content); }, "BROADCAST"));
    done = true;
    return;
}
```

- Each bot responds with the content of their inventory.
```cpp
for (auto &_allyMessage : _alliesMessage) {
    if (_allyMessage.content.find("send_ressources") != std::string::npos && _state.level == 2 && (_state.lastAction.action != INCANTATION)) {
        std::string _msg = "{EVOBOT}" + std::to_string(_id) + "/i_have_ressources?" +
        "linemate=" + std::to_string(_state.ressources.linemate) + "|" +
        "deraumere=" + std::to_string(_state.ressources.deraumere) + "|" +
        "sibur=" + std::to_string(_state.ressources.sibur) + "|" +
        "mendiane=" + std::to_string(_state.ressources.mendiane) + "|" +
        "phiras=" + std::to_string(_state.ressources.phiras) + "|" +
        "thystame=" + std::to_string(_state.ressources.thystame) + "&" + std::to_string(_state.level); 
        std::cout << _msg << std::endl;
        _message.format(_msg);
        queue.push_back(std::make_pair([&]()
                                    { doAction(BROADCAST, _message.content); }, "BROADCAST"));
    }
}
```
- Forker then fill map with the id of the bot and the content of their inventory.
```cpp
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
```
- Forker then check if the shared inventory has enough ressources to perform an incantation.
```cpp
std::pair<bool, NeededResources> res = canLevelUp(_evoBot.level);
bool canLevelUp = res.first;
```
- If it can perform an incantation, it will then call all the other EvoBots to perform the incantation. Next, it will check if the shared inventory of the EvoBots has enough resources. If not, it will calculate the most efficient slave bot to gather the missing resources.
```cpp
if (canLevelUp) {
    std::string message = "group";
    NeededResources remainingRequirements;
    std::pair<NeededResources, std::map<int, Ressources>> deposit = calculateAndPrintBotDeposits(evoBotInventory, _evoBot.level, res.second);
    remainingRequirements = deposit.first;
    std::map<int, Ressources> evoBotContributions = deposit.second;
    std::map<int, Ressources> botContributions = identifyEfficientBots(_evoBot.level, remainingRequirements);
} else {
    std::cout << "Les bots ne peuvent pas évoluer au niveau supérieur de manière efficace.\n";
}
```

- After the computation, the Forker will send a message to the AI's to indicate which bot need to set which ressources to perform an Incantation
```cpp
    std::string formattedBotContributions = formatBotContributions(botContributions, evoBotContributions);
```

Exemple of message sent by the Forker after computation : 

**10%linemate=1$1%deraumere=1$4%deraumere=1%sibur=3$5%phiras=1**

Here the Forker is calling the bot **10** to set 1 linemate, the bot **1** to set 1 deraumere, the bot **4** to set 1 deraumere and 3 sibur and the bot **5** to set 1 phiras.