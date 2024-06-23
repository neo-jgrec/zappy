---
sidebar_position: 1
---

Create a file in the `src/server/src/commands/ai` or `src/server/src/commands/gui` folder with the name of the command that you want to implement, of course if you add a AI command add it in the ai folder and same for gui!

```c
void hello_world(client_t *client, server_t *server) {
    printf("Hello from the client %d and the size of the map is X(%u) Y(%u)\n", client->id, server->x, server->y);
}
```

Congratulations you created your new command 🚀.
