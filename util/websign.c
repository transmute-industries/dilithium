#include "../ref/params.h"
#include "../ref/sign.h"
#include "../ref/randombytes.h"
#include "base64.h"
#include "websign.h"

#include <emscripten.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

EMSCRIPTEN_KEEPALIVE
int main(void)
{
    struct Keypair keys;
    keys = generate();
    printf("\"keypair\": {\n\t\"x\":\"%s\",\n\t\"d\":\"%s\"\n}\n", keys.pk, keys.sk);
    return 0;
}

EMSCRIPTEN_KEEPALIVE
int version(void) {
    return 1;
}

EMSCRIPTEN_KEEPALIVE
struct Keypair generate(void)
{
    struct Keypair keys;
    const uint8_t pk[pqcrystals_dilithium2_PUBLICKEYBYTES];
    uint8_t sk[pqcrystals_dilithium2_SECRETKEYBYTES];
    int ret = 0;
    
    ret = crypto_sign_keypair(pk, sk);
    if (ret == 0)
    {
        Base64encode(keys.pk, (const char*) pk, Base64encode_len(strlen((const char*) pk)));
        Base64encode(keys.sk, (const char*) sk, Base64encode_len(strlen((const char*) sk)));
    }
    else
    {
        strcpy(keys.pk, "ERROR");
        strcpy(keys.sk, "ERROR");
    }

    return keys;
}

EMSCRIPTEN_KEEPALIVE
char *sign(char *sm, const char *m, const char *sk)
{
    size_t siglen = CRYPTO_BYTES; 
    size_t mlen = sizeof(m);
    const uint8_t sig[CRYPTO_BYTES];
    char* sig_e = "";
    int ret = 0;

    ret = crypto_sign_signature(sig, siglen, m, mlen, sk);
    Base64encode(sig_e, sig, Base64encode_len(strlen((const char*) sig)));
    return sig_e;
}

EMSCRIPTEN_KEEPALIVE
int verify(const char *sig, const char *m, const char *pk)
{
    size_t siglen = CRYPTO_BYTES;
    size_t mlen = sizeof(m);
    uint8_t* sig_d = (uint8_t *) malloc(sizeof(sig));
    uint8_t* m_d = (uint8_t *) malloc(4096);
    uint8_t* pk_d = (uint8_t *) malloc(pqcrystals_dilithium2_PUBLICKEYBYTES);
    int ret, sig_err, m_err, pk_err = 0;
    
    sig_err = Base64decode(sig_d, sig); 
    m_err = Base64decode(m_d, m); 
    pk_err = Base64decode(pk_d, pk);

    ret = crypto_sign_verify(sig, siglen, m, mlen, pk);
    return ret + sig_err + m_err + pk_err;
}