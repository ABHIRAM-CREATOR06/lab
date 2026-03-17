#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int server, client;
    char buffer[1024];
    char s[1024];
    int PORT = 1026;
    struct sockaddr_in servaddr, clientaddr;
    socklen_t addrlen = sizeof(clientaddr);

    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        perror("socket creation failed");
        return 1;
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    if (bind(server, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        return 1;
    }

    if (listen(server, 3) < 0) {
        perror("listen failed");
        return 1;
    }

    client = accept(server, (struct sockaddr *)&clientaddr, &addrlen);
    if (client < 0) {
        perror("accept failed");
        return 1;
    }
    printf("connected \n");

    while (1) {
        int n = read(client, buffer, 1023);
        if (n < 0) {
            perror("read failed");
            break;
        }
        buffer[n] = '\0';
        printf("received %s\n", buffer);
        if (strcmp(buffer, "stop") == 0)
            break;
        printf("Enter The Data to send\n ");
        scanf("%s", s);
        if (send(client, s, strlen(s), 0) < 0) {
            perror("send failed");
            break;
        }
    }

    close(client);
    close(server);
    return 0;
}
