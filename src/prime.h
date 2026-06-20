#include <stdbool.h>
#include <stdint.h>
#include <intrin.h>
#include <math.h>

unsigned long long get_prime_array_bound(unsigned long long n) {
    if (n < 2) return 0;

    unsigned long long A = 64 - __builtin_clzll(n);
    unsigned long long B = 64 - __builtin_clzll(A);

    return (A + B) * n;
}

inline unsigned long long get_number(size_t i){
    return 2 * (i + 2) - 1;
}

static inline bool read(size_t i, uint8_t *list) {
    return (list[i >> 3] >> (i & 7)) & 1;
}

static inline void set(size_t i, uint8_t *list) {
    list[i >> 3] |= (1u << (i & 7));
}

unsigned long long getPrime(unsigned long long n){
    if (n == 0) return 1;
    if (n == 1) return 2;

    unsigned long long c = 1;

    unsigned long long size = (get_prime_array_bound(n) >> 1) + 1;

    uint8_t *list;

    list = (uint8_t *)calloc((size >> 3) + 1, 1);

    if (list == NULL) return 1;

    for(size_t i = 0;i < size;i++){
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

    free(list);

    return 1;
}