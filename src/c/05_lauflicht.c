#define __GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

int main() {
    while(1) {
        for (int i = 0; i < 20; i++) {
            // printf("\r");
            for (int j = 0; j < 20; j++) {
                if (i == j)
                    printf("*");
                else
                    printf(" ");
            }
            fflush(stdout);
            usleep(100000);
            printf("\n");
        }
    }

    return 0;
}
