import matplotlib.pyplot as plt

with open('./src/ai/dataSaved/behaviors.txt', 'r') as file:
    data = file.read()

lines = data.strip().split('\n')
iterations = []
survives = []
searchLinemates = []
incantationLvl1s = []

# iteration + behaviors + \n
for i in range(0, len(lines), 5):
    iterations.append(int(lines[i].split(':')[1]))
    survives.append(int(lines[i+1].split(':')[1]))
    searchLinemates.append(int(lines[i+2].split(':')[1]))
    incantationLvl1s.append(int(lines[i+3].split(':')[1]))

plt.figure(figsize=(12, 6))
bar_width = 0.25

r1 = [x - bar_width for x in range(len(iterations))]
r2 = range(len(iterations))
r3 = [x + bar_width for x in range(len(iterations))]

plt.bar(r1, survives, color='blue', width=bar_width, edgecolor='grey', label='Survive')
plt.bar(r2, searchLinemates, color='green', width=bar_width, edgecolor='grey', label='Search Linemate')
plt.bar(r3, incantationLvl1s, color='red', width=bar_width, edgecolor='grey', label='Incantation Lvl 1')

plt.xlabel('Iterations')
plt.ylabel('Values')
plt.title('Bar Plot of Iteration Data')
plt.xticks(range(len(iterations)), iterations)

plt.legend()

plt.show()
