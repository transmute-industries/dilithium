#include "params.h"
#include "sign.h"
//#include "base64.h"
#include "cli.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
    // printf("Generating...\n");
    struct Keypair keys;
    keys = generate();
//  printf("{\n\t\"p\":%s,\n\t\"s\":%s\n}\n", base64_encode_openssl(keys.pk, pqcrystals_dilithium2_PUBLICKEYBYTES), base64_encode_openssl(keys.sk, pqcrystals_dilithium2_SECRETKEYBYTES));
    printf("%s", (char*)keys.sk);
    printf("\n");
    printf("%s", (char*)keys.pk);
    printf("\n");
    return 1;
}

int version(void)
{
    return 1;
}

struct Keypair generate(void)
{
    struct Keypair keys;
    const uint8_t pk[pqcrystals_dilithium2_PUBLICKEYBYTES];
    const uint8_t sk[pqcrystals_dilithium2_SECRETKEYBYTES];

    int ret = crypto_sign_keypair(pk, sk);
    if (ret == 0)
    {
        printf("SUCCESS: %d\n", ret);
        printf("%A\n%A\n", (char*)pk, (char*)sk);
        memcpy(keys.pk, pk, pqcrystals_dilithium2_PUBLICKEYBYTES);
        memcpy(keys.sk, sk, pqcrystals_dilithium2_SECRETKEYBYTES);
    }
    else
    {
        printf("ERROR: %d\n", ret);
        memcpy(keys.pk, ERR_VAL_PK, pqcrystals_dilithium2_PUBLICKEYBYTES);
        memcpy(keys.sk, ERR_VAL_SK, pqcrystals_dilithium2_SECRETKEYBYTES);
    }

    return keys;
}

uint8_t *sign(uint8_t *sm, const uint8_t *m, const uint8_t *sk)
{
    size_t siglen, mlen;
    const uint8_t sig[CRYPTO_BYTES];

    int ret = crypto_sign_signature(*sig, siglen, *m, mlen, *sk);
    return sig;
}

int verify(const uint8_t *sig, const uint8_t *m, const uint8_t *pk)
{
    size_t siglen, mlen;

    int ret = crypto_sign_verify(*sig, siglen, *m, mlen, *pk);
    return ret;
}
