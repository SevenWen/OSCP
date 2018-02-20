#! /bin/bash

for server in $(grep Windows OSdis.txt | cut -d" " -f2);do
nmap -v -p 139,445 --script=smb-vuln-ms08-067 --script-args=unsafe=1 $server;done
