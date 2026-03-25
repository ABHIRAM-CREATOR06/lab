#include <stdio.h>

int main() {
    int bucket_size = 10;   
    int output_rate = 7;    
    int buffer = 0;         
    int n, pkt;

    printf("Bucket Size = %d\n", bucket_size);
    printf("Output Rate = %d\n\n", output_rate);

    printf("Enter n of seconds (packets): ");
    scanf("%d", &n);

    printf("\nTime\tPacket\tBuffer\tStatus\t\tSent\n");

    for (int t = 1; t <= n; t++) {
        printf("\nSecond %d - Enter packet s: ", t);
        scanf("%d", &pkt);

        int space = bucket_size - buffer;   

        if (pkt <= space) {

            buffer += pkt;

            if (buffer >= output_rate) {
                buffer -= output_rate;
                printf("%d\t%d\t%d\tAccepted\t%d\n", t, pkt, buffer, output_rate);
            } else {
                printf("%d\t%d\t%d\tAccepted\t0\n", t, pkt, buffer);
            }
        } else {

            int rejected = pkt - space;
            buffer = bucket_size - output_rate;
            printf("%d\t%d\t%d\tRejected %d\t%d\n", t, pkt, buffer, rejected, output_rate);
        }
    }

    printf("\nSimulation complete.\n");
    return 0;
}