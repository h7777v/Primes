#include <stdbool.h>
#include <stdint.h>
#include <intrin.h>
#include <math.h>

inline unsigned long long isqrt(unsigned long long x) {
    if (x == 0) return 0;

    unsigned long long r = (unsigned long long)sqrt((double)x);

    if ((r + 1) <= x / (r + 1)) ++r;
    if (r > x / r) --r;

    return r;
}

inline unsigned int modexp(unsigned int a, unsigned int e, unsigned int mod) {
    unsigned int result = 1;
    a %= mod;
    while (e > 0) {
        if (e & 1) {
            result = ((unsigned long long)result * a) % mod;
        }
        a = ((unsigned long long)a * a) % mod;
        e >>= 1;
    }
    return result;
}

bool isPrime(unsigned long long n){
    if (n < 2) return false;
    if (n == 2) return true;
    if ((n & 1) == 0) return false;

    if (n == 3 || n == 5 || n == 7 || n == 11 || n == 13) return true;
    if (n % 3 == 0 || n % 5 == 0 || n % 7 == 0 || n % 11 == 0 || n % 13 == 0) return false;

    uint8_t b[5] = {2, 3, 5, 7, 11};
    if (n >= 100000 && n <= 4294967295){
        for (uint8_t  i = 0; i < 5; i++){
            if (modexp(b[i], n-1, n) != 1) return false;
        }
    }

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