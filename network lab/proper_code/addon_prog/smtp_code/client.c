#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int s;
    char msg[200];
    struct sockaddr_in addr;

    // Create socket
    s = socket(AF_INET, SOCK_STREAM, 0);

    // Server address
    addr.sin_family = AF_INET;
    addr.sin_port = htons(2525);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect
    connect(s, (struct sockaddr*)&addr, sizeof(addr));

    printf("Connected to SMTP Server\n");

    // Enter message
    printf("Enter Mail: ");
    scanf("%s", msg);

    // Send mail
    send(s, msg, strlen(msg), 0);

    // Receive response
    read(s, msg, 200);

    printf("Server: %s\n", msg);

    close(s);

    return 0;
}
