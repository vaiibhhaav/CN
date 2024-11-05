// TCP Client
#include <arpa/inet.h> // for inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // for bzero()
#include <sys/socket.h>
#include <unistd.h> // for read(), write(), close()
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Function for chat between client and server
void func(int sockfd) {
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string: ");
        n = 0;

        // Read input from the user and store it in buff
        while ((buff[n++] = getchar()) != '\n');

        // Send the message to the server
        write(sockfd, buff, strlen(buff));

        bzero(buff, sizeof(buff));

        // Read the response from the server
        int bytesRead = read(sockfd, buff, sizeof(buff));
        if (bytesRead <= 0) {
            printf("Server disconnected or read error occurred.\n");
            break;
        }

        // Print server response
        printf("From Server: %s", buff);

        // Exit the loop if the server sends "exit"
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr;

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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // Connect the client socket to the server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Connection with the server failed...\n");
        close(sockfd);
        exit(0);
    } else {
        printf("Connected to the server..\n");
    }

    // Function for chat
    func(sockfd);

    // Close the socket
    close(sockfd);
    return 0;
}

// gcc client.c -o client
// ./client

// PYTHON
/*
// Client Side:

import socket
def client_program():
 host = socket.gethostname() # as both code is running on 
same pc
 port = 5000 # socket server port number
 client_socket = socket.socket() # instantiate
 client_socket.connect((host, port)) # connect to the 
server
 message = input(" -> ") # take input
 while message.lower().strip() != 'bye':
 client_socket.send(message.encode()) # send message
 data = client_socket.recv(1024).decode() # receive 
response
 print('Received from server: ' + data) # show in 
terminal
 message = input(" -> ") # again take input
 client_socket.close() # close the connection
if __name__ == '__main__':
 client_program()

cd locaton
python client.py

*/