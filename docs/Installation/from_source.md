---
title: From source
sidebar_position: 1
---

## Dependencies

For this project, you will need the following dependencies:
- `sfml2.5.1` for the graphical interface (only needed by the `zappy_gui` library).
- `boost` for the `boost::tokenizer` and `boost::framework` libraries.
- `cmake` to build the project.
- `gcc` or `clang` to compile the project.

## Using the tools at your disposal

```bash
git clone git@github.com:neo-jgrec/zappy.git
git submodule update --init --recursive
cd zappy
make
```

And then to execute the project:

```bash
./zappy_server -p 4242 -x 10 -y 10 -n team1 team2 team3 team4 -c 10 -f 100
./zappy_ai -n team1 -h localhost -p 4242
./zappy_ai -n team2 -h localhost -p 4242
./zappy_ai -n team3 -h localhost -p 4242
./zappy_ai -n team4 -h localhost -p 4242
./zappy_gui -h localhost -p 4242
```

## If you want to do everything manually

With that aside, you can compile the project using `cmake` or your favorite compiler.

Finally, you can run the project with the following command:

```bash
./zappy_server -p 4242 -x 10 -y 10 -n team1 team2 team3 team4 -c 10 -f 100
./zappy_ai -n team1 -h localhost -p 4242
./zappy_ai -n team2 -h localhost -p 4242
./zappy_ai -n team3 -h localhost -p 4242
./zappy_ai -n team4 -h localhost -p 4242
./zappy_gui -h localhost -p 4242
```
