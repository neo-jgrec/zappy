---
sidebar_position: 1
---

As it was said before the GUI is divided into two parts the Parser and the Render.
This page will guide you on how to use all the information of the Parser in the Render.

To use the gameData three things are needed:
1. connecting to the server
2. updating the data
3. accessing the data

:::warning
Before trying to make a Render process yourself you should understand the Core class
:::

## Connecting to the server

To connect to a server you need to use the member funtion `connectToServer(int port, const char *ip)` of the `ServerConnect` class.

:::info
The ServerConnect class contain a ip and port public variable for you to use
:::

`connectToServer` can throw in two situations:
1. if the ip given is invalid
2. if the call to connect fails

In both cases it throws a guiException.

## Updating the data

Before using the data you must make sure that the data is up to date.\
The function you want to use for that is the `updateData` member function of the `Parser` class.

```cpp
Parser parser;
parser.updateData(gameData, server)
```

This function does nothing if no data is available to read so don't hesitate to call it each frame to make sure your data is up to date.

:::info
You must feed the function a ServerConnect that is already connected to a server or else it will throw
:::

## Accesing the data

Now that your data is initialized and up to date you just need to look at the Data.cpp header to know all the getters you have access to.

for example if you want the size of the map, you first call the getMap member function of the Data class, and then the getSize memeber function of the Map class.

```cpp
Data gameData;
Map gameMap = gameData.getMap();
std::vector<int> size = gameMap.getSize();
```

:::warning
The example above doesn't take into account the initialisation of the data or the connection to the server, it only serve as an example of usage of the Data class
:::