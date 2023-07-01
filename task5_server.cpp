#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // Create socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // Prepare server address structure
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    // Bind socket to address
    if (bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0) {
        std::cerr << "Failed to bind socket." << std::endl;
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 3) < 0) {
        std::cerr << "Failed to listen for connections." << std::endl;
        return 1;
    }

    std::cout << "Server is listening on port 8080..." << std::endl;

    // Accept incoming connection
    int clientSocket;
    sockaddr_in clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);
    clientSocket = accept(serverSocket, reinterpret_cast<struct sockaddr*>(&clientAddress), &clientAddressLength);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept connection." << std::endl;
        return 1;
    }

    // Read data from client
    char buffer[1024] = {0};
    int bytesRead = read(clientSocket, buffer, sizeof(buffer));
    std::cout << "Received message from client: " << buffer << std::endl;

    // Send response to client
    const char* response = "Message received.";
    write(clientSocket, response, strlen(response));

    // Close sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}