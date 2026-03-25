#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 1029

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char buf[1024];

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port        = htons(PORT);
    connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Connected.\n");

    send(client_fd, "server.c", 8, 0);

    int n;
    while ((n = read(client_fd, buf, sizeof(buf) - 1)) > 0) {
        buf[n] = '\0';
        printf("%s", buf);
    }

    close(client_fd);
    return 0;
}