# !/usr/bin/python

hex=0x00
f=open("Allhex","w")

while(hex<=0xff):
	f.write("\\x"+format(hex, '02x'))
	hex+=1;

f.close()
