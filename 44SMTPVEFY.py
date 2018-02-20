#!/usr/bin/python 
import socket
import sys
if len(sys.argv) != 2:
	print "Usage: vrfy.py <username>" 
	sys.exit(0)

# Connect to the Server 
with open('Port25ip') as file :
	iplist=file.read().splitlines()
for ip in iplist:
	print ip
	# Create a Socket
	s=socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
	connect=s.connect((ip,25))
	# Receive the banner
	banner=s.recv(1024)
	print banner
	# VRFY a user
	s.send('VRFY ' + sys.argv[1] + '\r\n') 
	result=s.recv(1024)
	print result
	# Close the socket
	s.close()
