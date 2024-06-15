# Zappy Server

A server, created in C, that generates the inhabitants’ world.

## Usage

```sh
USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq --auto-start on|off --display-eggs true|false [-v | --verbose]
	port		is the port number
	width		is the width of the world
	height		is the height of the world
	nameX		is the name of the team X
	clientsNb	is the number of authorized clients per team
	freq		is the reciprocal of time unit for execution of actions
	auto-start	does the greeting is send automaticly #(see bonus part)
	display-eggs	eggs are visible and destructible
```


The server is executed in the form of one, single process and one, single thread.
It must use select to handle socket multiplexing; the select must unlock only if something happen on a
socket or if an event is ready to be executed.


> The team name GRAPHIC is reserved for the GUI to authenticate itself as such to the server.


## AI protocol

Each player responds to the following actions and only to these ones, with the following syntax :

|            Action            |       Command      | Time limit |                 Response                 |
|:----------------------------:|:------------------:|:----------:|:----------------------------------------:|
|       move up one tile       |     __Forward__    |     7/f    |                    ok                    |
|        turn 90° right        |      __Right__     |     7/f    |                    ok                    |
|         turn 90° left        |      __Left__      |     7/f    |                    ok                    |
|          look around         |      __Look__      |     7/f    |            [tile1, tile2,...]            |
|           inventory          |    __Inventory__   |     1/f    |        [linemate n, sibur n, ...]        |
|        broadcast text        | __Broadcast text__ |     7/f    |                    ok                    |
|  number of team unused slots |   __Connect_nbr__  |      -     |                   value                  |
|         fork a player        |      __Fork__      |    42/f    |                    ok                    |
| eject players from this tile |      __Eject__     |     7/f    |                   ok/ko                  |
|       death of a player      |         _-_        |      -     |                   dead                   |
|         fork a player        |      __Fork__      |    42/f    |                    ok                    |
|          take object         |   __Take object__  |     7/f    |                   ok/ko                  |
|        set object down       |   __Set object__   |     7/f    |                   ok/ko                  |
|       start incantation      |   __Incantation__  |    300/f   | Elevation underway | Current level: k/ko |


> In case of a bad/unknown command, the server must answer “ko”.


The AI client’s connection to the server happens as follows:

    1. the client opens a socket on the server’s port,

    2. the server and the client communicate the following way:
        Server --> WELCOME\n
               <-- TEAM-NAME\n
               --> game informations (see tha above array)

X and Y indicate the world’s dimensions.

CLIENT-NUM indicates the number of slots available on the server for the TEAM-NAME team. If this number is greater than or equal to 1, a new client can connect.

> The client can send up to 10 requests in a row without any response from the server. Over 10, the server will drop the incomming commands.

The server executes the client’s requests in the order they were received.

The requests are buffered and a command’s execution time only blocks the player in question.

Trantorians have adopted an international time unit.
The time unit is seconds.

An action’s execution time is calculated with the following formula:

action / f

Where f is an integer representing the reciprocal (multiplicative inverse) of time unit.

For instance, if f=1, “forward” takes 7 / 1 = 7 seconds.

By default f=100.


## GUI protocol


| SYMBOL |               MEANING               |
|:------:|:-----------------------------------:|
|    X   |     width or horizontal position    |
|    Y   |     height or vertical position     |
|   q0   |      resource 0 (food) quantity     |
|   q1   |    resource 1 (linemate) quantity   |
|   q2   |   resource 2 (deraumere) quantity   |
|   q3   |     resource 3 (sibur) quantity     |
|   q4   |    resource 4 (mendiane) quantity   |
|   q5   |     resource 5 (phiras) quantity    |
|   q6   |    resource 6 (thystame) quantity   |
|    n   |            player number            |
|    O   | orientation: 1(N), 2(E), 3(S), 4(W) |
|    L   |     player or incantation level     |
|    e   |              egg number             |
|    T   |              time unit              |
|    N   |           name of the team          |
|    R   |          incantation result         |
|    M   |               message               |
|    i   |           resource number           |

<br>

