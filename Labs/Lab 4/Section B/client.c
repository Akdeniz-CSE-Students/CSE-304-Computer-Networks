#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int s;
    struct sockaddr_in server;

    char message[1024];
    char server_reply[1024];

    int a, b;

    // Create socket
    s = socket(AF_INET, SOCK_STREAM, 0);

    // Set server info
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8082);

    // Connect
    connect(s, (struct sockaddr *)&server, sizeof(server));

    // Get input from user
    printf("Enter two integers (e.g., 10 5): ");
    scanf("%d %d", &a, &b);

    // Format message
    sprintf(message, "%d %d", a, b);

    // Send message
    send(s, message, strlen(message), 0);

    // Receive reply
    recv(s, server_reply, sizeof(server_reply), 0);
    printf("Server replied: %s\n", server_reply);

    // Close socket
    close(s);

    return 0;
}

// asenkron programlama