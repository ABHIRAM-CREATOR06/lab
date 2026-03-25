#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int servsock;
    char buffer[1024], str[1000];
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    servsock = socket(AF_INET, SOCK_DGRAM, 0);
    if (servsock < 0) {
        perror("socket creation failed");
        return 1;
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(2040);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    while (1) {
        printf("\nEnter the message to send: ");
        scanf("%s", str);

        sendto(servsock, str, strlen(str), MSG_CONFIRM,
               (struct sockaddr *)&servaddr, sizeof(servaddr));

        if (strcmp(str, "stop") == 0)
            break;

        int i = recvfrom(servsock, buffer, 1024, MSG_WAITALL,
                         (struct sockaddr *)&servaddr, &len);

        buffer[i] = '\0';
        printf("Received: %s\n", buffer);
    }

    return 0;
}
