//
// Created by Aaron Li on 8/7/21.
//

#ifndef ARGON2_BROWSER_ARGON2_LIBRARY_H
#define ARGON2_BROWSER_ARGON2_LIBRARY_H

#include "../argon2/include/argon2.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int argon2_fast_hash_ext(const uint32_t t_cost, const uint32_t m_cost,
                         const uint32_t parallelism, const void *pwd, const uint32_t numpwd,
                         const size_t pwdlen, const void *salt, const size_t saltlen,
                         void *hash, const size_t hashlen, char *encoded,
                         const size_t encodedlen, argon2_type type);

int argon2_hash_ext(const uint32_t t_cost, const uint32_t m_cost,
                    const uint32_t parallelism, const void *pwd, const uint32_t numpwd,
                    const size_t pwdlen, const void *salt, const size_t saltlen,
                    void *hash, const size_t hashlen, char *encoded,
                    const size_t encodedlen, argon2_type type,

                    const void *secret, const size_t secretlen,
                    const void *ad, const size_t adlen,

                    const uint32_t version);

int argon2_verify_ext(const char *encoded, const void *pwd, const size_t pwdlen,

                      const void *secret, const size_t secretlen,
                      const void *ad, const size_t adlen,

                      argon2_type type);


#endif //ARGON2_BROWSER_ARGON2_LIBRARY_H
