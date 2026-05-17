#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int s;
    char msg[100];
    struct sockaddr_in addr;

    // Create socket
    s = socket(AF_INET, SOCK_STREAM, 0);

    // Server address
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1026);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    connect(s, (struct sockaddr*)&addr, sizeof(addr));

    printf("Connected to server\n");

    while(1) {

        printf("Enter string/number: ");
        scanf("%s", msg);

        send(s, msg, strlen(msg), 0);

        if(strcmp(msg, "stop") == 0)
            break;

        read(s, msg, 100);

        printf("Server: %s\n", msg);
    }

    close(s);

    return 0;
}
