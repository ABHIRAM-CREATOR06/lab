#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 2040

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    char buf[1024];

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    while (1) {
        printf("Enter message: ");
        scanf("%s", buf);

        sendto(sock_fd, buf, strlen(buf), MSG_CONFIRM,
               (struct sockaddr *)&server_addr, sizeof(server_addr));

        if (strcmp(buf, "stop") == 0)
            break;

        int n = recvfrom(sock_fd, buf, sizeof(buf) - 1, MSG_WAITALL,
                         (struct sockaddr *)&server_addr, &addr_len);
        buf[n] = '\0';
        printf("Server: %s\n", buf);
    }

    return 0;
}