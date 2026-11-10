OS LAB - 20 PROGRAMS (C, Ubuntu / Linux)
=========================================

SETUP (once)
  sudo apt update
  sudo apt install build-essential

COMPILE ALL
  chmod +x compile_all.sh
  ./compile_all.sh          (executables go into the bin/ folder)

COMPILE ONE
  gcc 01_fork.c -o 01_fork
  gcc 18_dining_philosophers.c -o 18_dining -pthread     (programs 18, 19, 20 need -pthread)

RUN
  cd bin
  ./01_fork

SAMPLE INPUTS FOR PROGRAMS THAT ASK FOR INPUT
---------------------------------------------
11 FCFS, 12 SJF, 13 SRTF  -> enter n, then "arrival burst" per process
    4
    0 5
    1 3
    2 8
    3 6

14 Round Robin -> same as above, then the time quantum at the end
    3
    0 5
    1 4
    2 2
    2

15 / 16 Priority -> "arrival burst priority" per process (lower number = higher priority)
    4
    0 8 3
    1 4 2
    2 2 4
    3 1 1

17 Banker's Algorithm (classic textbook example)
    processes = 5, resources = 3
    Allocation:   0 1 0 / 2 0 0 / 3 0 2 / 2 1 1 / 0 0 2
    Max:          7 5 3 / 3 2 2 / 9 0 2 / 2 2 2 / 4 3 3
    Available:    3 3 2
    Safe sequence: P1 -> P3 -> P4 -> P0 -> P2
    Optional request: process 1, request 1 0 2 -> granted

You can also feed input from a file:  ./11_fcfs < input.txt

NOTES
  * 04_stat takes an optional file name:  ./04_stat myfile.txt
  * 08, 09, 10 (IPC) use one program: parent = server, child processes = clients.
  * If a message queue / shared memory segment is ever left behind after Ctrl+C,
    clean it with:  ipcs   then   ipcrm -q <id>   or   ipcrm -m <id>
