# Bots

## Scope

Here is the documentation about zappy's bots:
- Usage
- Functionning
- Machine Learning
- Strategies
🤖<br>

## Usage 👨‍💻
**Run theses commands at root of projets**
- Run server:
```sh
./zappy_ai -p port -n team -h address
```

- Run the machine learning training:
```sh
python3 ./src/ai/src/training/training.py
```

- Run the graph for behaviors:
```sh
python3 ./src/ai/bonus/printBehaviorsGraph.py
```

## Functionning 🧑‍💼

### Probabilistic

We use a probability graph to take the worther actions.

* **V1**: We put ourselves the probabilties.

* **V2**: We train a model that calculates probabilities.

## Machine Learning 📖

### Integration
* An **ia** is an informatic programm that got:
    * Perception: Interaction with an environment or datas
    * Decision: Execute actions or solve problems.

Our bot do actions depending on the worth rate of an action. We calculate each turn which actions is worther depending on the state.<br>

Our models is ML trained by genetic algorithms.

### Genetic algorithms:
- Initialize a Population: Create an initial set of bots with random configurations.
- Evaluate Fitness: Run the bots and evaluate their performance based on the state they achieve.
- Selection: Select the best-performing bots.
- Crossover and Mutation: Create new bots by combining characteristics of the best bots and introducing slight changes (mutations).
- Repeat: Continue this process for a specified number of generations.

#### Trained variables:
- There is importance variables injected in conditions, can be whatever in number
- There is probability variables that must between 0 and 1

#### Mutations
- Will mutate importance on -2 : 2
- Will mutate probability on -0.1 : 0.1

**Fitness**: “Fitness” is used to evaluate the quality of candidate solutions in the current population. Each individual (or candidate solution) is evaluated based on a fitness function that quantifies their fitness or performance relative to the overall objective.

## Strategies 🥷

### Protocol of messages

- Messages are signed + encrypted.

### References
- [Remove ansi color on a string on python](https://stackoverflow.com/questions/14693701/how-can-i-remove-the-ansi-escape-sequences-from-a-string-in-python)