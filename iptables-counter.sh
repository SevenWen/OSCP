#! /bin/bash

#reset all counter and iptables rules
iptables -Z && iptables -F

#measure incoming traffic to 10.11.1.229
iptables -I INPUT 1 -s 10.11.1.229 -j ACCEPT

#measure outgoing traffic to 10.11.1.229
iptables -I OUTPUT 1 -d 10.11.1.229 -j ACCEPT

