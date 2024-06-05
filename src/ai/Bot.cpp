/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Bot.cpp
*/
#include "Bot.hpp"

Bot::Bot(int sockfd, std::string teamName) : _sockfd(sockfd), _teamName(teamName), _messageId(0), _timeUnit(126), _iteration(0)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    sendMessage(teamName);
    state.ressources.food = 9;
    behaviors.push_back(std::make_unique<Behavior>(0.0, [&]()
                                                   { testPatern(); }, "testPatern"));
    behaviors.push_back(std::make_unique<Behavior>(0.0, [&]()
                                                   { testPatern2(); }, "testPatern2"));
    for (auto &behavior : behaviors)
    {
        behavior->probability = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }
    debugInitialisation();
}

// to verify: print it at end, it will with this that we will know which bot is better
Bot::~Bot()
{
    printColor("===== [Bot destruction] =====", RED);
    printColor("lvl: " + std::to_string(state.level), RED);
    printColor("food: " + std::to_string(state.ressources.food), RED);
    printColor("linemate: " + std::to_string(state.ressources.linemate), RED);
    printColor("deraumere: " + std::to_string(state.ressources.deraumere), RED);
    printColor("sibur: " + std::to_string(state.ressources.sibur), RED);
    printColor("mendiane: " + std::to_string(state.ressources.mendiane), RED);
    printColor("phiras: " + std::to_string(state.ressources.phiras), RED);
    printColor("thystame: " + std::to_string(state.ressources.thystame), RED);
    printColor("===== [!Bot destruction] =====", RED);
}

void Bot::sendMessage(const std::string &message)
{
    std::string messageToSend = message + "\n";

    send(_sockfd, messageToSend.c_str(), messageToSend.size(), 0);
}

void Bot::run(std::string response)
{
    if (!response.empty() && response.back() == '\n')
    {
        response.pop_back();
    }

    printColor("========== [Bot Run] ==========\n", BLUE);
    printKeyValueColored("Iteration", std::to_string(_iteration));
    printKeyValueColored("Bot listens", response);

    listen(response); // -> change le state
    if (actionsCount > 0)
        actionsCount--;
    if (state.reward != 0)
        applyReward();
    updateProbabilities();
    if (actionsCount == 0)
        act(); // -> fait l'action la plus rentable
    _iteration++;
}

/*
epsilon is chance to explore, max it to make a bot more ambitious (0.1 == 10 % chance to explore)
*/
// still depcrecated, it has to be modified on updateProbabilities. Will see how to do it.
void Bot::act()
{
    Behavior *bestBehavior = nullptr;
    float epsilon = 0.4;

    // Exploration
    if ((rand() / (float)RAND_MAX) < epsilon)
    {
        int randomIndex = rand() % behaviors.size();
        bestBehavior = behaviors[randomIndex].get();
        printKeyValueColored("Explore", bestBehavior->name);
    }
    else // Exploitation
    {
        int maxProbability = -1;

        for (auto &behavior : behaviors)
        {
            if (behavior->probability > maxProbability)
            {
                maxProbability = behavior->probability;
                bestBehavior = behavior.get();
            }
        }
        printKeyValueColored("Exploit", bestBehavior->name);
    }
    if (bestBehavior)
    {
        bestBehavior->act();
        state.lastBehaviors.push_back(std::make_unique<Behavior>(*bestBehavior));
    }
}

void Bot::listen(std::string response)
{
    if (state.lastAction.action == LOOK)
    {
        listenLookResponse(response);
    }
    else if (state.lastAction.action == FORK)
    {
        listenForkResponse(response);
    }
    else if (state.lastAction.action == TAKE)
    {
        listenTakeResponse(response);
    }
    else if (state.lastAction.action == FORWARD)
    {
        listenForwardResponse(response);
    }
}

void Bot::applyReward()
{
    double reward = state.reward;
    std::string rewardStr = "Reward: " + std::to_string(reward);

    printKeyValueColored("Reward", std::to_string(reward));
    for (auto &behavior : state.lastBehaviors)
    {
        auto it = std::find_if(behaviors.begin(), behaviors.end(), [&behavior](const std::unique_ptr<Behavior> &b)
                               { return b->name == behavior->name; });

        if (it != behaviors.end())
        {
            (*it)->probability += reward;
            if ((*it)->probability > 1)
                (*it)->probability = 1;
            else if ((*it)->probability < 0)
                (*it)->probability = 0;
        }
    }
    state.lastBehaviors.clear();
    state.reward = 0;
}

void Bot::takeFirstDecision(std::string response)
{
    int slot;
    int x; // to verify: we want to store that in bot ? behavior different if map is larger ?
    int y;

    std::string modifiedInput = response;
    std::replace(modifiedInput.begin(), modifiedInput.end(), '\n', ' ');
    std::istringstream iss(modifiedInput);
    iss >> slot >> x >> y;

    if (slot == 0)
        doAction(FORK, "");
    else
        doAction(LOOK, "");
}

void Bot::doAction(actions action, const std::string &parameter)
{
    ActionInfo actionInfo = getActionInfo(action);

    std::string finalAction = actionInfo.getName();

    if (parameter != "")
        finalAction += " " + parameter;
    printKeyValueColored("Bot does", finalAction);
    sendMessage(finalAction);
    state.lastAction.action = action;
    state.lastAction.parameter = parameter;
    _timeUnit -= actionInfo.getValue();
    if (_timeUnit % 126 == 0)
        state.ressources.food -= 1;
}

/* [ML] */
/* [AddObservation]
What bot will change
last behavior.probability

and

Botstate

will modify the last behavior.probability
*/

/* [Rewards]
An action occured
food * 0.1;
linemate * 0.2;
deraumere * 0.3;
reached a lvl = nb_lvl * 0.3

die = -1
get ko response ? (not sure)
*/