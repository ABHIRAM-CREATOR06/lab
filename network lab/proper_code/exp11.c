#include <stdio.h>

#define INF 9999

struct table
{
    int dist[10];
    int from[10];
} rt[10];

int main()
{
    int n, e, start, end, cost, i, j, k, c;
    int costmat[10][10];

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
        {
            rt[i].dist[j] = INF;
            rt[i].from[j] = 0;
        }
        rt[i].dist[i] = 0;
        rt[i].from[i] = i;
    }

    printf("Enter the number of connections: ");
    scanf("%d", &e);
    printf("Node numbers should start from 1\n");
    printf("Enter start node, end node and cost:\n");

    for(i = 1; i <= e; i++)
    {
        scanf("%d %d %d", &start, &end, &cost);
        costmat[start][end] = cost;
        costmat[end][start] = cost;
        rt[start].dist[end] = cost;
        rt[end].dist[start] = cost;
        rt[start].from[end] = end;
        rt[end].from[start] = start;
    }

    do
    {
        c = 0;
        for(i = 1; i <= n; i++)
        {
            for(j = 1; j <= n; j++)
            {
                for(k = 1; k <= n; k++)
                {
                    if(rt[i].dist[k] != INF && rt[k].dist[j] != INF)
                    {
                        if(rt[i].dist[j] > rt[i].dist[k] + rt[k].dist[j])
                        {
                            rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
                            rt[i].from[j] = k;
                            c++;
                        }
                    }
                }
            }
        }
    } while(c > 0);

    for(i = 1; i <= n; i++)
    {
        printf("\nRouting table for node %d\n", i);
        printf("Destination\tCost\tVia\n");
        for(j = 1; j <= n; j++)
        {
            if(rt[i].dist[j] == INF)
                printf("%d\t\tINF\t-\n", j);
            else
                printf("%d\t\t%d\t%d\n", j, rt[i].dist[j], rt[i].from[j]);
        }
    }

    return 0;
}
