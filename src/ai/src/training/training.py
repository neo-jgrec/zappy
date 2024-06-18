import subprocess
import time
import os
import signal
import random
import re
import matplotlib.pyplot as plt
from termcolor import colored

def start_server(port, width, height, team_names, client_count, freq):
    return subprocess.Popen(
        ['../zappy_server', '-p', str(port), '-x', str(width), '-y', str(height), '-n'] + team_names + ['-c', str(client_count), '-f', str(freq)],
        preexec_fn=os.setsid
    )

def stop_server(server_process):
    os.killpg(os.getpgid(server_process.pid), signal.SIGTERM)

def run_bot(port, team_name, host):
    return subprocess.Popen(['./zappy_ai', str(port), team_name, host], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

def write_config(file_path, config):
    with open(file_path, 'w') as f:
        for key, value in config.items():
            f.write(f"{key}={value}\n")

def generate_probabilities():
    probabilities = [round(random.uniform(0, 1), 2) for _ in range(3)]
    total = sum(probabilities)
    probabilities = [round(p / total, 2) for p in probabilities]
    return probabilities

def mutate_probability(prob):
    mutation = random.uniform(-0.1, 0.1)
    return round(max(0, min(1, prob + mutation)), 2)

def mutate_importance(importance):
    mutation = random.randint(-2, 2)
    return max(1, importance + mutation)

# Look at documentation for more information
def strip_ansi_escape_codes(s):
    ansi_escape = re.compile(r'\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])')
    return ansi_escape.sub('', s)

def parse_bot_output(output):
    bot_state = {
        "level": 0,
        "thystame": 0,
        "phiras": 0,
        "mendiane": 0,
        "sibur": 0,
        "deraumere": 0,
        "linemate": 0,
        "food": 0
    }
    output = strip_ansi_escape_codes(output.decode('utf-8'))
    lines = output.split('\n')
    state_started = False

    for line in lines:
        if "========== [Bot State] ==========" in line:
            state_started = True
        elif "========== [!Bot State] ==========" in line:
            break
        elif state_started:
            match = re.match(r"(\w+): (\d+)", line)
            if match:
                key = match.group(1)
                value = int(match.group(2))
                if key in bot_state:
                    bot_state[key] = value

    return bot_state

def print_best_bot_graph(bot):
    labels = ['food_probability', 'linemate_probability', 'incantation_probability', 'linemate_probability_2', 'deraumere_probability', 'sibur_probability']
    probabilities = [bot['config'][label] for label in labels]
    plt.bar(labels, probabilities)
    plt.ylim(0, 1)
    plt.title('Best Bot Probabilities')
    plt.ylabel('Probability')
    plt.show()

if __name__ == "__main__":
    port = 4040
    width = 10
    height = 30
    team_names = ['team1', 'team2']
    client_count = 2
    freq = 100
    host = '127.0.0.1'
    config_file_path = "./src/ai/config/config.txt"

    num_generations = 5
    population_size = 3
    max_stagnant_generations = 30
    stagnant_generations = 0
    previous_best_bot = None

    population = []
    for _ in range(population_size):
        food_importance = random.randint(1, 10)
        food_probability, linemate_probability, incantation_probability = generate_probabilities()
        linemate_probability_2 = mutate_probability(linemate_probability)
        deraumere_probability = mutate_probability(random.uniform(0, 1))
        sibur_probability = mutate_probability(random.uniform(0, 1))
        population.append({
            "config": {
                "food_importance": food_importance,
                "food_probability": food_probability,
                "linemate_probability": linemate_probability,
                "incantation_probability": incantation_probability,
                "linemate_probability_2": linemate_probability_2,
                "deraumere_probability": deraumere_probability,
                "sibur_probability": sibur_probability
            }
        })

    for generation in range(num_generations):
        print(colored(f"Generation {generation + 1}", 'blue'))

        server_process = start_server(port, width, height, team_names, client_count, freq)
        time.sleep(2)

        try:
            bot_processes = []
            for bot in population:
                write_config(config_file_path, bot['config'])

                bot_process = run_bot(port, team_names[0], host)
                bot_processes.append((bot_process, bot))

            for bot_process, bot in bot_processes:
                bot_stdout, bot_stderr = bot_process.communicate()
                bot['state'] = parse_bot_output(bot_stdout)

        finally:
            stop_server(server_process)

        population.sort(key=lambda x: (
            x['state']['level'],
            x['state']['thystame'],
            x['state']['phiras'],
            x['state']['mendiane'],
            x['state']['sibur'],
            x['state']['deraumere'],
            x['state']['linemate'],
            x['state']['food']
        ), reverse=True)

        best_bot = population[0]

        if previous_best_bot and previous_best_bot['config'] == best_bot['config']:
            stagnant_generations += 1
            if stagnant_generations >= max_stagnant_generations:
                break
        else:
            stagnant_generations = 0

        previous_best_bot = best_bot

        new_population = [best_bot]
        for _ in range(population_size - 1):
            new_bot = {
                "config": {
                    "food_importance": mutate_importance(best_bot['config']['food_importance']),
                    "food_probability": mutate_probability(best_bot['config']['food_probability']),
                    "linemate_probability": mutate_probability(best_bot['config']['linemate_probability']),
                    "incantation_probability": mutate_probability(best_bot['config']['incantation_probability']),
                    "linemate_probability_2": mutate_probability(best_bot['config']['linemate_probability_2']),
                    "deraumere_probability": mutate_probability(best_bot['config']['deraumere_probability']),
                    "sibur_probability": mutate_probability(best_bot['config']['sibur_probability'])
                }
            }
            new_population.append(new_bot)

        population = new_population

    best_bot = population[0]
    with open('./src/ai/config/config_trained.txt', 'w') as f:
        for key, value in best_bot['config'].items():
            f.write(f"{key}={value}\n")

    print_best_bot_graph(best_bot)

    print(colored("Best bot configurations:", 'blue'))
    for key, value in best_bot['config'].items():
        print(colored(f"{key}: ", 'green') + colored(f"{value}", 'yellow'))
    for key, value in best_bot['state'].items():
        print(colored(f"{key}: ", 'green') + colored(f"{value}", 'yellow'))
    print()
