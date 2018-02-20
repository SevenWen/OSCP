#!/bin/bash

for ip in $(grep Up pingscan.txt|cut -d" " -f 2);do
nmap -p 445,139 -sV  $ip -oG webserver.txt --append-output;done

#for ip in $(grep -e open -e filtered webserver.txt|cut -d" " -f 2);do
#nmap -O $ip -oG  serverOS.txt --append-output;done

