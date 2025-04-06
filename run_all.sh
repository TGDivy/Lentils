#!/bin/bash

# ***** Compile Executable *****
mkdir -p build && cd build
cmake ..
cmake --build .

# ***** Run TCP server/client *****

echo "Running TCP Server:"
./src/tcp_server &           # Run server in background
TCP_SERVER_PID=$!
sleep 1

echo "Running TCP Client:"
./src/tcp_client

kill $TCP_SERVER_PID     # Stop server after client finishes
