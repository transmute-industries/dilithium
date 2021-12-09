#ifndef WEBSIGN_H
#define WEBSIGN_H

#include "../ref/params.h"

#include <stddef.h>
#include <stdint.h>

#define pqcrystals_dilithium2_PUBLICKEYBYTES 1312
#define pqcrystals_dilithium2_SECRETKEYBYTES 2528
#define pqcrystals_dilithium2_BYTES 2420

const uint8_t ERR_VAL_PK[pqcrystals_dilithium2_PUBLICKEYBYTES] = {0, 1, 0, 1}; 
const uint8_t ERR_VAL_SK[pqcrystals_dilithium2_SECRETKEYBYTES] = {0, 1, 0, 1}; 

struct Keypair
{
    char *pk[1750];
    char *sk[1896];
};

int version(void);
struct Keypair generate(void);
char* sign(char *sm, const char *m, const char *sk);
int verify(const char *sig, const char *m, const char *pk);

#endif
