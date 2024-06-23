# AI - Machine Learning 🏫

## Scope

This documentation covers various aspects of our machine learning (ML) efforts:
- Usage
- Functioning
- Machine Learning
- Strategies
🤖<br/>

## Functioning 🧑‍💼

### Probabilistic

We utilize a probability graph to determine the optimal actions.

* **V1**: Manually assigned probabilities.
* **V2**: A trained model calculates probabilities.

## Machine Learning 📖

### Integration
* An **IA** is an informatic program that includes:
    * **Perception**: Interaction with an environment or data.
    * **Decision**: Execution of actions or problem-solving.

Our bot performs actions based on the worth rate of each action. We calculate the optimal actions each turn based on the current state.

Our model is trained using genetic algorithms.

### Genetic Algorithms:
1. **Initialize a Population**: Create an initial set of bots with random configurations.
2. **Evaluate Fitness**: Run the bots and evaluate their performance based on the states they achieve.
3. **Selection**: Select the best-performing bots.
4. **Crossover and Mutation**: Create new bots by combining characteristics of the best bots and introducing slight changes (mutations).
5. **Repeat**: Continue this process for a specified number of generations.

#### Trained Variables:
- **Importance Variables**: Injected into conditions, variable in number.
- **Probability Variables**: Values must be between 0 and 1.

#### Mutations:
- Importance variables mutate within the range -2 to 2.
- Probability variables mutate within the range -0.1 to 0.1.

**Fitness**: "Fitness" evaluates the quality of candidate solutions in the current population. Each individual (candidate solution) is assessed using a fitness function that quantifies their performance relative to the overall objective.
