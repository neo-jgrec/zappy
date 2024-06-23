---
sidebar_position: 7
---


## Player Actions and Communication Protocol

Each player can perform specific actions, communicated via character strings that end with a newline. The server responds with a confirmation or an error.

| Action                          | Command      | Time Limit | Response                  |
|---------------------------------|--------------|------------|---------------------------|
| Move up one tile                | Forward      | 7/f        | ok                        |
| Turn 90° right                  | Right        | 7/f        | ok                        |
| Turn 90° left                   | Left         | 7/f        | ok                        |
| Look around                     | Look         | 7/f        | [tile1, tile2, ...]       |
| Inventory                       | Inventory    | 1/f        | [linemate n, sibur n, ...]|
| Broadcast text                  | Broadcast    | 7/f        | ok                        |
| Number of team unused slots     | Connect_nbr  | -          | value                     |
| Fork a player                   | Fork         | 42/f       | ok                        |
| Eject players from this tile    | Eject        | 7/f        | ok/ko                     |
| Death of a player               | -            | -          | dead                      |
| Take object                     | Take object  | 7/f        | ok/ko                     |


You want to create your command? Go to the [handler](./Commands/Handler.md).
