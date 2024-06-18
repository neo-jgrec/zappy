---
sidebar_position: 7
---

Sound is a wave that spreads out linearly (at least on Trantor) by broadcasting.  
All the players can hear the broadcasts without knowing who is playing them.  
They can only perceive the direction the sound is coming from and its subsequent message.  

:::warning
The direction is indicated by the number of the tile affected by the sound, before arriving
in the player’s tile.  
This numbering is done through attributing 1 to the tile that is located in front of the player, then through deducting the tiles that trigonomically encircle the player.  
In the event that the broadcast is emitted from the same player receptor tile, they will
receive the message coming from the 0 tile.
:::

:::info
As the world is spherical, several trajectories are possible for the sound between the emitter and the player.  
The shortest path will always be chosen.  
:::

Here is an example showing the shortest sound trajectory and the tile numbering around the
player.

![Sound transmission](/img/broadcast.png)
