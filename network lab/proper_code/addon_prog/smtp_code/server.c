#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int s, c;
    char msg[200];
    struct sockaddr_in addr;

    // Create socket
    s = socket(AF_INET, SOCK_STREAM, 0);

    // Address settings
    addr.sin_family = AF_INET;
    addr.sin_port = htons(2525);
    addr.sin_addr.s_addr = INADDR_ANY;

    // Bind + Listen + Accept
    bind(s, (struct sockaddr*)&addr, sizeof(addr));
    listen(s, 1);

    printf("SMTP Server Waiting...\n");

    c = accept(s, NULL, NULL);

    printf("Client Connected\n");

    while(1) {

        // Receive mail
        read(c, msg, 200);

        printf("Mail Received: %s\n", msg);

        // Send reply
        strcpy(msg, "Mail Sent Successfully");

        send(c, msg, strlen(msg), 0);
    }

    close(c);
    close(s);

    return 0;
}
