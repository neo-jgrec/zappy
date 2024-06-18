---
sidebar_position: 6
---

# Vision

For various reasons, the players’ field of vision is limited.  
With each elevation, the vision increases by one unit in front, and one on each side of the new line.  
At the first level, the unit is defined as 1.  

In order for a player to recognize their team, the client sends the **look** command. The server will respond with the character string, as follows.

```
look
[player, object-on-tile1, ..., object-on-tileP,...]
```

The following diagram explains the numbering concept:

![Vision](/img/vision.png)

If more than one object is located on a tile, they will all be indicated and separated by a space.  
Here’s an example for a level-1 player having two objects in tile 1:

```
look
[player, player deraumere,,]
```

:::info
Beware, the tile separator is a comma followed or not by a space.
:::
