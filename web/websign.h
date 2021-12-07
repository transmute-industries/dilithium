#ifndef WEBSIGN_H
#define WEBSIGN_H

#include "params.h"
#include "sign.h"

#include <stddef.h>
#include <stdint.h>

#define pqcrystals_dilithium2_PUBLICKEYBYTES 1312
#define pqcrystals_dilithium2_SECRETKEYBYTES 2528
#define pqcrystals_dilithium2_BYTES 2420

const uint8_t ERR_VAL_PK[pqcrystals_dilithium2_PUBLICKEYBYTES] = {0, 1, 0, 1}; 
const uint8_t ERR_VAL_SK[pqcrystals_dilithium2_SECRETKEYBYTES] = {0, 1, 0, 1}; 

struct keypair
{
    uint8_t pk[pqcrystals_dilithium2_PUBLICKEYBYTES];
    uint8_t sk[pqcrystals_dilithium2_SECRETKEYBYTES];
};

int version(void);
struct keypair generate(void);
uint8_t* sign(uint8_t *sm, const uint8_t *m, const uint8_t *sk);
int verify(const uint8_t *sig, const uint8_t *m, const uint8_t *pk);

#endif
