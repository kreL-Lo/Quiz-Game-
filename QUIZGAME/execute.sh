#!/bin/bash
g++ server.cpp -o server -l sqlite3 -pthread
#g++ results.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system  -pthread -l sqlite3 