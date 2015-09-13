#!/bin/bash
#python -u myAI.py
cd ../myGame;
g++ -O3 main.cpp player.cpp -o player.o
./player.o