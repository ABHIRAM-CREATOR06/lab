#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int servsock;
    char buffer[1024];
    char str[1000];
    int opt = 1;
    struct sockaddr_in clientaddr, servaddr;
    socklen_t len = sizeof(clientaddr);

    servsock = socket(AF_INET, SOCK_DGRAM, 0);
    if (servsock < 0) {
        perror("socket creation failed");
        return 1;
    }

    setsockopt(servsock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    setsockopt(servsock, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(2040);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    bind(servsock, (struct sockaddr *)&servaddr, sizeof(servaddr));

    while (1) {
        int i = recvfrom(servsock, buffer, 1024, 0,
                         (struct sockaddr *)&clientaddr, &len);

        buffer[i] = '\0';
        printf("Received: %s\n", buffer);

        if (strcmp(buffer, "stop") == 0)
            break;

        printf("Enter the message: ");
        scanf("%s", str);

        sendto(servsock, str, strlen(str), MSG_CONFIRM,
               (struct sockaddr *)&clientaddr, sizeof(clientaddr));
    }

    close(servsock);
    return 0;
}
