#!/usr/bin/env sh

test_response_time() {
    local server=$1
    local port=$2
    local start_time
    local end_time
    local response_time

    start_time=$(date +%s%N)
    response=$(nc -zv $server $port)
    end_time=$(date +%s%N)

    if [[ $response == *"ok\n"* ]]; then
        response_time=$((end_time - start_time))
    else
        response_time=-1
    fi

    echo $response_time
}

server1="127.0.0.1"
port1=3000

server2="127.0.0.1"
port2=3001

response_time1=$(test_response_time $server1 $port1)
response_time2=$(test_response_time $server2 $port2)

echo "Response time for server1 on port $port1: $response_time1 ns"
echo "Response time for server2 on port $port2: $response_time2 ns"

if [[ $response_time1 -eq -1 || $response_time2 -eq -1 ]]; then
    echo "One or both servers did not return 'ok' response."
elif [[ $response_time1 -eq $response_time2 ]]; then
    echo "Both servers returned 'ok' at the same time."
else
    echo "Servers did not return 'ok' at the same time."
fi
