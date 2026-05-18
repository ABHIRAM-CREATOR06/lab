#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int s, n, i = 1, ack;
    struct sockaddr_in sa;

    s = socket(AF_INET, SOCK_STREAM, 0);

    sa.sin_family = AF_INET;
    sa.sin_port = htons(8080);
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(s, (struct sockaddr*)&sa, sizeof(sa));

    printf("Enter number of frames: ");
    scanf("%d", &n);

    while (i <= n) {
        printf("Sending frame %d\n", i);
        send(s, &i, sizeof(i), 0);

        read(s, &ack, sizeof(ack));

        if (ack == i) {
            printf("ACK %d received\n", ack);
            i++;
        }
    }

    close(s);
    return 0;
}
