---
sidebar_position: 0
---

Scenes in the renderer are like a page you could find on a website.

All scenes are derived from the `IScene` interface.\
Because of that they must implement 4 keys functions:
1. initialisation
```cpp
void init()
```
2. draw sequence
```cpp
void draw(sf::RenderWindow &window)
```
1. update based on the time for animations
```cpp
void update(float fElapsedTime)
```
1. update depending on events triggered
```cpp
bool update(sf::Event event, sf::RenderWindow &window)
```

The Scenes present on the zappy are the following:
- Home, where you can connect to a server and start the game
- Menu, which is called when *escape* is pressed
- World, the main display of the game

