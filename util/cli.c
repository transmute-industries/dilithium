// cli wrapper for the api
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "keypair.h"
#include "cli.h"
#include "api.h"

static const char *TEST_MESSAGE = "TESTING SIGNATURES";

int main(void)
{
    demo();

    return 0;
}

void demo(void)
{
    printf("Running quick key generation and signing demo...");
    if (DEBUG)
        printf("Entering cli:main\n");
    printf("CRYPTO_BYTES: %d\n\n", CRYPTO_BYTES);
    struct Keypair keys;
    char keysString[CRYPTO_SECRETKEYBYTES_B64 + CRYPTO_PUBLICKEYBYTES_B64 + (CRYPTO_BYTES_B64 * 2) + 64];
    char signed_message[CRYPTO_BYTES_B64];
    int signed_return = 0;
    int verify_return = 0;

    if (VDEBUG)
        printf("\tcli:main::initialized\n");

    if (VDEBUG)
        printf("\tcli:main::generating\n");
    generate(&keys);
    if (VDEBUG)
    {
        printf("\tcli:main::keys\n");
        printf("%s\n\n", keys.pks);
        printf("%s\n\n", keys.sks);
        printf("%s\n\n", keys.pk);
        printf("%s\n\n", keys.sk);
    }
    if (VDEBUG)
        printf("\tcli:main::keystostring\n");
    keypairToString(keysString, keys);
    if (VDEBUG)
    {
        printf("\tcli:main::printing\n");
    }
    
    printf("Generated Keypair: %s\n", keysString);
    
    printf("\nSigning: 'TESTING SIGNATURES'\n");
    signed_return = sign(signed_message, TEST_MESSAGE, (const char *)keys.sk);
    printf("\nSigned: 'TESTING SIGNATURES'\n");
    printf("Result: %d\n%s\n", signed_return, signed_message);

    verify_return = verify((const char *)signed_message, (const char *)TEST_MESSAGE, (const char *)keys.pk);
    printf("\nVerification Result: %d\n", verify_return);

    return;
}