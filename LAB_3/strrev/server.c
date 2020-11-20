#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> 
#include <string.h> 

#define LOCAL_SERVER_PORT 8005
#define MAX_MSG 100

int main(int argc, char *argv[]) {
int l,x,y;
char swp;
int sd, rc, n, cliLen, flags;
struct sockaddr_in cliAddr, servAddr;
char msg[MAX_MSG];


sd=socket(AF_INET, SOCK_DGRAM, 0);
if(sd<0) {
printf("%s: cannot open socket \n",argv[0]);
exit(1);
}

servAddr.sin_family = AF_INET;
servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
servAddr.sin_port = htons(LOCAL_SERVER_PORT);
rc = bind (sd, (struct sockaddr *) &servAddr,sizeof(servAddr));
if(rc<0) {
printf("%s: cannot bind port number %d \n",
argv[0], LOCAL_SERVER_PORT);
exit(1);
}

printf("%s: waiting for client to send a string and listening on port %u\n",argv[0],LOCAL_SERVER_PORT);

flags = 0;

while(1) {

memset(msg,0x0,MAX_MSG);

cliLen = sizeof(cliAddr);
n = recvfrom(sd, msg, MAX_MSG, flags,
(struct sockaddr *) &cliAddr, &cliLen);

if(n<0) {
printf("%s: cannot receive data \n",argv[0]);
continue;
}

l=strlen(msg);

for(x=0,y=l-1;x<l/2;x++,y--)
{
swp=msg[x];
msg[x]=msg[y];
msg[y]=swp;
}

sendto(sd,msg,n,flags,(struct sockaddr *)&cliAddr,cliLen);


}

return 0;

}