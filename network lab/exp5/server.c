#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

void main()
{
    int server, client, addrlen;
    char buffer[1029];
    FILE *fp;
    struct sockaddr_in servaddr, clientaddr;

    server = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(1029);

    int b = bind(server, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if(b < 0)
    {
        printf("Error in binding\n");
    }

    listen(server, 3);
    
    addrlen = sizeof(struct sockaddr_in);
    client = accept(server, (struct sockaddr*)&clientaddr, &addrlen);
    if(client < 0)
        printf("not connected\n");

    int n = read(client, buffer, 1029);
    buffer[n] = '\0';
    printf("file name received is %s\n", buffer);
    fp = fopen(buffer, "r");

    if(fp == NULL)
        send(client, "File not present", strlen("File not present"), 0);
    else
    {
        while(fgets(buffer, 1029, fp) != NULL)
            send(client, buffer, strlen(buffer), 0);
        
        printf("file data send");
        fclose(fp);
    }

    close(client);
    close(server);
}
