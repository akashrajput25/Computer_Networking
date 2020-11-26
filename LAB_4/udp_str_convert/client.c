#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){
  int clientSocket, portNum, nBytes;
  char buffer[300];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(8081);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  addr_size = sizeof serverAddr;

  printf("Enter the string to send the server for string convertion :\n");
  fgets(buffer,300,stdin);

  nBytes = strlen(buffer) + 1;

  sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);

            nBytes = recvfrom(clientSocket,buffer,300,0,NULL, NULL);

  printf("Converted lowercase string received from server: %s\n",buffer);

 

  return 0;
}