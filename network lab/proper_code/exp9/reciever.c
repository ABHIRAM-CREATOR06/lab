#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    int buffer[101] = {0};
    printf("Receiver: Waiting for packets...\n");

    // 1. Repeat until N frames has been received
    while (1) {
        int frame_id;
        // Wait for packet
        if (recvfrom(sock, &frame_id, sizeof(frame_id), 0, (struct sockaddr*)&client_addr, &addr_size) > 0) {
            
            // Randomly simulate packet loss (1 in 5 chance)
            if (rand() % 5 == 0) { 
                printf("Receiver: Frame %d received but dropped (simulating error)\n", frame_id);
                continue;
            }

            printf("Receiver: Frame %d received correctly\n", frame_id);
            // Store the frame
            buffer[frame_id] = 1; 

            // Send acknowledgment to sender
            sendto(sock, &frame_id, sizeof(frame_id), 0, (struct sockaddr*)&client_addr, addr_size);
            printf("Receiver: Sent ACK %d\n", frame_id);
        }
    }

    // 2. Arrange the frame based on the sequence number
    // (Handled automatically by the buffer indexing)
    
    close(sock);
    return 0; // 3. stop
}
