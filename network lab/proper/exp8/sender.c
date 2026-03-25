#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int s, n, w, i = 1, ack;
    struct sockaddr_in sa;

    s = socket(AF_INET, SOCK_STREAM, 0);

    sa.sin_family = AF_INET;
    sa.sin_port = htons(8080);
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(s, (struct sockaddr*)&sa, sizeof(sa));

    printf("Enter no of frames: ");
    scanf("%d", &n);

    printf("Enter window size: ");
    scanf("%d", &w);

    while (i <= n) {
        int j;

        // send window
        for (j = 0; j < w && (i + j) <= n; j++) {
            int f = i + j;
            printf("Sending frame %d\n", f);
            send(s, &f, sizeof(f), 0);
        }

        // receive ACK
        read(s, &ack, sizeof(ack));
        printf("ACK %d received\n", ack);

        // slide window
        i = ack + 1;
    }

    close(s);
    return 0;
}
