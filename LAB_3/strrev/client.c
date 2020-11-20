#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> 
#include <sys/time.h> 

#define REMOTE_SERVER_PORT 8005
#define MAX_MSG 100


#define SOCKET_ERROR -1

int isReadable(int sd,int * error,int timeOut) {
fd_set socketReadSet;
FD_ZERO(&socketReadSet);
FD_SET(sd,&socketReadSet);
struct timeval tv;
if (timeOut) {
tv.tv_sec = timeOut / 1000;
tv.tv_usec = (timeOut % 1000) * 1000;
} else {
tv.tv_sec = 0;
tv.tv_usec = 0;
} // if
if (select(sd+1,&socketReadSet,0,0,&tv) == SOCKET_ERROR) {
*error = 1;
return 0;
} 
*error = 0;
return FD_ISSET(sd,&socketReadSet) != 0;
} 


int main(int argc, char *argv[]) {

int sd, rc, i, n, echoLen, flags, error, timeOut;
struct sockaddr_in cliAddr, remoteServAddr, echoServAddr;
struct hostent *h;
char msg[MAX_MSG];

if(argc<3) {
printf("usage : %s <server> <data1> ... <dataN> \n", argv[0]);
exit(1);
}

h = gethostbyname(argv[1]);
if(h==NULL) {
printf("%s: unknown host '%s' \n", argv[0], argv[1]);
exit(1);
}

printf("%s: sending data to '%s' (IP : %s) \n", argv[0], h->h_name,
inet_ntoa(*(struct in_addr *)h->h_addr_list[0]));

remoteServAddr.sin_family = h->h_addrtype;
memcpy((char *) &remoteServAddr.sin_addr.s_addr,
h->h_addr_list[0], h->h_length);
remoteServAddr.sin_port = htons(REMOTE_SERVER_PORT);

sd = socket(AF_INET,SOCK_DGRAM,0);
if(sd<0) {
printf("%s: cannot open socket \n",argv[0]);
exit(1);
}

cliAddr.sin_family = AF_INET;
cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
cliAddr.sin_port = htons(0);

rc = bind(sd, (struct sockaddr *) &cliAddr, sizeof(cliAddr));
if(rc<0) {
printf("%s: cannot bind port\n", argv[0]);
exit(1);
}


flags = 0;

timeOut = 100;
printf("Reverse of the string received from client: \n");
for(i=2;i<argc;i++) {
rc = sendto(sd, argv[i], strlen(argv[i])+1, flags,
(struct sockaddr *) &remoteServAddr,
sizeof(remoteServAddr));

if(rc<0) {
printf("%s: cannot send data %d \n",argv[0],i-1);
close(sd);
exit(1);
}
memset(msg,0x0,MAX_MSG);

echoLen = sizeof(echoServAddr);
n = recvfrom(sd, msg, MAX_MSG, flags,
(struct sockaddr *) &echoServAddr, &echoLen);

if(n<0) {
printf("%s: cannot receive data \n",argv[0]);
continue;
}
printf("%s ",msg);
}
printf("\n");
return 1;

}
