# Zappy ai

## About the project

Our project includes two types of bots:
- **Forker**
- **SimpleBot**

Initially, these bots operated based on probabilities defined in a configuration file. We employed genetic algorithms to train the bots, optimizing their probabilistic behaviors for the best results. However, we couldn't finalize this approach.

Currently, our bots function based on predefined logic behaviors and can utilize patterns comprising sets of actions or simple directives.

## Build with
* [![cpp][cpp-img]](https://fr.wikipedia.org/wiki/C%2B%2B)
* [![python][python-img]](https://www.python.org/)

## Prerequisites

This project is made in cpp and python.
* gcc -> https://gcc.gnu.org/install/
* python -> https://www.python.org/downloads/

## Usage 👨‍💻
**Run theses commands at root of projets**
- Run server:
```sh
./zappy_ai -p port -n team -h address
```

- Run the graph for actions:
- Metris are saved when you run bot, you have to delete it (if exist) before rerunning a simulation.

- **filename** of bot you want to inspect in './src/ai/dataSaved/actions{teamNameBotId}.txt'
```sh
./src/ai/bonus/printActionsGraph.py
```

## Client

It is a basic client that will do the communication between the bots and the server.

## Documentation
- Click on the robot to see what we tried about ML [🤖](documentation/BOTSML.md)


## Authors
| [<img src="https://github.com/quentinbol.png?size=85" width=85><br><sub>Quentin Bolloré</sub>](https://github.com/quentinbol) | [<img src="https://github.com/tomkawohl.png?size=85" width=85><br><sub>Tom Kawohl</sub>](https://github.com/tomkawohl)
| :---: | :---: |

[cpp-img]:https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white
[python-img]:https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54