|                   SERVER                   |   CLIENT  |                    DETAILS                    |    TO A GUI client    |    TO ALL GUI client    |
|:------------------------------------------:|:---------:|:---------------------------------------------:|:---------------------:|:-----------------------:|
|                  msz X Y\n                 |   msz\n   |                   map size                    | new GUI client connection or msz command | |
|       bct X Y q0 q1 q2 q3 q4 q5 q6\n       | bct X Y\n |               content of a tile               | bct command | |
| bct X Y q0 q1 q2 q3 q4 q5 q6\n * nbr_tiles |   mct\n   |       content of the map (all the tiles)      | new GUI client connection or mct command or map refill | |
|             tna N\n * nbr_teams            |   tna\n   |             name of all the teams             | new GUI client connection | |
|             pnw #n X Y O L N\n             |           |           connection of a new player          | new GUI client connection | new AI client connection |
|                ppo n X Y O\n               |  ppo #n\n |               player’s position               | ppo command | AI left, right forward action or AI is ejected |
|                  plv n L\n                 |  plv #n\n |                 player’s level                | new GUI client connection or plv command | AI sucessfully incantate |
|      pin n X Y q0 q1 q2 q3 q4 q5 q6\n      |  pin #n\n |               player’s inventory              | new GUI client connection or pin command | new AI client connection or AI set, take action or AI lost food |
|                   pex n\n                  |           |                   expulsion                   | | AI eject action |
|                  pbc n M\n                 |           |                   broadcast                   | | AI broadcast action |
|             pic X Y L n n ...\n            |           | start of an incantation (by the first player) | | AI incantation action |
|                 pie X Y R\n                |           |             end of an incantation             | | AI incatation end |
|                   pfk n\n                  |           |            egg laying by the player           | | AI fork action |
|                  pdr n i\n                 |           |               resource dropping               | | AI set action |
|                  pgt n i\n                 |           |              resource collecting              | | AI take action |
|                   pdi n\n                  |           |               death of a player               | | AI client disconnection or AI lost all it's food |
|                enw e n X Y\n               |           |          an egg was laid by a player          | new GUI client connection | AI fork action end (after 42/f) |
|                   ebo e\n                  |           |          player connection for an egg         | | new AI client connection |
|                   edi e\n                  |           |                death of an egg                | | egg is ejected by an AI |
|                   sgt T\n                  |   sgt\n   |               time unit request               | new GUI client connection or sgt | sst command |
|                   sst T\n                  |  sst T\n  |             time unit modification            | | |
|                   seg N\n                  |           |                  end of game                  | | an AI team reach the victory conditions |
|                   smg M\n                  |           |            message from the server            | | server send a message |
|                    suc\n                   |           |                unknown command                | | empty or unknown command |
|                    sbp\n                   |           |               command parameter               | | invalide command (wrong parameter.s) |
|                   eht e\n                  |           |                 egg is mature                 | new GUI client connection | server create an egg or egg create by an AI become mature |

<br>

The GUI client’s connection to the server happens as follows:

    1. the client opens a socket on the server’s port,

    2. the server and the client communicate the following way:
        Server --> WELCOME\n
               <-- GRAPHIC\n
               --> game informations (see the above array)


## Informations


### Incantations


This ritual, which augments physical and mental capacities, must be done according to a particular rite: they
must gather the following on the same unit of terrain:

- At least a certain number of each stones
- At least a certain number of players with the same level

The elevation begins as soon as a player initiates the incantation.
The player who starts an incantation will receive ko if all the requirements are not satisfied and the incantation will be canceled, the player will receive the ko instantly after the initial server check (not at the end of the incantation duration).

 which means that it will make the next action received by the server.

It is not necessary for the players to be on the same team; they only need to be of the same level.
Every player with the corresponding level and present at the beginning and at the end of the incantation attain the higher level.

During the incantation, the participants can not make any action until the end of the rite.

At the end of the incantation, the exact quantity of resources needed by the rite are consumed.


## Bonus


### Server commands


The server accepts command in its standard input.


|     Command    |           Effect           |
|:--------------:|:--------------------------:|
|    /clients    | list all connected clients |
|      /quit     |       stop the server      |
|  /send_ais msg |   send messages to all AI  |
| /send_guis msg |  send messages to all GUI  |
|      /map      |  display map informations  |
|     /clear     |       clear the shell      |
|     /pause     |   pause the AI's actions   |
|     /start     |      start the server      |
| /setTile ressource quantity x y | set the given ressource quantity of a tile |
| /tile x y | get the inventory of a tile |
| /tp id x y | tp an AI by it's id |
| /kill id | kill an AI by it's id |
| /noFood true or false | deactivate the food management |
| /broadcast "message" x y | simulate a broadcast |
| /setLevel id level | set the level of an AI by it's id |
| /setInventory id ressource quantity | set the given ressource quantity inside an AI inventory by it's id |
| /setClientsNb nb | set the minimum number of AI per team |
| /setFreq freq | set the frequency of the server |
| /noRefill true or false | deactivate the map refill |
| /fork team x y | simulate a fork for the given team at the given position |
| /incantate x y | simulate an incantation of the given level at the given position |
