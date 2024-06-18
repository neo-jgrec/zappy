---
sidebar_position: 10
---

To emit a message, the client must send the following command to the server:
```
Broadcast text\n
```

The server will then send the following line to all of its clients:
```
message K, text\n
```

Where **K** is the tile indicating the direction the sound is coming from.
