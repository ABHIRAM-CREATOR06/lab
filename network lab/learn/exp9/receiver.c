#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Receiver: Waiting for frames...\n");

    while (1) {
        int frame;
        recvfrom(sock, &frame, sizeof(frame), 0,
                 (struct sockaddr *)&client_addr, &addr_len);

        if (rand() % 5 == 0) {
            printf("Receiver: Frame %d DROPPED (simulated error)\n", frame);
            continue;   
        }

        printf("Receiver: Frame %d received OK\n", frame);

        sendto(sock, &frame, sizeof(frame), 0,
               (struct sockaddr *)&client_addr, addr_len);
        printf("Receiver: ACK %d sent\n", frame);
    }

    close(sock);
    return 0;
}