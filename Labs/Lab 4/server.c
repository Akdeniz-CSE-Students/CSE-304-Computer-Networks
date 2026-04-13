#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server, client;
    socklen_t client_size;

    char buffer[1024] = {0};
    char reply[1024];

    int a, b;

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Set server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8082);

    // Bind
    bind(server_socket, (struct sockaddr *)&server, sizeof(server));

    // Listen
    listen(server_socket, 1);
    printf("Calculator Server running on port 8082...\n");

    // Accept
    client_size = sizeof(struct sockaddr_in);
    client_socket = accept(server_socket, (struct sockaddr *)&client, &client_size);

    // Receive
    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("Received: %s\n", buffer);

    // Parse input
    sscanf(buffer, "%d %d", &a, &b);

    // Compute
    int sum = a + b;
    int diff = a - b;

    // Format reply
    sprintf(reply, "SUM: %d | DIFF: %d", sum, diff);

    // Send reply
    send(client_socket, reply, strlen(reply), 0);

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
