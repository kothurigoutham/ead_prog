#!/bin/bash
# Compiles all 20 programs. Usage: chmod +x compile_all.sh && ./compile_all.sh
# Requires gcc:  sudo apt update && sudo apt install build-essential
mkdir -p bin
for f in [0-9][0-9]_*.c; do
    name="${f%.c}"
    if gcc -Wall -o "bin/$name" "$f" -pthread; then
        echo "compiled  $f  ->  bin/$name"
    else
        echo "FAILED    $f"
    fi
done
