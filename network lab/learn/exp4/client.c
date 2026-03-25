#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 1029

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char buf[1000];

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port        = htons(PORT);

    connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Connected.\n");

    while (1) {
        printf("Enter a n (or 'stop'): ");
        scanf("%s", buf);
        send(client_fd, buf, strlen(buf), 0);

        if (strcmp(buf, "stop") == 0)
            break;

        int n = read(client_fd, buf, sizeof(buf) - 1);
        buf[n] = '\0';
        printf("Square: %s\n", buf);
    }

    close(client_fd);
    return 0;
}