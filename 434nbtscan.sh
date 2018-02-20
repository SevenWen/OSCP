# !/bin/bash

for server in $(grep Windows OSdis.txt | cut -d" " -f2);do
nbtscan -r $server;done
