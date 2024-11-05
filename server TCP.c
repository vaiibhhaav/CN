// TCP Server
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // for read(), write(), close()
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int connfd) {
    char buff[MAX];
    int n;

    // Infinite loop for chat
    for (;;) {
        bzero(buff, MAX);

        // Read the message from client and copy it in buffer
        int bytesRead = read(connfd, buff, sizeof(buff));
        if (bytesRead <= 0) {
            printf("Client disconnected or read error occurred.\n");
            break;
        }

        // Print buffer which contains the client contents
        printf("From client: %s\t To client: ", buff);
        bzero(buff, MAX);
        n = 0;

        // Copy server message into the buffer
        while ((buff[n++] = getchar()) != '\n');

        // Send that buffer to client
        write(connfd, buff, strlen(buff));

        // If message contains "exit" then server exit and chat ended
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}

// Driver function
int main() {
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // Socket creation and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed...\n");
        exit(0);
    } else {
        printf("Socket successfully created..\n");
    }
    bzero(&servaddr, sizeof(servaddr));

    // Assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket bind failed...\n");
        close(sockfd); // Close socket before exiting
        exit(0);
    } else {
        printf("Socket successfully binded..\n");
    }

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        close(sockfd); // Close socket before exiting
        exit(0);
    } else {
        printf("Server listening..\n");
    }
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, (socklen_t*)&len);
    if (connfd < 0) {
        printf("Server accept failed...\n");
        close(sockfd); // Close socket before exiting
        exit(0);
    } else {
        printf("Server accepted the client...\n");
    }

    // Function for chatting between client and server
    func(connfd);

    // Close the client and server sockets after chatting
    close(connfd); // Close the connected socket
    close(sockfd); // Close the listening socket
    return 0;
}

// gcc server.c -o server
// ./server

// PYTHON
/*
// Server Side:

import socket
def server_program():
 # get the hostname
 host = socket.gethostname()
 port = 5000 # initiate port no above 1024
 server_socket = socket.socket() # get instance
 # look closely. The bind() function takes tuple as 
argument
 server_socket.bind((host, port)) # bind host address and 
port together
 # configure how many client the server can listen 
simultaneously
 server_socket.listen(2)
 conn, address = server_socket.accept() # accept new 
connection
 print("Connection from: " + str(address))
 while True:
 # receive data stream. it won't accept data packet 
greater than 1024 bytes
 data = conn.recv(1024).decode()
 if not data:
 # if data is not received break
 break
 print("from connected user: " + str(data))
 data = input(' -> ')
 conn.send(data.encode()) # send data to the client
 conn.close() # close the connection
if __name__ == '__main__':
 server_program()


cd locaton
python filename.py

*/