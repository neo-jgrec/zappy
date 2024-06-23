---
sidebar_position: 2
---

To set up the server, follow these steps:

Compile the Server Code: Ensure you have a C compiler installed and the **make** command. Use the following command to compile the server code:
```sh
make zappy_server
```

- **Server Configuration**: The server can be configured using command-line arguments or configuration files, if applicable. Refer to the specific server implementation details for configuration options.

**Run the Server**: Execute the compiled server program:
```sh
./zappy_server -p 3000 -x 10 -y 10 -n team1 team2 -c 3 -f 2
```
### Parameters Explanation

- **-p PORT**: Specifies the port number on which the server will listen for incoming connections. In this example, the server will listen on port **3000**.

- **-x WIDTH**: Sets the width of the game world or grid. Here, the width is set to **10**.

- **-y HEIGHT**: Sets the height of the game world or grid. Here, the height is set to **10**.

- **-n TEAM_NAMES**: Defines the names of the teams that will participate in the game. This parameter is followed by a list of team names. In this example, there are two teams: **team1** and **team2**.

- **-c MAX_CAPACITY**: Specifies the maximum number of players that can be in a team. Here, the maximum capacity is **3**.

- **-f FREQUENCY**: Sets the frequency of the game, which might control the speed of game ticks or updates. The default value is **100**, but in this example, it is set to **2**.
