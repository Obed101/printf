#!/bin/bash
echo -e "\e[3m\e[33mProcessing..."
gcc -Wall -Werror -Wextra -pedantic -Wno-format -std=gnu89 *.c
