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
        int _highestLevel;
        int _score;
        std::string _teamName;

        static void sortRanking(std::vector<Ranking> &ranking) {
            std::sort(ranking.begin(), ranking.end(), [](Ranking &a, Ranking &b) {
                if (a._score == b._score) {
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
            _nbPlayer = 0;
            _highestLevel = 0;
            _score = 0;
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
