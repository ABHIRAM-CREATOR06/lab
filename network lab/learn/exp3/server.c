#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 1026

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buf[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port        = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    listen(server_fd, 3);
    printf("Waiting for client...\n");

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
    printf("Client connected.\n");

    while (1) {
        int n = read(client_fd, buf, sizeof(buf) - 1);
        buf[n] = '\0';
        printf("Client: %s\n", buf);

        if (strcmp(buf, "stop") == 0)
            break;

        printf("Enter reply: ");
        scanf("%s", buf);
        send(client_fd, buf, strlen(buf), 0);
    }

    close(client_fd);
    close(server_fd);
    return 0;
}