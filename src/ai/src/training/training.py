import subprocess
import time
import os
import signal
import random

def start_server(port, width, height, team_names, client_count, freq):
    return subprocess.Popen(
        ['../zappy_server', '-p', str(port), '-x', str(width), '-y', str(height), '-n'] + team_names + ['-c', str(client_count), '-f', str(freq)],
        preexec_fn=os.setsid
    )

def stop_server(server_process):
    os.killpg(os.getpgid(server_process.pid), signal.SIGTERM)

def run_bot(port, team_name, host):
    subprocess.run(['./zappy_ai', str(port), team_name, host])

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

if __name__ == "__main__":
    port = 4040
    width = 10
    height = 30
    team_names = ['team1', 'team2']
    client_count = 2
    freq = 10
    host = '127.0.0.1'
    config_file_path = "./src/ai/config/config.txt"

    food_condition = random.randint(1, 10)
    linemate_condition = random.randint(1, 10)
    food_probability, linemate_probability = generate_probabilities()

    write_config(config_file_path, food_condition, food_probability, linemate_condition, linemate_probability)

    server_process = start_server(port, width, height, team_names, client_count, freq)
    time.sleep(2)

    try:
        bot1 = subprocess.Popen(['./zappy_ai', str(port), team_names[0], host])

        bot2 = subprocess.Popen(['./zappy_ai', str(port), team_names[0], host])

        bot1.wait()
        bot2.wait()
    finally:
        stop_server(server_process)
