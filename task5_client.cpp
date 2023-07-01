#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
int main() {
    // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // Prepare server address structure
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "Failed to convert address from text to binary form." << std::endl;
        return 1;
    }

    // Connect to server
    if (connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0) {
        std::cerr << "Failed to connect to server." << std::endl;
        return 1;
    }

    // Send data to server
    const char* message = "Hello, server!";
    if (write(clientSocket, message, strlen(message)) < 0) {
        std::cerr << "Failed to send data to server." << std::endl;
        return 1;
    }

    // Read response from server
    char buffer[1024] = {0};
    int bytesRead = read(clientSocket, buffer, sizeof(buffer));
    std::cout << "Received response from server: " << buffer << std::endl;

    // Close socket
    close(clientSocket);

    return 0;
}