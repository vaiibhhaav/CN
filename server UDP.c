// UDP Server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;         // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP
    servaddr.sin_port = htons(PORT);       // Port number

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);
    
    // Server loop to receive and echo messages
    len = sizeof(cliaddr);
    while (1) {
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &cliaddr, &len);
        if (n < 0) {
            perror("recvfrom failed");
            break;
        }
        buffer[n] = '\0';
        printf("Client: %s\n", buffer);

        // Echo message back to the client
        if (sendto(sockfd, buffer, n, 0, (const struct sockaddr *) &cliaddr, len) < 0) {
            perror("sendto failed");
            break;
        }
        printf("Echoed message back to client\n");
    }

    close(sockfd);
    return 0;
}

// gcc server.c -o server
// ./server

// PYTHON
/*
// Server Side:

import socket
# Define the server IP address and port
server_ip = '127.0.0.1' # Replace with your server's IP 
address or use 'localhost' for local testing
server_port = 12345 # Choose a port number
# Create a UDP socket
server_socket = socket.socket(socket.AF_INET, 
socket.SOCK_DGRAM)
# Bind the socket to the server address and port
server_socket.bind((server_ip, server_port))
print(f"Server listening on {server_ip}:{server_port}")
while True:
 try:
 # Receive data from the client
 data, client_address = server_socket.recvfrom(1024)
 print(f"Received message from {client_address}: 
{data.decode('utf-8')}")
 # Process the received data (You can add your own 
logic here)
 # Send a response back to the client
 response = "Message received by the server."
 server_socket.sendto(response.encode('utf-8'), 
client_address)
 except KeyboardInterrupt:
 print("Server terminated by the user.")
 break
# Close the server socket
server_socket.close()

cd locaton
python server.py

*/