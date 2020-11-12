#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

void send_receive_integer_over_socket(int sockfd) { 
    int int_to_send,sum,x_sq,two_x; 
    printf("enter the integer value to be sent to server\n");
    scanf("%d",&int_to_send);
    write(sockfd, &int_to_send, sizeof(int_to_send));
     
    read(sockfd, &x_sq, sizeof(x_sq));
    read(sockfd, &two_x, sizeof(two_x));
    printf("2*X: %d and X^2: %d\n",x_sq,two_x); 
    sum=x_sq+two_x;
    write(sockfd, &sum, sizeof(sum)); 
} 
 
int main(int argc, char **argv) { 
    int sockfd, port; 
    struct sockaddr_in servaddr, cli; 
 
    if (argc < 3) {
        printf("Some of the command line arguments missing");
        return -1;
    }
 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(errno); 
    }   
    printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(argv[1]); 
    port = atoi(argv[2]);
    servaddr.sin_port = htons(port); 
 
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(errno);
    } 
    printf("connected to the server..\n"); 
 
    send_receive_integer_over_socket(sockfd); 
 
    close(sockfd);
    return 0;
} 