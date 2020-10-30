// Client code in C to sort the array 
#include <arpa/inet.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 
  
int main(int argc, char* argv[]) 
{ 
    int sock; 
    struct sockaddr_in server;
    int size=10;
    int server_reply[size]; 
    int number[size], i, temp;
    printf("enter the array elements\n"); 
    for(int x=0;x<size;x++)
    {
        scanf("%d",&number[x]);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0); 
    if (sock == -1) { 
        printf("Could not create socket"); 
    } 
    puts("Socket created"); 
  
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    server.sin_family = AF_INET; 
    server.sin_port = htons(8880); 
  

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) { 
        perror("connect failed. Error"); 
        return 1; 
    } 
  
    puts("Connection to server was successful\n"); 
  
    if (send(sock, &number, size * sizeof(int), 0) < 0) { 
        puts("Send failed"); 
        return 1; 
    } 
  
    if (recv(sock, &server_reply, size * sizeof(int), 0) < 0) { 
        puts("recv failed"); 
        return 0; 
    } 
  
    puts("Sorted numbers:\n"); 
    for (i = 0; i < size; i++) { 
        printf("%d ", server_reply[i]); 
    } 
    printf("\n");

    close(sock); 
    return 0; 
} 