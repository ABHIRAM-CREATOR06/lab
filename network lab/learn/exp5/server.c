#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 1029

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buf[1024];
    FILE *fp;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port        = htons(PORT);
    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 3);

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);

    int n = read(client_fd, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("File requested: %s\n", buf);

    fp = fopen(buf, "r");
    if (fp == NULL) {
        send(client_fd, "File not found", 14, 0);
    } else {

        while (fgets(buf, sizeof(buf), fp) != NULL)
            send(client_fd, buf, strlen(buf), 0);
        printf("File sent.\n");
        fclose(fp);
    }

    close(client_fd);
    close(server_fd);
    return 0;
}