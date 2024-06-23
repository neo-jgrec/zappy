# Zappi AI Documentation

## Scope
If you want to develop your own bots, this is the place.

You can create your classes derived from:
- <span style="color: yellow;">**IBot:**</span> Interface for bots. You have to code all the logic.
- <span style="color: yellow;">**ABot:**</span>Use [Actions](#actions), [State](#state), [Listeners](#listeners) you have to code the initialisation and run logic.
- <span style="color: green;">**ABotPattern:**</span> Use [Pattern](#patterns), you have to code only the bot logic based on patterns and actions.

IBot => ABot => ABotPattern

[Click to know how to code on projet or for information](#code-on-project)

## Actions
Look at Action.hpp to see availables actions.
An action has a name, an optionnal parameter, a time unit cost.
For example:
- Forward - no parameter - 7 time unit cost
- Broadcast - message - 7 time unit cost
For example:
```c++
doAction(TAKE, "food");
```

# Patterns
Look at Pattern.hpp.
Patterns are set of actions.
We push actions to a queue that will execute actions in order.
For example:
```c++
void ABotPattern::testPatern()
{
    queue.push_back({[&]()
                     { doAction(LOOK, ""); }, "LOOK"});
    queue.push_back({[&]()
                     { doAction(FORWARD, ""); }, "FORWARD"});
    queue.push_back({[&]()
                     { doAction(TAKE, "food"); }, "TAKE"});
    queue.push_back({[&]()
                     { doAction(RIGHT, ""); }, "RIGHT"});
}
```

## State
Look at BotState.hpp
We store datas about bots in a state.
- State of bot (Standard, INCANTATING, ...)
- Environment (Ressources in his environments)
- Last action
- Level
- Slot available
- Map size

## Listeners
When bot do an action, it will listen the response of the server.
Then, we update the state.

## Code on project (ABotPattern)

# Logic
Bot update his strategy based on his state.
State are updated when bot listen to the servers via listeners.
You can add state modifications and listeners.

1. Work on project<br>
git clone the project, git checkout feat/ia. Do Pull Request when you want to add your work.

2. Create your class deriving from ABotPattern:<br>
This class muse have:
    - initChild: if you need to init configuration about your bot
    - updateStrategy: contains your bot logic

```c++
class SimpleBot : public ABotPattern
{
public:
    void initChild();
    void updateStrategy() override;
};
```

3. Init your bot<br>
It is if you use new variables for your bot.
If not, just print that your bot is well initialized.

```c++
void SimpleBot::initChild()
{
    std::cout << "🧒✅ SimpleBot initialized" << std::endl;
}
```

4. Do your logic<br>
Based on the bot state, you can use strategies.
It verify a condition => do pattern

This bot does:
- Will survive if he has not enough food
- Will take linemate if he is lvl 1 and has no linemate
- Will Incant to lvl 2if he has ressources

```c++
void SimpleBot::updateStrategy()
{
    if (_state.ressources.food < 5)
        survive();
    else if (_state.level == 1 && _state.ressources.linemate != 1)
        searchAndTakeRessource("linemate");
    else if (_state.ressources.linemate == 1 && _state.level == 1)
        incantationLvl1();
}
```

[OPTIONNAL]<br>
5. Add pattern ./src/ai/src/run/patterns<br>
To add a pattern, add actions to the queue, update the state if needed. You can add conditions in patterns too.
For example:
**IncantationLvl1**
```c++
void ABotPattern::incantationLvl1()
{
    queue.push_back({[&]()
                     { doAction(SET, "linemate"); }, "SET"});
    _state.ressources.linemate--;
    queue.push_back({[&]()
                     { doAction(INCANTATION, ""); }, "INCANTATION"});
}
```

6. Add listeners ./src/ai/src/run/listeners<br>
You can add listeners for actions.
Add it too to ABotPattern::listen
For example:
```c++
void ABot::listenConnectNbrResponse(const std::string &response)
{
    try
    {
        _state.slot = std::stoi(response);
    }
    catch (std::invalid_argument &e)
    {
        PRINT_ERROR("Invalid argument error: " << e.what());
    }
    catch (std::out_of_range &e)
    {
        PRINT_ERROR("Out of range error: " << e.what());
    }
}
```

7. Use message:<br>
We encrypt and sign message, if you want to send a message, you have to format it first.<br>
Don't use <span style="color: red;">{"ok", "ko", "dead", "[", "]", "Elevation underway", "Current level:", ",", ":"}</span> in your message
We separate response and broadcast messages.
```c++
std::string myMsg = "hello";

addBroadcastAction(myMsg);
```
