#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

void main()
{
    int client, x;
    char buf[1000];
    struct sockaddr_in servaddr;

    client = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(1029);
    servaddr.sin_family = AF_INET;

    if(connect(client, (struct sockaddr*)&servaddr, sizeof(servaddr)) >= 0)
        printf("connected\n");

    while(1)
    {
        printf("Enter the data to send::: \n");
        scanf("%s", buf);

        send(client, buf, strlen(buf), 0);

        if(strcmp(buf, "stop") == 0)
            break;

        x = read(client, buf, 1000);
        if (x > 0) {
            buf[x] = '\0';
            printf("received %s\n", buf);
        }
    }

    close(client);
}
