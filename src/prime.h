#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <intrin.h>
#include <math.h>

//Your L1d cache size here:
#define CACHE_SIZE 48000

#define SEGM_SIZE (CACHE_SIZE * 2 / 3)


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
    return 2 * i + 3;
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

    unsigned long long size = get_prime_array_bound(n) >> 1;

    unsigned int ubound = isqrt(size << 1);

    uint8_t *segment;
    size_t *primes;
    size_t *next;
    size_t len = 0;

    segment = (uint8_t *)calloc(SEGM_SIZE, 1);
    primes = (unsigned long long *)calloc(ubound >> 1, sizeof(unsigned long long));
    next = (unsigned long long *)calloc(ubound >> 1, sizeof(unsigned long long));

    if (segment == NULL) return 1;
    if (primes == NULL) return 1;
    if (next == NULL) return 1;
    
    for(size_t s = 0; s < (size >> 3) / SEGM_SIZE + 1; s++){
        if (s > 0) {
            memset(segment, 0, SEGM_SIZE);
            for (size_t i = 0; i < len; i++) {
                size_t p = primes[i];

                if (p >= 4294967296) continue;

                size_t start = next[i];

                size_t t = s * (SEGM_SIZE << 3);

                size_t j = start - t;
                while (j < SEGM_SIZE << 3) {
                    set(j, segment);
                    j += p;
                }
                next[i] = j + t;
            }
        }

        for(size_t i = 0; i < SEGM_SIZE << 3; i++){
            if (read(i, segment)) continue;

            c++;

            size_t t = s * (SEGM_SIZE << 3);

            if (c == n){
                free(segment);
                free(primes);
                free(next);
                return get_number(i + t);
            }

            size_t p = get_number(i + t);

            if (p > ubound) continue;

            if (p >= 4294967296) continue;

            size_t start = (p * p - 3) / 2;

            size_t j = start - t;
            while (j < SEGM_SIZE << 3) {
                set(j, segment);
                j += p;
            }

            primes[len] = p;
            next[len] = j + t;
            len++;
        }
    }

    free(segment);
    free(primes);
    free(next);

    return 1;
}