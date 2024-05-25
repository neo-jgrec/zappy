#!/bin/zsh

current_dir=$(pwd)

cleanup() {
    echo "Closing terminals..."
    pkill -f "./zappy_server -p 4040 -x 10 -y 20 -n FRANCK JONAS -c 2 -f 2"
    pkill -f "./zappy_ai 4040 JONAS 127.0.0.1"
}

trap cleanup EXIT

gnome-terminal --working-directory="$current_dir/.." -- zsh -c "$current_dir/../zappy_server -p 4040 -x 10 -y 20 -n FRANCK JONAS -c 2 -f 2; exec zsh" &
SERVER_PID=$!

# Wait for the server to start
sleep 2

# bot
gnome-terminal --working-directory="$current_dir" -- zsh -c "$current_dir/zappy_ai 4040 JONAS 127.0.0.1; exec zsh" &
AI1_PID=$!

# bot
gnome-terminal --working-directory="$current_dir" -- zsh -c "$current_dir/zappy_ai 4040 JONAS 127.0.0.1; exec zsh" &
AI2_PID=$!

echo "Type 'leave' to close the terminals."
while read -r input; do
    if [ "$input" = "leave" ]; then
        cleanup
        break
    fi
done
