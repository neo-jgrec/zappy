---
sidebar_position: 11
---

# Ejection

A player can eject all other players from a shared unit of terrain by pushing them in the direction it is looking.  
When a client send the eject command to the server, all of the clients that are sharing the tile will receive the following line:
```
eject: K\n
```

Where **K** is the direction of the tile where the pushed player is coming from.

When a player ejects all other beings from the unit of terrain, it also destroy any eggs layed on
that unit.

