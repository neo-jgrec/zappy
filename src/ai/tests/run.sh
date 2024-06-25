#!/bin/zsh

current_dir=$(pwd)

cleanup() {
    echo "Closing terminals..."
    pkill -f "./zappy_server -x 30 -y 30 -n team1 team2 -c 10 -f 2 -p 4445"
    pkill -f "./zappy_ai -i team1 -h 127.0.0.1 -p 4445"
    pkill -f "./zappy_gui -h 127.0.0.1 -p 4445"
    # pkill -f "./zappy_gui -n team1 -h 127.0.0.1 -p 4445"
}

trap cleanup INT

gnome-terminal --working-directory="$current_dir" -- zsh -c "$current_dir/../zappy_server -x 30 -y 30 -n team1 team2 -c 10 -f 2 -p 4445; exec zsh" &
SERVER_PID=$!

# Wait for the server to start
sleep 2

gnome-terminal --working-directory="$current_dir" -- zsh -c "$current_dir/zappy_gui -i 127.0.0.1 -p 4445; exec zsh" &
GUI_PID=$!

sleep 2

gnome-terminal --working-directory="$current_dir" -- zsh -c "$current_dir/zappy_ai -n team1 -h 127.0.0.1 -p 4445; exec zsh" &
AI1_PID=$!

# sleep 2

# gnome-terminal --working-directory="$current_dir" -- zsh -c "$current_dir/zappy_ai -n team1 -h 127.0.0.1 -p 4445; exec zsh" &
# AI2_PID=$!

# sleep 2

# gnome-terminal --working-directory="$current_dir" -- zsh -c "$current_dir/zappy_ai -n team1 -h 127.0.0.1 -p 4445; exec zsh" &
# AI3_PID=$!

# sleep 2

# gnome-terminal --working-directory="$current_dir" -- zsh -c "$current_dir/zappy_ai -n team1 -h 127.0.0.1 -p 4445; exec zsh" &
# AI4_PID=$!

# sleep 2

# gnome-terminal --working-directory="$current_dir" -- zsh -c "$current_dir/zappy_ai -n team1 -h 127.0.0.1 -p 4445; exec zsh" &
# AI5_PID=$!

# sleep 2

# gnome-terminal --working-directory="$current_dir" -- zsh -c "$current_dir/zappy_ai -n team1 -h 127.0.0.1 -p 4445; exec zsh" &
# AI6_PID=$!

# sleep 2

# gnome-terminal --working-directory="$current_dir" -- zsh -c "$current_dir/zappy_ai -n team1 -h 127.0.0.1 -p 4445; exec zsh" &
# AI7_PID=$!

# sleep 2

# gnome-terminal --working-directory="$current_dir" -- zsh -c "$current_dir/zappy_ai -n team1 -h 127.0.0.1 -p 4445; exec zsh" &
# AI8_PID=$!

echo "Type 'leave' to close the terminals."
while read -r input; do
    if [ "$input" = "leave" ]; then
        cleanup
        break
    fi
done
