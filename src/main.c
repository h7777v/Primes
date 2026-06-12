#include <stdio.h>
#include <stdlib.h>
#include "prime.h"

int main(int argc, char* argv[]){
    unsigned long long num = 25;

    if(argc >= 2){
        num = strtoull(argv[1], NULL, 10);
    }

    printf("%llu", getPrime(num));
    return 0;
}