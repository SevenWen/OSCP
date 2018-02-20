# !/bin/bash

for ip in $(grep open 4_4SMTPSRV.txt | cut -d" " -f 2);do
echo VRFY bob | nc -nv -w 10 $ip 25;done
