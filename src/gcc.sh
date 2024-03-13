#!/bin/bash
#g++ main.cpp -g -L../include/can -lmylibscan -lcontrolcan -lspdlog -lfmt -ludev -o move_sov 
#g++ main.cpp communication.cpp mathfunc.cpp Ti5BASIC.cpp  Ti5MOVE.cpp tool.cpp -g -L../include/can -lmylibscan -lcontrolcan -lspdlog -lfmt -ludev -o move_sov 
g++ main.cpp communication.cpp mathfunc.cpp Ti5BASIC.cpp  Ti5MOVE.cpp Ti5LOGIC.cpp tool.cpp clamping_jaw.cpp example.cpp -g -L../include/can  -I/usr/include/python3.10 -lpython3.10 -lmylibscan -lcontrolcan -lspdlog -lfmt -ludev -o move_sov
