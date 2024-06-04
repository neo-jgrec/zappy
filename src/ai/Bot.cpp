/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Bot.cpp
*/
// to verify: test reward
//  Implementation of epsilon-greedy: Cette approche permet au bot de choisir aléatoirement une action
// avec une certaine probabilité (epsilon) afin d'explorer de nouvelles actions et comportements.
#include "Bot.hpp"

Bot::Bot(int sockfd, std::string teamName) : _sockfd(sockfd), _teamName(teamName), _messageId(0), _timeUnit(126)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    printColor("===== [Bot initiation] =====", GREEN);
    printColor("sockfd: " + std::to_string(_sockfd), YELLOW);
    printColor("teamName: " + _teamName, YELLOW);
    printColor("messageId: " + std::to_string(_messageId), YELLOW);
    printColor("timeUnit: " + std::to_string(_timeUnit), YELLOW);
    std::cout << std::endl;

    sendMessage(teamName);
    state.ressources.food = 9;
    behaviors.push_back(std::make_unique<Behavior>(0.0, [&]()
                                                   { testPatern(); }, "testPatern"));

    for (auto &behavior : behaviors)
    {
        behavior->probability = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }
    printColor("===== [!Bot initiation] =====", GREEN);
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

    printColor("Bot listens: " + response, GREEN);

    listen(response); // -> change le state
    if (actionsCount > 0)
        actionsCount--;
    // if (state.reward != 0)
    //   applyReward();
    updateProbabilities();
    if (actionsCount == 0)
        act(); // -> fait l'action la plus rentable
}

/*
epsilon is chance to explore, max it to make a bot more ambitious (0.1 == 10 % chance to explore)
*/
void Bot::act()
{
    Behavior *bestBehavior = nullptr;
    float epsilon = 0.4;

    // Exploration
    if ((rand() / (float)RAND_MAX) < epsilon)
    {
        int randomIndex = rand() % behaviors.size();
        bestBehavior = behaviors[randomIndex].get();
        printColor("behavior (random): " + bestBehavior->name, GREEN);
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
        printColor("behavior (best): " + bestBehavior->name, GREEN);
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

// depecrated
void Bot::applyReward()
{
    double reward = state.reward;
    std::string rewardStr = "Reward: " + std::to_string(reward);

    if (reward < 0)
        printColor(rewardStr, RED);
    else
        printColor(rewardStr, GREEN);
    std::cout << "----- [Behaviors] -----\n";
    for (auto &behavior : state.lastBehaviors)
    {
        auto it = std::find_if(behaviors.begin(), behaviors.end(), [&behavior](const std::unique_ptr<Behavior> &b)
                               { return b->name == behavior->name; });

        if (it != behaviors.end())
        {
            (*it)->probability += reward;
            std::cout << "behavior name: " << (*it)->name << " probability: " << (*it)->probability << std::endl;
            if ((*it)->probability > 1)
                (*it)->probability = 1;
            else if ((*it)->probability < 0)
                (*it)->probability = 0;
        }
    }
    std::cout << "----- [!Behaviors] -----\n";
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
        doAction(FORK, "", "");
    else
        doAction(LOOK, "", "");
}

// to verify: this action could only take a behavior in parameter ?
void Bot::doAction(actions action, const std::string &parameter, const std::string &behaviorName)
{
    ActionInfo actionInfo = getActionInfo(action);

    std::string finalAction = actionInfo.getName();

    if (parameter != "")
        finalAction += " " + parameter;
    printColor("Bot does: " + finalAction, YELLOW);
    sendMessage(finalAction);
    state.lastBehavior = behaviorName;
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