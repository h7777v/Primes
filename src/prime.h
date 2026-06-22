#include <stdbool.h>
#include <stdint.h>
#include <intrin.h>
#include <math.h>

inline unsigned long long isqrt(unsigned long long x) {
    if (x == 0) return 0;

    unsigned long long r = (unsigned long long)sqrt((double)x);

    if (r * r > x) r--;
    if (x - (r * r) >= (r * 2) + 1) r++;

    return r;
}

unsigned long long get_prime_array_bound(unsigned long long n) {
    if (n < 2) return 0;

    unsigned long long A = 64 - __builtin_clzll(n);
    unsigned long long B = 64 - __builtin_clzll(A);

    return (A + B) * n;
}

inline unsigned long long get_number(size_t i){
    return 2 * (i + 2) - 1;
}

static inline bool read(size_t i, uint8_t *restrict list) {
    return (list[i >> 3] >> (i & 7)) & 1;
}

static inline void set(size_t i, uint8_t *restrict list) {
    list[i >> 3] |= (1u << (i & 7));
}

unsigned long long getPrime(unsigned long long n){
    if (n == 0) return 1;
    if (n == 1) return 2;

    unsigned long long c = 1;

    unsigned long long size = (get_prime_array_bound(n) >> 1) + 1;

    unsigned int ubound = isqrt(size);

    uint8_t *list;

    list = (uint8_t *)calloc(size >> 3, 1);

    if (list == NULL) return 1;

    for(size_t i = 0;i < ubound;i++){
        if (read(i, list)) continue;

        c++;

        if (c == n){
            free(list);
            return get_number(i);
        }

        size_t p = 2 * i + 3;

        size_t start = (p * p - 3) / 2;

        for (size_t j = start; j < size; j += p) {
            set(j, list);
        }
    }

    size_t byte = ubound >> 3;
    size_t bit  = ubound & 7;

    for (; bit < 8; bit++) {
        if (!(list[byte] & (1u << bit))) {
            c++;

            if (c == n) {
                size_t idx = (byte << 3) + bit;
                free(list);
                return 2 * idx + 3;
            }
        }
    }

    for (size_t i = byte + 1; i < ((size + 7) >> 3); i++) {
        unsigned primes_in_byte = 8 - __builtin_popcount(list[i]);

        if (c + primes_in_byte < n) {
            c += primes_in_byte;
            continue;
        }

        for (unsigned b = 0; b < 8; b++) {
            size_t idx = (i << 3) + b;

            if (idx >= size)
                break;

            if (!(list[i] & (1u << b))) {
                c++;

                if (c == n) {
                    free(list);
                    return 2 * idx + 3;
                }
            }
        }
    }

    free(list);

    return 1;
}