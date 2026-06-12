#include <stdbool.h>
#include <math.h>

inline unsigned long long isqrt(unsigned long long x) {
    if (x == 0) return 0;

    unsigned long long r = (unsigned long long)sqrt((double)x);

    if ((r + 1) <= x / (r + 1)) ++r;
    if (r > x / r) --r;

    return r;
}

bool isPrime(unsigned long long n){
    if (n < 2) return false;
    if (n == 2) return true;
    if ((n & 1) == 0) return false;

    unsigned long long ubound = isqrt(n);

    for (unsigned long long i = 3;i <= ubound;i+=2){
        if (n % i == 0){
            return false;
        }
    }

    return true;
}

unsigned long long getPrime(unsigned long long n){
    unsigned long long i = 1;
    unsigned long long c = 2;

    while (i <= n){
        if (isPrime(c)){
            i++;
        }
        c++;
    }
    c--;

    return c;
}