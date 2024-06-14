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
    _orientation = NORTH;
    state.ressources.food = 9;
    behaviors.push_back(std::make_unique<Behavior>(0.4, [&]()
                                                   { survive(); }, "survive"));
    behaviors.push_back(std::make_unique<Behavior>(0.75, [&]()
                                                   { searchLinemate(); }, "searchLinemate"));
    // behaviors.push_back(std::make_unique<Behavior>(0.15, [&]()
    //                                                { searchDeraumere(); }, "searchDeraumere"));
    // behaviors.push_back(std::make_unique<Behavior>(0.15, [&]()
    //                                                { searchSibur(); }, "searchSibur"));
    // behaviors.push_back(std::make_unique<Behavior>(0.15, [&]()
    //                                                { searchMendiane(); }, "searchMendiane"));
    // behaviors.push_back(std::make_unique<Behavior>(0.15, [&]()
    //                                                { searchPhiras(); }, "searchPhiras"));
    // behaviors.push_back(std::make_unique<Behavior>(0.15, [&]()
    //                                                { searchThystame(); }, "searchThystame"));
    for (auto &behavior : behaviors)
    {
        behavior->probability = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }
    debugInitialisation();
    /* probabilities */
    probabilities.push_back(std::make_unique<Probability>(5, 0.4, "food_importance"));
    probabilities.push_back(std::make_unique<Probability>(5, 0.3, "linemate_importance"));
    // probabilities.push_back(std::make_unique<Probability>(5, 0.3, "deraumere_importance"));
    // probabilities.push_back(std::make_unique<Probability>(5, 0.3, "sibur_importance"));
    // probabilities.push_back(std::make_unique<Probability>(5, 0.3, "mendiane_importance"));
    // probabilities.push_back(std::make_unique<Probability>(5, 0.3, "phiras_importance"));
    // probabilities.push_back(std::make_unique<Probability>(5, 0.3, "thystame_importance"));
    debugProbabilities();
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
    int cycle = 0;
    printColor("========== [Bot Run] ==========\n", BLUE);
    printKeyValueColored("Iteration", std::to_string(_iteration));

    if (!response.empty() && response.back() == '\n')
    {
        response.pop_back();
    }

    if (state.lastAction.action == LOOK)
    {
        printKeyValueColored("Bot listens", response);
        if (response.find("message") != std::string::npos)
            doNothing = true;
        listen(response);
    }
    setRewardWithState();
    if (state.reward != 0)
        applyReward();
    if (state.reward != 0 || _iteration == 0)
        updateProbabilities();
    if (queue.empty())
        act(); // -> fait l'action la plus rentable
    if (!queue.empty() && !doNothing)
    {
        queue.front().first();
        queue.erase(queue.begin());
    }
    _iteration++;
    printColor("========== [!Bot Run] ==========\n", BLUE);
}

/*
epsilon is chance to explore, max it to make a bot more ambitious (0.1 == 10 % chance to explore)
*/
// depecrated epsilon greedy should not be there
void Bot::act()
{
    exploreProbabilities();
    Behavior *bestBehavior = nullptr;

    double maxProbability = -1;

    if (!behaviors.empty())
    {
        maxProbability = behaviors.front()->probability;

        bestBehavior = behaviors.front().get();
    }
    else
    {
        return;
    }

    for (auto &behavior : behaviors)
    {
        if (behavior->probability > maxProbability)
        {
            maxProbability = behavior->probability;
            bestBehavior = behavior.get();
        }
    }
    printColor("Behavior choosen: " + bestBehavior->name + "\n", BOLD);
    if (bestBehavior)
    {
        bestBehavior->act();
    }
}

std::string getElementAfterComma(const std::string& input)
{
    std::istringstream iss(input);
    std::string token;
    
    while (std::getline(iss, token, ',')) {
        // Après la virgule, récupérer le token suivant
        if (iss >> token) {
            return token;
        }
    }

    return ""; // Retourner une chaîne vide si la virgule n'est pas trouvée
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
        printf("TAKE\n");
        listenTakeResponse(response);
    }
    else if (state.lastAction.action == FORWARD)
    {
        printf("FORWARD\n");
        listenForwardResponse(response);
    }
    if (response.find("message") != std::string::npos)
    {
        std::string message = getElementAfterComma(response);
        _message._content = message;
        _message.vigenereDecrypt();
        printKeyValueColored("Message", _message._content);
    }
}

void Bot::applyReward()
{
    double reward = state.reward;

    printColor("========== [Bot Probabilities] ==========\n", CYAN);
    printKeyValueColored("Reward", std::to_string(reward));

    for (auto &probability : probabilities)
    {
        if (std::find(state.exploredProbabilities.begin(), state.exploredProbabilities.end(), probability->name) != state.exploredProbabilities.end())
        {
            probability->probability += reward;

            // Clamp the probability values between 0 and 1
            if (probability->probability > 1)
                probability->probability = 1;
            else if (probability->probability < 0)
                probability->probability = 0;
        }
    }

    state.reward = 0;
    debugProbabilities();
    printColor("========== [!Bot Probabilities] ==========\n", CYAN);
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

// Landmark: should do exploring probability after a reward!
