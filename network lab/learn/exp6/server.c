#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 2040

int main() {
    int sock_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buf[1024];

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Server ready.\n");

    while (1) {

        int n = recvfrom(sock_fd, buf, sizeof(buf) - 1, 0,
                         (struct sockaddr *)&client_addr, &addr_len);
        buf[n] = '\0';
        printf("Client: %s\n", buf);

        if (strcmp(buf, "stop") == 0)
            break;

        printf("Enter reply: ");
        scanf("%s", buf);

        sendto(sock_fd, buf, strlen(buf), MSG_CONFIRM,
               (struct sockaddr *)&client_addr, addr_len);
    }

    close(sock_fd);
    return 0;
}