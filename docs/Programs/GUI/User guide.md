---
sidebar_position: 3
---

This is a section to understand as a user what's going on.

## Starting the GUI and connecting to the game server

How to launch the gui:
```bash
./zappy_gui
```

Once you have launched the gui you will be greated by that window:
![Home window](/img/home.png)

Here you can click on the input box to enter the host adress and the port.
![connection button](/img/connect_bt.png)

Once you entered both the ip and port you can go ahead and press start.

Two possibles scenarios can happen here:

Either you get an error message, that means that the server is likely not started or you entered a wrong adress / port.
image

Or there is no problem and you find yourself on a new window, the GAME WINDOW !
![game window](/img/game_window.png)

## Understanding the Interface

If we decompose the screen we can distinguish 4 main elements.

### The chat

At the bottom left of the screen you have the chat where every message is listed.
![Chat](/img/chat.png)

### The inventory bar

At the bottom center lies the inventory, it displays either the ressources of the tile or the trantorian selected.
![inventory](/img/inventory.png)

If we zoom on a ressource in the inventory we can see a number indicating how much of that ressource there is.
![ressource focus](/img/ressource.png)

From left to right the ressources are:
1. Linemate
2. Deraumere
3. Sibur
4. Mendiane
5. Phiras
6. Thystame
7. food

And the little man represent the number of trantorians on the tile
![trantorian incon](/img/trantorian_inv.png)

### The informations buttons

Now in the top left corner you have 4 nice little buttons to display all kinds of information, we will go over them one by one.

1. Team button
![team button](/img/team_bt.png)
The team button allows you to switch between each team, the first thing it does is displaying the name and score of the team.

And the second thing is that a little arrow is displayed over the head of every player from that team.
image

2. Player button
![Player button](/img/player_bt.png)

The player button allows you to switch between each player, it also display an arrow over the head of the player selected and display its inventory in the inventory bar. In addition it shows you what is the id of the player and which direction he is facing.

3. Score button
![Score button](/img/score_bt.png)




### The map

In the center of the screen you find the map.
![Map](/img/map.png)

The trees and little rocks are here purely for aesthetics.
![Tree](/img/tree.png)

Crops circles on the other hand, represents spawn point for a new player.
![eggs](/img/egg.png)

Trantorians are represented as little orange things and are taken by ufos when they die.
![trantorian](/img/trantorian.png)

To navigate the map you can hold left click to move the map and use your scroll-weel to control the zoom.

## The menu

To access the menu press the `escape` key. 

While in the menu you can choose between 3 resolutions and to be in fullscreen mode or not.
![fullscreen button](/img/fullscreen.png)

You can also choose to quit the game or go to the home page by pressing the corresponding button.
![quit button](/img/home_bt.png)

And you can change the speed at which the game goes.
![Rate button](/img/rate.png)

