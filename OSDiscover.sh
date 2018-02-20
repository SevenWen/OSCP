# !/bin/bash

for server in $(grep open webserver.txt| cut -d" " -f 2);do
nmap -sT -O $server -oG OSdis.txt --append-output;done
