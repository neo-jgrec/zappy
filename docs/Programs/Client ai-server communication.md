---
sidebar_position: 4
---

# Client ai/server communication

The communication between the AI client and the server is carried out via **tcp** sockets.  
The port that is used must be indicated in parameters.

The client sends its requests, without waiting for them to be done.  
The server sends back a message confirming the correct execution of the requests.

The client’s connection to the server happens as follows:

1. the client opens a socket on the server’s port,
2. the server and the client communicate the following way:
```
<-- WELCOME\n
--> TEAM-NAME\n
<-- CLIENT-NUM\n
<-- X Y\n
```

**X** and **Y** indicate the world’s dimensions.  
**CLIENT-NUM** indicates the number of slots available on the server for the **TEAM-NAME** team.  
If this number is greater than or equal to 1, a new client can connect.

:::info
The client can send up to 10 requests in a row without any response from the server.  
Over 10, the server will no longer take them into account.
:::

The server executes the client’s requests in the order they were received.  
The requests are buffered and a command’s execution time only blocks the player in question.
