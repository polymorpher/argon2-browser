//
// Created by Aaron Li on 8/7/21.
//
#include "argon2_library.h"

static uint64_t rdtsc(void) {
#ifdef _WIN32
    return __rdtsc();
#else
#if defined(__amd64__) || defined(__x86_64__)
    uint64_t rax, rdx;
    __asm__ __volatile__("rdtsc" : "=a"(rax), "=d"(rdx) : :);
    return (rdx << 32) | rax;
#elif defined(__i386__) || defined(__i386) || defined(__X86__)
    uint64_t rax;
    __asm__ __volatile__("rdtsc" : "=A"(rax) : :);
    return rax;
#else
#error "Not implemented!"
#endif
#endif
}

int main(int argc, char *argv[]) {
    uint32_t t_cost = 1;
    uint32_t m_cost = 8;
    uint32_t parallelism = 1;
    size_t pwdlen = 32;
    size_t hashlen = 32;
    uint32_t numpwd = 100000;
    unsigned char *pwd_array = malloc(numpwd * pwdlen);
    unsigned char salt_array[pwdlen];

    memset(pwd_array, 0, pwdlen * numpwd);
    memset(salt_array, 1, pwdlen);

    unsigned char *hash = malloc(numpwd * hashlen);
//    argon2_hash_ext(const uint32_t t_cost, const uint32_t m_cost,
//                        const uint32_t parallelism, const void *pwd, const uint32_t numpwd,
//                        const size_t pwdlen, const void *salt, const size_t saltlen,
//                        void *hash, const size_t hashlen, char *encoded,
//                        const size_t encodedlen, argon2_type type,
//
//                        const void *secret, const size_t secretlen,
//                        const void *ad, const size_t adlen,
//
//                        const uint32_t version);

    double run_time = 0;
    clock_t start_time, stop_time;
    uint64_t start_cycles, stop_cycles;
    uint64_t delta;
    double mcycles;

    start_time = clock();
    start_cycles = rdtsc();

    int result = argon2_hash_ext(t_cost, m_cost,
                                 parallelism, pwd_array, numpwd,
                                 pwdlen, salt_array, pwdlen,
                                 hash, hashlen, NULL,
                                 0, Argon2_d,

                                 NULL, 0,
                                 NULL, 0,

                                 ARGON2_VERSION_NUMBER);

//    int result = argon2_fast_hash_ext(t_cost, m_cost,
//                                 parallelism, pwd_array, numpwd,
//                                 pwdlen, salt_array, pwdlen,
//                                 hash, hashlen, NULL,
//                                 0, Argon2_d);

    if (result != ARGON2_OK) {
        printf("Error: %d\n", result);
        exit(result);
    }
    printf("Result: %d\n", result);

    stop_cycles = rdtsc();
    stop_time = clock();
    delta = (stop_cycles - start_cycles) / (m_cost);
    mcycles = (double) (stop_cycles - start_cycles) / (1UL << 20);
    run_time += ((double) stop_time - start_time) / (CLOCKS_PER_SEC);

    printf("%d %s, %d iterations, mem %d KiB, %d threads:  %2.2f cpb %2.2f "
           "Mcycles \n", numpwd, argon2_type2string(Argon2_d, 1), t_cost,
           m_cost, 1, (float) delta / 1024, mcycles);
    printf("%2.4f seconds\n\n", run_time);

}