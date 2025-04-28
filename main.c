#include "echo.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int PORT = 8888;
int LISTEN_BACKLOG = 5;

int main(int argc, char* argv[]){


    int port = PORT;
    int opt;
    if(argc > 2 && !strcmp(argv[1], "-p")){
        port = atoi(argv[2]);
    }

    //creating a socket and binding an adaress
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in socket_address;
    memset(&socket_address, '\0', sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_address.sin_port = htons(port);

    printf("Binding to port %d\n", port);
    //bind the socket to the address and port
    int returnval;
    returnval = bind(socket_fd, (struct sockaddr*)&socket_address, sizeof(socket_address));
    if(returnval < 0){
        perror("Bind failed");
        return 1;
    }
    returnval = listen(socket_fd, LISTEN_BACKLOG);

    //respond when someone connects to the socket
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);
    while(1){
        pthread_t thread;
        int* client_fd_buf = malloc(sizeof(int));

        *client_fd_buf = accept(socket_fd, (struct sockaddr*)&client_address, &client_address_len);
        
        printf("Accepted connection on %d\n", *client_fd_buf);

        pthread_create(&thread, NULL, (void* (*)(void*))handleConnection, (void*)client_fd_buf);


    }

    return 0;
}