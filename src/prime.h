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

unsigned int gcd(unsigned int a, unsigned int b) {
    while (b != 0) {
        unsigned int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int jacobi(unsigned int a, unsigned int n) {
    if (n == 0 || (n & 1) == 0)
        return 0;

    int t = 1;
    unsigned int m = n;

    a %= m;

    while (a != 0) {
        while ((a & 1) == 0) {
            a >>= 1;
            unsigned int r = m % 8;
            if (r == 3 || r == 5)
                t = -t;
        }

        unsigned int tmp = a;
        a = m;
        m = tmp;

        if ((a % 4 == 3) && (m % 4 == 3))
            t = -t;

        a %= m;
    }

    return (m == 1) ? t : 0;
}

int solovay_strassen(unsigned int n, unsigned int a) {
    if (n < 2) return 0;
    if (n == 2 || n == 3) return 1;
    if ((n & 1) == 0) return 0;

    if (a < 2 || a >= n - 1)
        return 0;

    if (gcd(a, n) > 1)
        return 0;

    unsigned int exp = (n - 1) >> 1;

    unsigned int x = modexp(a, exp, n);

    int j = jacobi(a, n);

    unsigned int j_mod = (j == -1) ? n - 1 : (unsigned int)j;

    return x == j_mod;
}

bool isPrime(unsigned long long n){
    if (n < 2) return false;
    if (n == 2) return true;
    if ((n & 1) == 0) return false;

    if (n == 3 || n == 5 || n == 7 || n == 11 || n == 13 || n == 17 || n == 19) return true;
    if (n % 3 == 0 || n % 5 == 0 || n % 7 == 0 || n % 11 == 0 || n % 13 == 0 || n % 17 == 0 || n % 19 == 0) return false;

    uint8_t b[5] = {2, 3, 5, 7, 11};
    if (n >= 500000 && n <= 4294967295){
        for (uint8_t  i = 0; i < 5; i++){
            if (!solovay_strassen(n, b[i])) return false;
        }
    } else if (n >= 100000 && n <= 4294967295){
        for (uint8_t  i = 0; i < 3; i++){
            if (!solovay_strassen(n, b[i])) return false;
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