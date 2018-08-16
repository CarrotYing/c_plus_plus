#!/bin/bash
curr_path=$(pwd)
export LD_LIBRARY_PATH=$curr_path/lib/lib
source /etc/profile
./myHttp 8080 192.168.43.86
