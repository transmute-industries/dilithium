#ifndef API_H
#define API_H

#define API_VERSION 1

static const bool DEBUG = false;
static const bool VERBOSE = false;
static const bool VDEBUG = DEBUG && VERBOSE;

int version(void);
int generate(struct Keypair *keypair);
int sign(char *sm, const char *m, const char *sk);
int verify(const char *sig, const char *m, const char *pk);

#endif
