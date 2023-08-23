#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/my_unix_socket"

int main() {
    int server_fd, client_fd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len;

    // Create a socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to a file path
    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_un)) == -1) {
        perror("Binding failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) == -1) {
        perror("Listening failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening...\n");

    // Accept connections from clients
    client_len = sizeof(struct sockaddr_un);
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd == -1) {
        perror("Accepting failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Read data from the client and print it
    char buffer[256];
    ssize_t num_bytes_read;
    while ((num_bytes_read = read(client_fd, buffer, sizeof(buffer))) > 0) {
        printf("Received message: %.*s\n", (int)num_bytes_read, buffer);
    }

    // Close the sockets and remove the socket file
    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH);

    return 0;
}

