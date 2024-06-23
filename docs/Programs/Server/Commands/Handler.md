---
sidebar_position: 0
---

You will find all the commands the `src/server/src/commands/handler` folder.

This is the structure that will represent a command.

```c
typedef struct commands_s {
    char *name;
    void (*command)(client_t *client, server_t *server);
} commands_t;
```

**name**: the name of the command
**command**: the function pointer that will execute command

If you want to add **AI** or **GUI** commands you will need to update one of the 2 defines:

```c
#define NB_AI_COMMANDS 12
#define NB_GUI_COMMANDS 9
```

Don't forget to update these const variables that contains the commands:
```c
const commands_t commands_gui[NB_GUI_COMMANDS] = {
    {"msz", msz},
    {"bct", bct},
    {"mct", mct},
    {"tna", tna},
    {"ppo", ppo},
    {"plv", plv},
    {"pin", pin},
    {"sgt", sgt},
    {"sst", sst}
};

const commands_t commands_ai[NB_AI_COMMANDS] = {
    {"Forward", forward},
    {"Right", right},
    {"Left", left},
    {"Look", look},
    {"Inventory", inventory},
    {"Broadcast", broadcast},
    {"Connect_nbr", connect_nbr},
    {"Fork", fork_z},
    {"Eject", eject},
    {"Take", take},
    {"Set", set},
    {"Incantation", incantation},
};
```

If you want to add a **Hello World** command go [here](./Hello%20World.md)
