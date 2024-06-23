---
sidebar_position: 0
---

This document serves as a technical guide on how to interact with the server. It covers the technologies used in the server's development, provides instructions on how to set up the server, and explains how to communicate with it effectively.


## Introduction

The server was developed using the following technologies:

- **C Programming Language**: The server is implemented in C, as it was a requirement for the project.

- **Socket Programming**: For network communication, we used sockets, which allow the server to communicate with clients over the network.

-  **select Function**: To handle multiple client connections simultaneously, the select function is used. This function monitors multiple file descriptors to see if any of them are ready for I/O operations.

## Key Functions and Concepts
- **Sockets**: A socket is an endpoint for sending and receiving data across a computer network. In this project, both TCP/IP and UDP protocols can be used.

- **select Function**: This function allows the server to monitor multiple sockets for incoming connections and data, enabling efficient management of multiple clients.
