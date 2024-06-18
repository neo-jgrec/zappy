---
sidebar_position: -3
---

A server, written in C, that generates the inhabitants’ world.
A graphical client, written in C++, that can be used to watch what happens in the world.
A client, with no language constraint, that drives an inhabitant through orders sent to the server.

:::info
We chose to use the C++ language for the client (ia).
:::

### Server
```
$> ./zappy_server -help
USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq
```

| Option | Description |
|--------|-------------|
| -p port | Port number |
| -x width | Width of the world |
| -y height | Height of the world |
| -n name1 name2 ... | Name of the team |
| -c clientsNb | Number of authorized clients per team |
| -f freq | Reciprocal of time unit for execution of actions |

### Clients

#### Graphical Client
```
$> ./zappy_gui -help
USAGE: ./zappy_gui -p port -h machine
```

| Option | Description |
|--------|-------------|
| -p port | Port number |
| -h machine | Hostname |


#### AI Client
```
$> ./zappy_ai -help
USAGE: ./zappy_ai -p port -n name -h machine
```

| Option | Description |
|--------|-------------|
| -p port | Port number |
| -n name | Name of the team |
| -h machine | Name of the machine; localhost by default |

---

The server is executed as one single process and one single thread.  
It must use `select` to handle socket multiplexing; the select must unlock only if something happens on a socket or if an event is ready to be executed. (See strace)

:::warning
The team name GRAPHIC is reserved for the GUI to authenticate itself as such to the server.
:::

The AI client is autonomous.  
After it’s launched the user has no further influence on how it functions.  
It drives a drone (the player) (kind of similar to what a champion does in the Corewar project, remember?).

The graphical client is autonomous.

:::warning
The **mandatory** protocol for the graphical client is given alongside this subject, see **[GUI Protocol](/docs/Programs/GUI/Protocol.md)**.  
It is used by the reference server (so you can test your GUI with it aswell).
:::
