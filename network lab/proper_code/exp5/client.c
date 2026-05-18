#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main()
{
    int client;
    struct sockaddr_in serveraddr;
    char buffer[1029];

    client = socket(AF_INET, SOCK_STREAM, 0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    serveraddr.sin_port = htons(1029);

    if(connect(client, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) >= 0)
        printf("connected\n");

    send(client, "server.c", strlen("server.c"), 0);

    while(1)
    {
        int n = read(client, buffer, 1029);
        if (n <= 0)
            break;
        
        buffer[n] = '\0';
        printf("%s", buffer);
    }

    close(client);
    return 0;
}
