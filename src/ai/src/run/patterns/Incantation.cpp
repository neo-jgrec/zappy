/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Incantation.cpp
*/

#include "../../bots/ABotPattern.hpp"
// Landmark: fix meeting_id_group_done
void ABotPattern::warnsWillIncant()
{
    std::string willIncant = "warns_will_incant_" + _state.metadata["id_group"];
    addBroadcastAction(willIncant);
}

void ABotPattern::incantationLvl1()
{
    queue.push_back({[&]()
                     { doAction(SET, "linemate"); }, "SET"});
    _state.ressources.linemate--;
    queue.push_back({[&]()
                     { doAction(INCANTATION, ""); }, "INCANTATION"});
}

void ABotPattern::incantationLvl2()
{
    queue.push_back({[&]()
                     { doAction(SET, "linemate"); }, "SET"});
    _state.ressources.linemate--;
    queue.push_back({[&]()
                     { doAction(SET, "deraumere"); }, "SET"});
    _state.ressources.deraumere--;
    queue.push_back({[&]()
                     { doAction(SET, "sibur"); }, "SET"});
    _state.ressources.sibur--;
    warnsWillIncant();
    queue.push_back({[&]()
                     { doAction(INCANTATION, ""); }, "INCANTATION"});
    _state.metadata["should_incant"] = "false";
}

void ABotPattern::incantationLvl3()
{
    queue.push_back({[&]()
                     { doAction(SET, "linemate"); }, "SET"});
    _state.ressources.linemate--;
    queue.push_back({[&]()
                     { doAction(SET, "linemate"); }, "SET"});
    _state.ressources.linemate--;
    queue.push_back({[&]()
                     { doAction(SET, "sibur"); }, "SET"});
    _state.ressources.sibur--;
    queue.push_back({[&]()
                     { doAction(SET, "phiras"); }, "SET"});
    _state.ressources.phiras--;
    queue.push_back({[&]()
                     { doAction(SET, "phiras"); }, "SET"});
    _state.ressources.phiras--;
    warnsWillIncant();
    queue.push_back({[&]()
                     { doAction(INCANTATION, ""); }, "INCANTATION"});
    _state.metadata["should_incant"] = "false";
}

void ABotPattern::incantationLvl4()
{
    queue.push_back({[&]()
                     { doAction(SET, "linemate"); }, "SET"});
    _state.ressources.linemate--;
    queue.push_back({[&]()
                     { doAction(SET, "deraumere"); }, "SET"});
    _state.ressources.deraumere--;
    queue.push_back({[&]()
                     { doAction(SET, "sibur"); }, "SET"});
    _state.ressources.sibur--;
    queue.push_back({[&]()
                     { doAction(SET, "sibur"); }, "SET"});
    _state.ressources.sibur--;
    queue.push_back({[&]()
                     { doAction(SET, "phiras"); }, "SET"});
    _state.ressources.phiras--;
    warnsWillIncant();
    queue.push_back({[&]()
                     { doAction(INCANTATION, ""); }, "INCANTATION"});
    _state.metadata["should_incant"] = "false";
}

void ABotPattern::incantationLvl5()
{
    queue.push_back({[&]()
                     { doAction(SET, "linemate"); }, "SET"});
    _state.ressources.linemate--;
    queue.push_back({[&]()
                     { doAction(SET, "deraumere"); }, "SET"});
    _state.ressources.deraumere--;
    queue.push_back({[&]()
                     { doAction(SET, "deraumere"); }, "SET"});
    _state.ressources.deraumere--;
    queue.push_back({[&]()
                     { doAction(SET, "sibur"); }, "SET"});
    _state.ressources.sibur--;
    queue.push_back({[&]()
                     { doAction(SET, "mendiane"); }, "SET"});
    _state.ressources.mendiane--;
    queue.push_back({[&]()
                     { doAction(SET, "mendiane"); }, "SET"});
    _state.ressources.mendiane--;
    queue.push_back({[&]()
                     { doAction(SET, "mendiane"); }, "SET"});
    _state.ressources.mendiane--;
    warnsWillIncant();
    queue.push_back({[&]()
                     { doAction(INCANTATION, ""); }, "INCANTATION"});
    _state.metadata["should_incant"] = "false";
}

void ABotPattern::incantationLvl6()
{
    queue.push_back({[&]()
                     { doAction(SET, "linemate"); }, "SET"});
    _state.ressources.linemate--;
    queue.push_back({[&]()
                     { doAction(SET, "deraumere"); }, "SET"});
    _state.ressources.deraumere--;
    queue.push_back({[&]()
                     { doAction(SET, "deraumere"); }, "SET"});
    _state.ressources.deraumere--;
    queue.push_back({[&]()
                     { doAction(SET, "sibur"); }, "SET"});
    _state.ressources.sibur--;
    queue.push_back({[&]()
                     { doAction(SET, "sibur"); }, "SET"});
    _state.ressources.sibur--;
    queue.push_back({[&]()
                     { doAction(SET, "sibur"); }, "SET"});
    _state.ressources.sibur--;
    queue.push_back({[&]()
                     { doAction(SET, "phiras"); }, "SET"});
    _state.ressources.phiras--;
    warnsWillIncant();
    queue.push_back({[&]()
                     { doAction(INCANTATION, ""); }, "INCANTATION"});
    _state.metadata["should_incant"] = "false";
}

void ABotPattern::incantationLvl7()
{
    queue.push_back({[&]()
                     { doAction(SET, "linemate"); }, "SET"});
    _state.ressources.linemate--;
    queue.push_back({[&]()
                     { doAction(SET, "linemate"); }, "SET"});
    _state.ressources.linemate--;
    queue.push_back({[&]()
                     { doAction(SET, "deraumere"); }, "SET"});
    _state.ressources.deraumere--;
    queue.push_back({[&]()
                     { doAction(SET, "deraumere"); }, "SET"});
    _state.ressources.deraumere--;
    queue.push_back({[&]()
                     { doAction(SET, "sibur"); }, "SET"});
    _state.ressources.sibur--;
    queue.push_back({[&]()
                     { doAction(SET, "sibur"); }, "SET"});
    _state.ressources.sibur--;
    queue.push_back({[&]()
                     { doAction(SET, "mendiane"); }, "SET"});
    _state.ressources.mendiane--;
    queue.push_back({[&]()
                     { doAction(SET, "mendiane"); }, "SET"});
    _state.ressources.mendiane--;
    queue.push_back({[&]()
                     { doAction(SET, "phiras"); }, "SET"});
    _state.ressources.phiras--;
    queue.push_back({[&]()
                     { doAction(SET, "phiras"); }, "SET"});
    _state.ressources.phiras--;
    queue.push_back({[&]()
                     { doAction(SET, "thystame"); }, "SET"});
    _state.ressources.thystame--;
    warnsWillIncant();
    queue.push_back({[&]()
                     { doAction(INCANTATION, ""); }, "INCANTATION"});
    _state.metadata["should_incant"] = "false";
}

// TODO: Fix this i guess. objStr is empty
void ABotPattern::incantation(std::vector<std::string> objs)
{
    for (auto &obj : objs)
    {
        std::string objStr = obj;

        queue.push_back({[&]()
                         { doAction(SET, objStr); }, "SET"});
        if (obj == "linemate")
            _state.ressources.linemate--;
    }
    warnsWillIncant();
    queue.push_back({[&]()
                     { doAction(INCANTATION, ""); }, "INCANTATION"});
}
