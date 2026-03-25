#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define PORT 8080

int main() {
    int sock, n, window_size;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter total frames (N): ");
    scanf("%d", &n);
    printf("Enter window s: ");
    scanf("%d", &window_size);

    int acked[101] = {0};   
    int base = 1;           
    int total_acked = 0;

    struct timeval tv = {2, 0};
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    while (total_acked < n) {

        for (int i = 0; i < window_size && (base + i) <= n; i++) {
            int frame = base + i;
            if (!acked[frame]) {
                printf("Sender: Sending frame %d\n", frame);
                sendto(sock, &frame, sizeof(frame), 0,
                       (struct sockaddr *)&server_addr, addr_len);
            }
        }

        int ack;
        if (recvfrom(sock, &ack, sizeof(ack), 0,
                     (struct sockaddr *)&server_addr, &addr_len) > 0) {
            if (ack <= n && !acked[ack]) {
                printf("Sender: ACK received for frame %d\n", ack);
                acked[ack] = 1;
                total_acked++;

                while (acked[base] && base <= n)
                    base++;
            }
        } else {
            printf("Sender: Timeout! Resending window...\n");
        }
    }

    printf("All frames sent and acknowledged.\n");
    close(sock);
    return 0;
}