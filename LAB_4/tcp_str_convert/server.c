#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main(){
  int welcomeSocket, newSocket, portNum, clientLen, nBytes;
  char buffer[300];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  int i;

  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

  portNum = 8081;
  
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(portNum);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  if(listen(welcomeSocket,5)==0)
    printf("Server is binded and Listening to port %d\n",portNum);
  else
    printf("Error\n");

  addr_size = sizeof serverStorage;

  while(1){
    newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
    if(!fork()){
      nBytes = 1;
      while(nBytes!=0){
        nBytes = recv(newSocket,buffer,300,0);
        for (i=0;i<nBytes-1;i++)
        {
            buffer[i] = toupper(buffer[i]);
        }

        send(newSocket,buffer,nBytes,0);
      }
      close(newSocket);
      exit(0);
    }
    else{
      close(newSocket);
    }
  }
}