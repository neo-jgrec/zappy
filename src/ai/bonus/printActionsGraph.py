import matplotlib.pyplot as plt

# filename
with open('./src/ai/dataSaved/actionsteam11.txt', 'r') as file:
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
bar_width = 0.1
colors = ['blue', 'green', 'red', 'purple', 'orange', 'cyan', 'magenta', 'yellow', 'brown']

positions = {action: [x + (i - len(actions) / 2) * bar_width for x in range(len(iterations))]
             for i, action in enumerate(actions)}

for i, (action, values) in enumerate(actions.items()):
    plt.bar(positions[action], values, color=colors[i % len(colors)], width=bar_width, edgecolor='grey', label=action)

plt.xlabel('Iterations')
plt.ylabel('Values')
plt.title('Bar Plot of Iteration Actions')
plt.xticks(range(len(iterations)), iterations)
plt.legend()

plt.show()
