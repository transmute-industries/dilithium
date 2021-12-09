#include "keypair.h"
#include <stdio.h>

int keypairToString(char *keypairString, struct Keypair keypair)
{
    sprintf(keypairString,
            "{\n"
                "\t\"kty\": \"PQK\",\n"
                "\t\"alg\": \"DICRY\",\n"
                "\t\"xs\":\"%s\",\n"
                "\t\"ds\":\"%s\",\n"
                "\t\"x\":\"%s\",\n"
                "\t\"d\":\"%s\"\n}"
            "\n",
            keypair.pks, keypair.sks,
            keypair.pk, keypair.sk);
    return 0;
}