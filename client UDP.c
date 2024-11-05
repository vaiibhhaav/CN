// UDP Client
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1" // Server IP address

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr;
    socklen_t len;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    len = sizeof(servaddr);
    while (1) {
        printf("Enter message for server: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Send message to the server
        int n = sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *) &servaddr, len);
        if (n < 0) {
            perror("sendto failed");
            break;
        }

        // Receive the server's response
        n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &servaddr, &len);
        if (n < 0) {
            perror("recvfrom failed");
            break;
        }
        buffer[n] = '\0';
        printf("Server: %s\n", buffer);

        // Exit the loop if "exit" message is sent
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Client exiting...\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}

// gcc client.c -o client
// ./client

// PYTHON
/*
// Client Side:

import socket
# Define the server IP address and port
server_ip = '127.0.0.1' # Replace with the server's IP 
address or use 'localhost' for local testing
server_port = 12345 # Match the server's port number
# Create a UDP socket
client_socket = socket.socket(socket.AF_INET, 
socket.SOCK_DGRAM)
while True:
 try:
 # Get user input
 message = input("Enter a message (or 'exit' to quit): 
")
 if message.lower() == 'exit':
 break
 # Send the message to the server
 client_socket.sendto(message.encode('utf-8'), 
(server_ip, server_port))
 # Receive a response from the server
 response, server_address = 
client_socket.recvfrom(1024)
 print(f"Response from server ({server_address}): 
{response.decode('utf-8')}")
 except KeyboardInterrupt:
 print("Client terminated by the user.")
 break
# Close the client socket
client_socket.close()


cd locaton
python client.py

*/