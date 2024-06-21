/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Ranking
*/

#ifndef RANKING_HPP_
#define RANKING_HPP_

#include "../../../../parser/Data.hpp"

class Ranking {
    public:
        int _nbPlayer;
        int _nbEgg;
        int _highestLevel;
        int _score;
        std::string _teamName;

        static void sortRanking(std::vector<Ranking> &ranking) {
            std::sort(ranking.begin(), ranking.end(), [](Ranking &a, Ranking &b) {
                if (a._score == b._score) {
                    if (a._highestLevel == b._highestLevel) {
                        if (a._nbEgg == b._nbEgg) {
                            return a._nbPlayer > b._nbPlayer;
                        }
                        return a._nbEgg > b._nbEgg;
                    }
                    return a._highestLevel > b._highestLevel;
                }
                return a._score > b._score;
            });
        }

        static void getRanking(std::vector<Ranking> &ranking, Data &data) {
            ranking.clear();
            auto teams = data.getTeams();
            for (auto &team : teams) {
                Ranking rank;
                rank._teamName = team;
                rank.getRanking(data);
                ranking.push_back(rank);
            }
            sortRanking(ranking);
        }

        void getRanking(Data &data) {
            _nbEgg = 0;
            _nbPlayer = 0;
            _highestLevel = 0;
            _score = 0;
            auto eggs = data.getEggs();
            for (auto &egg : eggs) {
                if (egg.second.getState() == EggStatus::READY_TO_HATCH)
                    _nbEgg++;
            }
            auto players = data.getPlayers();
            for (auto &player : players) {
                if (player.second->getAlive() == false)
                    continue;
                if (player.second->getTeam() == _teamName) {
                    _nbPlayer++;
                    _score += player.second->getLvl() * 15;
                    _score += 10;
                    if (player.second->getLvl() > _highestLevel)
                        _highestLevel = player.second->getLvl();
                }
            }

        }
};

#endif /* !RANKING_HPP_ */
