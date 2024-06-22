---
sidebar_position: 0
---

The GUI is separated into two main parts, the Parser and the Renderer.
The Parser take care of all communication with the server and store all information relative to the game in a Data structure.
The Renderer uses that Data structure and translate it into a graphical display using the SFML.

# The Parser
The parser is composed of 3 main component:
1. the connection to the server
2. the command parser
3. the storage of the data

### The connection to the server

the connection to the server is done by the C command `socket` and `connect`. Because those are C functions they are encapsulated in the `ServerConnect` class.

This class contain 4 functions: 
1. read everything sent by the server and return it as a string
```cpp
std::string readFromServer();
```
2. send a message to the server
```cpp
void sendToServer(std::string message);
```
3. initialyze a connection to the given ip and port
```cpp
void connectToServer(int port, const char *ip);
```
4. disconnect from the server (close the socket)
```cpp
bool disconectFromServer();
```

:::info
If you don't call `disconectFromServer` before exiting the destructor will take care of unclosed socket for you
:::

:::warning
All those functions throw an guiException if they doesn't work
:::

### The command parser

The command parser is separated into two main parts.

First it takes the output from `readFromServer` and transform it into a `stringStream` to read it line by line and look for the corresponding handler of each line.

When the handler is called it verifies each of the arguments given to the command and put the command in a queue.

Then when there is nothing left to parse it executes all the funtions in the queue.

:::info
if you want to know more about the handlers head to the "Adding new commands" page
:::

### Storage of the data

The `Data` class holds all the informations that the parser gets.

Here are all the variables it holds:
```cpp
int tickRate;
std::vector<std::string> teamNames;
std::map<int, Egg> eggs;
std::map<int, std::shared_ptr<Player>>players;
std::map<std::vector<int>,std::shared_ptr<Incantation>> incantations;
std::vector<Broadcast> broadcasts;
std::optional<std::string> winner;
Map map;
```

each of those function has a getter and a setter,
they are modified by the handlers of the `Parser` class.

:::info
If you want to know more about how to use that Data head to the "Manipulation the data" page"
:::

# The renderer

At the core of the renderer lies the `Core` class, it is used to make the link with the Parser side of the GUI and holds both the gameData and the renderData.

The renderer has a main loop that update both the display and the gameData.

Like a standard graphic implementation the main loop calls update for every component and then call draw for each of them.

the core also has 2 function to handle window size:
1. change the resolution
```cpp
void Core::newResolution(sf::Vector2f resolution)
```
2. swap to and from fullscreen
```cpp
void Core::switchFullscreen()
```

The core also store global variables such as the `deltaTime`, the `mousePosition` and the `gameState`.

All other aspect of the renderer will be explained in detail on their own page.

[Scenes documentation](/category/GUI/Renderer/Scenes).
[Sprites documentation](/category/GUI/Renderer/Sprites).
[Buttons & inputs documentation](/category/GUI/Renderer/).

