#include<stdio.h>
#include<arpa/inet.h>
#include <unistd.h>
#include<string.h>

void main()
{
    int server, len, client, n;
    struct sockaddr_in servaddr, clientaddr;
    char buf[1000];

    server = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(1029);

    int b = bind(server, (struct sockaddr*)&servaddr, sizeof(servaddr));

    if(b < 0)
    {
        printf("not bind with port no\n");
        return;
    }

    listen(server, 4);

    len = sizeof(clientaddr);
    client = accept(server, (struct sockaddr*)&clientaddr, &len);

    if(client > 0)
        printf("connected\n");

    while(1)
    {
        n = read(client, buf, 1000);
        if (n <= 0) break;
        buf[n] = '\0';

        printf("recieved %s\n", buf);

        if(strcmp(buf, "stop") == 0)
            break;

        int val;
        sscanf(buf, "%d", &val);
        val = val * val;
        sprintf(buf, "%d", val);

        send(client, buf, strlen(buf), 0);
    }

    close(client);
    close(server);
}
