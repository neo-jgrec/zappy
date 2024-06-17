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

def write_config(file_path, food_condition, food_probability, linemate_condition, linemate_probability):
    with open(file_path, 'w') as f:
        f.write(f"food_importance.condition={food_condition}\n")
        f.write(f"food_importance.probability={food_probability}\n")
        f.write(f"linemate_importance.condition={linemate_condition}\n")
        f.write(f"linemate_importance.probability={linemate_probability}\n")

def generate_probabilities():
    food_probability = round(random.uniform(0, 1), 2)
    linemate_probability = round(1 - food_probability, 2)
    return food_probability, linemate_probability

# Check documentation of ai to see how it works
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
    labels = ['food_probability', 'linemate_probability']
    probabilities = [bot['config']['food_probability'], bot['config']['linemate_probability']]
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

    best_bots = []

    for i in range(5):
        food_condition = random.randint(1, 10)
        linemate_condition = random.randint(1, 10)
        food_probability, linemate_probability = generate_probabilities()

        write_config(config_file_path, food_condition, food_probability, linemate_condition, linemate_probability)

        server_process = start_server(port, width, height, team_names, client_count, freq)
        time.sleep(2)

        try:
            bot1 = run_bot(port, team_names[0], host)
            bot1_stdout, bot1_stderr = bot1.communicate()

            bot2 = run_bot(port, team_names[0], host)
            bot2_stdout, bot2_stderr = bot2.communicate()

            bot1_state = parse_bot_output(bot1_stdout)
            bot2_state = parse_bot_output(bot2_stdout)

            bot1_data = {
                "config": {
                    "food_condition": food_condition,
                    "food_probability": food_probability,
                    "linemate_condition": linemate_condition,
                    "linemate_probability": linemate_probability
                },
                "state": bot1_state
            }
            bot2_data = {
                "config": {
                    "food_condition": food_condition,
                    "food_probability": food_probability,
                    "linemate_condition": linemate_condition,
                    "linemate_probability": linemate_probability
                },
                "state": bot2_state
            }

            best_bots.append(bot1_data)
            best_bots.append(bot2_data)

        finally:
            stop_server(server_process)

    best_bots.sort(key=lambda x: (x['state']['level'], x['state']['thystame'], x['state']['phiras'], x['state']['mendiane'], x['state']['sibur'], x['state']['deraumere'], x['state']['linemate'], x['state']['food']), reverse=True)
    with open('./src/ai/config/config_trained.txt', 'w') as f:
        f.write(f"food_importance.condition={best_bots[0]['config']['food_condition']}\n")
        f.write(f"food_importance.probability={best_bots[0]['config']['food_probability']}\n")
        f.write(f"linemate_importance.condition={best_bots[0]['config']['linemate_condition']}\n")
        f.write(f"linemate_importance.probability={best_bots[0]['config']['linemate_probability']}\n")
    print_best_bot_graph(best_bots[0])

    print(colored("Best bot configurations:", 'blue'))
    for bot in best_bots[:5]:
        for key, value in bot['config'].items():
            print(colored(f"{key}: ", 'green') + colored(f"{value}", 'yellow'))
        for key, value in bot['state'].items():
            print(colored(f"{key}: ", 'green') + colored(f"{value}", 'yellow'))
        print()
