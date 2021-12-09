#ifndef KEYPAIR_H
#define KEYPAIR_H

#include "../ref/params.h"

#define CRYPTO_PUBLICKEYBYTES_B64 ((CRYPTO_PUBLICKEYBYTES + 2) / 3 * 4) + 1
#define CRYPTO_SECRETKEYBYTES_B64 ((CRYPTO_SECRETKEYBYTES + 2) / 3 * 4) + 1
#define CRYPTO_SHAKEBYTES 32
#define CRYPTO_SHAKEBYTES_B64 ((CRYPTO_SHAKEBYTES + 2) / 3 * 4) + 1
#define CRYPTO_BYTES_B64 ((CRYPTO_BYTES + 2) / 3 * 4) + 1

struct Keypair
{
    char kty[8]; //key type
    char alg[8]; //algorithm
    char pset[8]; // parameter set
    char xs[CRYPTO_SHAKEBYTES_B64]; // shake256 of pk
    char ds[CRYPTO_SHAKEBYTES_B64]; // shake256 of sk
    char x[CRYPTO_PUBLICKEYBYTES_B64];  // public key itself
    char d[CRYPTO_SECRETKEYBYTES_B64];  // secret key itself
};
int keypairToString(char* keypairString, struct Keypair keypair);

#endif
