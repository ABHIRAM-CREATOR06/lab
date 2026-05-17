#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int palindrome(char str[]) {
    int i, j;
    j = strlen(str) - 1;

    for(i = 0; i < j; i++, j--) {
        if(str[i] != str[j])
            return 0;
    }
    return 1;
}

int main() {
    int s, c;
    char msg[100], reply[100];
    struct sockaddr_in addr;

    // Create socket
    s = socket(AF_INET, SOCK_STREAM, 0);

    // Address settings
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1026);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind, Listen, Accept
    bind(s, (struct sockaddr*)&addr, sizeof(addr));
    listen(s, 1);

    printf("Waiting for connection...\n");

    c = accept(s, NULL, NULL);

    printf("Client connected\n");

    while(1) {

        read(c, msg, 100);

        if(strcmp(msg, "stop") == 0)
            break;

        printf("Received: %s\n", msg);

        if(palindrome(msg))
            strcpy(reply, "Palindrome");
        else
            strcpy(reply, "Not Palindrome");

        send(c, reply, strlen(reply), 0);
    }

    close(c);
    close(s);

    return 0;
}
