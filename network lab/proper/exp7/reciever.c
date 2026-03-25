#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int s, c, f, ack;
    struct sockaddr_in sa, ca;
    socklen_t l = sizeof(ca);

    s = socket(AF_INET, SOCK_STREAM, 0);

    sa.sin_family = AF_INET;
    sa.sin_port = htons(8080);
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(s, (struct sockaddr*)&sa, sizeof(sa));
    listen(s, 1);

    c = accept(s, (struct sockaddr*)&ca, &l);

    printf("Receiver ready...\n");

    while (1) {
        read(c, &f, sizeof(f));

        printf("Received frame %d\n", f);

        ack = f;
        send(c, &ack, sizeof(ack), 0);
    }

    close(c);
    close(s);
    return 0;
}
