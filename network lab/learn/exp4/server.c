#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 1029

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buf[1000];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port        = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 4);

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
    printf("Client connected.\n");

    while (1) {
        int n = read(client_fd, buf, sizeof(buf) - 1);
        if (n <= 0) break;
        buf[n] = '\0';
        printf("Received: %s\n", buf);

        if (strcmp(buf, "stop") == 0)
            break;

        int num;
        sscanf(buf, "%d", &num);      
        num = num * num;              
        sprintf(buf, "%d", num);      
        send(client_fd, buf, strlen(buf), 0);
    }

    close(client_fd);
    close(server_fd);
    return 0;
}