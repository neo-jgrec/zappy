---
title: Zappy
sidebar_position: 1
slug: /
---

# ZAPPY: A Tribute to Zaphod Beeblebrox

Welcome to **ZAPPY**, a network-based game where teams compete on a dynamic tile map rich with resources. Our project celebrates the whimsical and adventurous spirit of Zaphod Beeblebrox from *The Hitchhiker's Guide to the Galaxy*. Let's embark on an intergalactic journey together! 🚀

## 📋 Introduction

### Project Overview
**ZAPPY** is a multiplayer game set in the world of **Trantor**. Teams of players will navigate this world, gathering resources, feeding themselves, and ultimately trying to elevate their status by performing specific rituals. The first team to have six players reach the maximum elevation level wins the game.

### Components
The project comprises three main components:
1. **Server (`zappy_server`)**: Manages the game world, resources, and player actions.
2. **Graphical Client (`zappy_gui`)**: Provides a visual representation of the game world.
3. **AI Client (`zappy_ai`)**: Controls a player autonomously, making strategic decisions to help their team.

### Language and Tools
- **Server**: Written in C
- **GUI**: Written in C++
- **AI**: Written in C++
- **Makefile**: Compiles `zappy_server`, `zappy_gui`, and `zappy_ai`

## 🌍 The World of Trantor

### Lore
**Trantor** is a world of zero-relief planes with no craters, valleys, or mountains. The map loops in all directions, creating a continuous, spherical world. Players navigate this world to collect resources and achieve their goals.

### Resources
Trantor is rich in both mineral and dietary resources. Players will find:
- **Food**
- **Natural Stones**: Linemate, Deraumere, Sibur, Mendiane, Phiras, and Thystame

### Elevation Ritual
Elevation is a crucial aspect of the game. Players gather specific stones and perform rituals to elevate their status. Each elevation increases their abilities and vision, bringing them closer to victory.

## 🛠️ Getting Started

### Running the Binaries
**Server**:
```
./zappy_server -p port -x width -y height -n team1 team2 ... -c clientsNb -f freq
```

**Graphical Client**:
```
./zappy_gui -p port -h machine
```

**AI Client**:
```
./zappy_ai -p port -n team_name -h machine
```

### Usage Tips
- Ensure all binaries are correctly compiled using the provided Makefile.
- Customize the game settings via command-line arguments to fit your preferred gameplay experience.

## 🎨 Graphical User Interface

The graphical client provides a 2D visualization of the game world, allowing you to watch the action unfold in real-time. Using **SFML** for the 2D interface is highly recommended due to its ease of use and functionality.

## 🚀 Ready to Play?

Dive into the world of Trantor, gather resources, elevate your players, and lead your team to victory! Stay tuned for detailed pages on gameplay mechanics, commands, and strategies.

![Zappy](https://example.com/zappy_image.png)

May the best team win! 🏆

---

For more detailed information on gameplay mechanics and commands, please refer to the respective sections on our documentation.

:::note
The project also includes unit tests, and so coverage, you can find them [here](/coverage).
:::
