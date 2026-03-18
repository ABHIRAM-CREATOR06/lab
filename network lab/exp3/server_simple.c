#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int s, c;
    char msg[100];
    struct sockaddr_in addr;

    // 1. Create socket
    s = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Set address
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1026);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 3. Bind + Listen + Accept
    bind(s, (struct sockaddr*)&addr, sizeof(addr));
    listen(s, 1);
    c = accept(s, NULL, NULL);

    // 4. Communication
    while(1){
        read(c, msg, 100);
        printf("Client: %s\n", msg);

        scanf("%s", msg);
        send(c, msg, strlen(msg), 0);

        if(strcmp(msg,"stop")==0) break;
    }

    close(c);
    close(s);
}
