#!/bin/bash
g++ client.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system  -pthread -l sqlite3 
#g++ results.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system  -pthread -l sqlite3 