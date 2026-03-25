#include <stdio.h>

#define INF 9999
#define MAX 10

struct RoutingTable {
    int dist[MAX];  
    int via[MAX];   
} rt[MAX];

int main() {
    int n, e;
    int cost[MAX][MAX];

    printf("Enter n of nodes: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            rt[i].dist[j] = INF;
            rt[i].via[j]  = 0;
        }
        rt[i].dist[i] = 0;
        rt[i].via[i]  = i;
    }

    printf("Enter n of links: ");
    scanf("%d", &e);
    printf("Enter each link as: start end cost\n");

    for (int i = 0; i < e; i++) {
        int s, d, c;
        scanf("%d %d %d", &s, &d, &c);

        rt[s].dist[d] = c;
        rt[d].dist[s] = c;
        rt[s].via[d]  = d;
        rt[d].via[s]  = s;
    }

    int changed;
    do {
        changed = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= n; k++) {

                    if (rt[i].dist[k] != INF && rt[k].dist[j] != INF) {
                        int new_dist = rt[i].dist[k] + rt[k].dist[j];
                        if (new_dist < rt[i].dist[j]) {
                            rt[i].dist[j] = new_dist;
                            rt[i].via[j]  = k;
                            changed++;
                        }
                    }
                }
            }
        }
    } while (changed > 0);

    for (int i = 1; i <= n; i++) {
        printf("\nRouting Table for Node %d\n", i);
        printf("Dest\tCost\tVia\n");
        for (int j = 1; j <= n; j++) {
            if (rt[i].dist[j] == INF)
                printf("%d\tINF\t-\n", j);
            else
                printf("%d\t%d\t%d\n", j, rt[i].dist[j], rt[i].via[j]);
        }
    }

    return 0;
}