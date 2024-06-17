import subprocess
import time
import os
import signal

def start_server(port, width, height, team_names, client_count, freq):
    return subprocess.Popen(
        ['../zappy_server', '-p', str(port), '-x', str(width), '-y', str(height), '-n'] + team_names + ['-c', str(client_count), '-f', str(freq)],
        preexec_fn=os.setsid
    )

def stop_server(server_process):
    os.killpg(os.getpgid(server_process.pid), signal.SIGTERM)

def run_bot(port, team_name, host):
    subprocess.run(['./zappy_ai', str(port), team_name, host])

if __name__ == "__main__":
    port = 4040
    width = 10
    height = 30
    team_names = ['team1', 'team2']
    client_count = 2
    freq = 10
    host = '127.0.0.1'

    server_process = start_server(port, width, height, team_names, client_count, freq)
    time.sleep(2)  # Wait for server to initialize

    # try:
    run_bot(port, team_names[0], host)
    # finally:
    #     stop_server(server_process)
