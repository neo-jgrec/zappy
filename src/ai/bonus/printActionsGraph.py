import matplotlib.pyplot as plt

with open('./src/ai/dataSaved/actions_team1_986930438.txt', 'r') as file:
    data = file.read()

sections = data.strip().split('\n\n')

iterations = []
actions = {}

for section in sections:
    lines = section.strip().split('\n')
    iteration = int(lines[0].split(':')[1])
    iterations.append(iteration)
    for line in lines[1:]:
        action, value = line.split(':')
        action = action.strip()
        value = int(value.strip())
        if action not in actions:
            actions[action] = [0] * len(iterations)
        actions[action][-1] = value
    for action in actions:
        if len(actions[action]) < len(iterations):
            actions[action].append(0)

plt.figure(figsize=(12, 6))
colors = ['blue', 'green', 'red', 'purple', 'orange', 'cyan', 'magenta', 'yellow', 'brown']

for i, (action, values) in enumerate(actions.items()):
    filtered_iterations = [iterations[j] for j in range(len(values)) if values[j] != 0]
    filtered_values = [values[j] for j in range(len(values)) if values[j] != 0]
    plt.plot(filtered_iterations, filtered_values, color=colors[i % len(colors)], label=action, marker='o')

plt.xlabel('Iterations')
plt.ylabel('Values')
plt.title('Actions')

# Adjust x-ticks to avoid overlap
plt.xticks(ticks=iterations, labels=iterations, rotation=45, ha='right')

plt.legend()

plt.tight_layout()  # Adjust layout to make room for rotated x-ticks
plt.show()
