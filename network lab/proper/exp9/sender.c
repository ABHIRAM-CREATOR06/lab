#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define PORT 8080

int main() {
    int sock, n, window_size;
    struct sockaddr_in server_addr;
    socklen_t addr_size = sizeof(server_addr);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 1. Read N frames of data to send
    printf("Enter total number of frames (N): ");
    scanf("%d", &n);
    // 2. Send window size number of frames
    printf("Enter window size: ");
    scanf("%d", &window_size);

    int acknowledged[101] = {0};
    int next_to_send = 1;
    int total_ack = 0;

    struct timeval tv = {2, 0}; 
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    // 3. Repeat until acknowledgment from n frames has been received
    while (total_ack < n) {
        for (int i = 0; i < window_size && (next_to_send + i) <= n; i++) {
            int current = next_to_send + i;
            if (!acknowledged[current]) {
                printf("Sender: Sending Frame %d\n", current);
                sendto(sock, &current, sizeof(current), 0, (struct sockaddr*)&server_addr, addr_size);
            }
        }

        int ack;
        if (recvfrom(sock, &ack, sizeof(ack), 0, (struct sockaddr*)&server_addr, &addr_size) > 0) {
            if (ack <= n && !acknowledged[ack]) {
                printf("Sender: Acknowledgment for Frame %d received\n", ack);
                acknowledged[ack] = 1;
                total_ack++;
                // Slide the window to next frame
                while (acknowledged[next_to_send] && next_to_send <= n) {
                    next_to_send++;
                }
            }
        } else {
            printf("Sender: Timeout! Resending frames...\n");
        }
    }

    printf("\nResult: Selective repeat simulation successful\n");
    close(sock);
    return 0; // 4. stop
}
