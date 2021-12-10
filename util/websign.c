#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "../ref/params.h"
#include "common.h"
#include "keypair.h"
#include "uapi.h"

int dilithiumVersion(void) {
    return API_VERSION;
}

char* dilithiumGenerate(void)
{
    struct Keypair keys;
    static char keysString[CRYPTO_SECRETKEYBYTES_B64 + CRYPTO_PUBLICKEYBYTES_B64 + (CRYPTO_BYTES_B64 * 2) + 64];
    int generate_return = 0;

    generate_return = generate(&keys);
    keypairToString(keysString, keys);
    return keysString;
}

char* dilithiumSign(char *sm, const char *m, const char *sk)
{
    return "";
}

int dilithiumVerify(const char *sig, const char *m, const char *pk)
{
    return "";
}