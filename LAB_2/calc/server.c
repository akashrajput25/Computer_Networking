#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
 
#define MAXBUF 1024
#define QUEUE_NO 5
 
int main(int argc, char **argv) {
    int sockfd, clientfd, port, int_to_receive,int_to_send,two_x,x_sq,sum;
    struct sockaddr_in s_addr, c_addr;
    char buffer[MAXBUF];
    socklen_t socklen = (socklen_t)sizeof(struct sockaddr_in);
 
    if (argc < 2) {
        printf("Some of the command line arguments missing");
        return -1;
    }
 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(errno);
    }
        printf("Socket successfully created..\n");
 
    bzero(&s_addr, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    port = atoi(argv[1]);
    s_addr.sin_port = htons(port);
    s_addr.sin_addr.s_addr = INADDR_ANY;
 
    if (bind(sockfd, (struct sockaddr*)&s_addr, sizeof(s_addr)) != 0){
        printf("socket creation failed...\n");
        exit(errno);
    }
 
    if (listen(sockfd, QUEUE_NO) != 0) {
        printf("socket listen failed...\n");
        exit(errno);
    }
    
    
    clientfd = accept(sockfd, (struct sockaddr*)&c_addr, &socklen);
    printf("%s:%d connected\n", inet_ntoa(c_addr.sin_addr), ntohs(c_addr.sin_port));
    read(clientfd, &int_to_receive, sizeof(int_to_receive));
    printf("Received from client: %d\n", int_to_receive);
    x_sq=int_to_receive*int_to_receive;
    two_x=2*int_to_receive;
    write(clientfd, &two_x, sizeof(two_x));
    write(clientfd, &x_sq, sizeof(x_sq));
    read(clientfd, &sum, sizeof(sum));
    printf("sum of X^2 and 2*X recieved from client = %d\n",sum);
    close(clientfd);

 
    close(sockfd);
    return 0;
}