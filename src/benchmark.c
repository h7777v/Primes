#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "prime.h"

#define TRIALS 10

unsigned long long getPrime(unsigned long long n);

int main(int argc, char* argv[]) {
    unsigned long long num = 25;
    double times[TRIALS] = {0};

    if (argc >= 2) {
        num = strtoull(argv[1], NULL, 10);
    }

    printf("N primes: %llu\n", num);

    for (int i = 0;i < TRIALS;i++){
        struct timespec start, end;

        timespec_get(&start, TIME_UTC);

        unsigned long long result = getPrime(num);

        timespec_get(&end, TIME_UTC);

        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        
        times[i] = elapsed;

        int temp = i + 1;
        int length = 0;
        
        if (temp == 0) {
            length = 1;
        } else {
            while (temp != 0) {
                length++;
                temp /= 10;
            }
        }

        printf("/-----TEST %d-----/\n", i + 1);
        printf("Result: %llu\n", result);
        printf("Time taken: %f seconds\n", elapsed);
        printf("/----------");
        for (int j = 0;j < length; j++){
            printf("-");
        }
        printf("-----/\n");
    }

    double sum = 0;

    for(int i = 0; i < TRIALS; i++) {
        sum += times[i];
    }

    printf("/----------------/\n");
    printf("Mean: %f seconds\n", sum/TRIALS);
    printf("/----------------/");

    return 0;
}
