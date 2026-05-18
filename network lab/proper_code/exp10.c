#include<stdio.h>

void main()
{
    int n, bksize = 10, buffer = 0, oprate = 7, i, pktsize;

    printf("Enter No: of Packets\n");
    scanf("%d", &n);

    printf("Bucket size=%d\n OutputRate=%d\n", bksize, oprate);

    for(i = 1; i <= n; i++)
    {
        printf("second %d:\nEnter incoming packet size\n ", i);
        scanf("%d", &pktsize);

        printf("\nTime\tPacketsize\tbuffer\taccept/reject\tsend\n");

        if (pktsize <= bksize - buffer)
        {
            buffer = buffer + pktsize;
            if (buffer >= oprate)
            {
                buffer = buffer - oprate;
                printf("%d\t%d\t\t%d\taccept%d\t\t%d\n", i, pktsize, buffer, pktsize, oprate);
            }
            else
            {
                printf("%d\t%d\t\t%d\taccept%d\t\t%d\n", i, pktsize, buffer, pktsize, 0);
            }
        }
        else
        {
            int dis = pktsize - (bksize - buffer);
            buffer = bksize - oprate;
            printf("%d\t%d\t\t%d\treject%d\t\t%d\n", i, pktsize, buffer, dis, oprate);
        }
    }
    printf("\nProcess continues............");
}

