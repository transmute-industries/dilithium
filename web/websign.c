#include "emscripten.h"
#include "params.h"
#include "sign.h"
#include "websign.h"
#include "randombytes.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

EMSCRIPTEN_KEEPALIVE
int version(void) {
    return 1;
}

EMSCRIPTEN_KEEPALIVE
struct keypair generate(void) {
    struct keypair keys;
    const uint8_t pk[pqcrystals_dilithium2_PUBLICKEYBYTES];
    const uint8_t sk[pqcrystals_dilithium2_SECRETKEYBYTES];

    int ret = crypto_sign_keypair(pk, sk);
    if (ret == 0) {
        memcpy(keys.pk, pk, pqcrystals_dilithium2_PUBLICKEYBYTES);
        memcpy(keys.sk, sk, pqcrystals_dilithium2_SECRETKEYBYTES);
    } else {
        memcpy(keys.pk, ERR_VAL_PK, pqcrystals_dilithium2_PUBLICKEYBYTES);
        memcpy(keys.sk, ERR_VAL_SK, pqcrystals_dilithium2_SECRETKEYBYTES);
    }

    return keys;
}

EMSCRIPTEN_KEEPALIVE
uint8_t* sign(uint8_t *sm, const uint8_t *m, const uint8_t *sk) {
    size_t siglen, mlen;
    const uint8_t sig[CRYPTO_BYTES];
    
    int ret = crypto_sign_signature(*sig, siglen, *m, mlen, *sk);
    return sig;
}

EMSCRIPTEN_KEEPALIVE
int verify(const uint8_t *sig, const uint8_t *m, const uint8_t *pk) {
    size_t siglen, mlen;
    
    int ret = crypto_sign_verify(*sig, siglen, *m, mlen, *pk);
    return ret;
}
