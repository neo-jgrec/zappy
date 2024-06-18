---
sidebar_position: 3
---

Each player responds to the following actions and **only** to these ones, with the following syntax:

| Action | Command | Time limit | Response |
|--------|---------|------------|----------|
| Move up one tile | Forward | 7/f | ok |
| Turn 90° right | Right | 7/f | ok |
| Turn 90° left | Left | 7/f | ok |
| Look around | Look | 7/f | [tile1, tile2,. .. ] |
| Inventory | Inventory | 1/f | [linemate n, sibur n,. .. ] |
| Broadcast text | Broadcast text | 7/f | ok |
| Number of team unused slots | Connect_nbr | - | value |
| Fork a player | Fork | 42/f | ok |
| Eject players from this tile | Eject | 7/f | ok/ko |
| Death of a player | - | - | dead |
| Take object | Take object | 7/f | ok/ko |
| Set object down | Set object | 7/f | ok/ko |
| Start incantation | Incantation | 300/f | Elevation underway / Current level: *k* / ko |

:::info
All commands are transmitted through a character string that ends with a new line.
:::

:::info
In case of a bad/unknown command, the server must answer “ko”.
:::

:::warning
The protocol defined at the end of this document must be respected!
:::
