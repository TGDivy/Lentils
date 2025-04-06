#!/bin/bash

# ***** Compile Executable *****
mkdir -p build && cd build
cmake ..
cmake --build .

# ***** Run TCP server/client *****

echo "Running: show_ip_addr"
echo ""
./src/show_ip_addr www.bloomberg.com
./src/show_ip_addr www.google.com
./src/show_ip_addr www.github.com
