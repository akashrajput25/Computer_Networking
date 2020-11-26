#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){
  int clientSocket, portNum, nBytes;
  char buffer[300];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  portNum = 8000;

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(portNum);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  printf("Enter the string that you want to convert to upper case or n/N to stop the program \n");
  fgets(buffer,300,stdin);
  printf("String in lowercase: %s",buffer);

  nBytes = strlen(buffer) + 1;

  send(clientSocket,buffer,nBytes,0);

  recv(clientSocket, buffer, 300, 0);

  printf("Server converted the string to uppercase : %s\n\n",buffer);   

}