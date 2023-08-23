#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>


#define SOCKET_PATH "/tmp/my_unix_socket"

int main() {
    int client_fd;
    struct sockaddr_un server_addr;

    // Create a socket
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_un)) == -1) {
        perror("Connection failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Send a message to the server
    char *message = (char *) malloc(sizeof(char) * 20);
    scanf("%s",message);
    ssize_t num_bytes_sent = write(client_fd, message, strlen(message));
    if (num_bytes_sent == -1) {
        perror("Sending failed");
    }

    // Close the socket
    close(client_fd);

    return 0;
}

