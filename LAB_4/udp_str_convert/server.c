#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main(){
  int udpSocket, nBytes;
  char buffer[300];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  int i;

  udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(8081);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  addr_size = sizeof serverStorage;
  while(1){

    nBytes = recvfrom(udpSocket,buffer,300,0,(struct sockaddr *)&serverStorage, &addr_size);
    printf("I got the string : %s",buffer);
    for(i=0;i<nBytes-1;i++)

      buffer[i] = tolower(buffer[i]);
    printf("Converted the string to lowercase and sending back : %s",buffer);
    sendto(udpSocket,buffer,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);
  }

}