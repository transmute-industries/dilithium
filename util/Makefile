CC ?= /usr/bin/cc
CFLAGS += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
  -Wshadow -Wvla -Wpointer-arith -O3 -fomit-frame-pointer 
CFLAGS += -Wdeprecated 
DDILITHIUM_MODE = -DDILITHIUM_MODE=3
NISTFLAGS += -Wno-unused-result -O3 -fomit-frame-pointer
SOURCES = ../ref/sign.c ../ref/packing.c ../ref/polyvec.c ../ref/poly.c ../ref/ntt.c \
  ../ref/reduce.c ../ref/rounding.c ../ref/randombytes.c \
  base64.c keypair.c uapi.c
HEADERS = ../ref/config.h ../ref/params.h ../ref/api.h ../ref/sign.h ../ref/packing.h \
  ../ref/polyvec.h ../ref/poly.h ../ref/ntt.h \
  ../ref/reduce.h ../ref/rounding.h ../ref/symmetric.h ../ref/randombytes.h \
  common.h base64.h keypair.h uapi.h

KECCAK_SOURCES = $(SOURCES) ../ref/fips202.c ../ref/symmetric-shake.c
KECCAK_HEADERS = $(HEADERS) ../ref/fips202.h

AES_SOURCES = $(SOURCES) ../ref/fips202.c ../ref/aes256ctr.c ../ref/symmetric-aes.c
AES_HEADERS = $(HEADERS) ../ref/fips202.h ../ref/aes256ctr.h

WEBASM_COMPILER ?= emcc
WEBASM_EXPORTS = _dilithiumGenerate, _dilithiumSign, _dilithiumVerify, _dilithiumVersion, _malloc
WEBASM_FLAGS ?= -O3 -s WASM=1 \
  -D DILITHIUM_MODE=3 \
  -s EXPORTED_FUNCTIONS="[$(WEBASM_EXPORTS)]"

WEBASM_SOURCES = websign.c $(KECCAK_SOURCES)
WASM_HEADERS = -I ../ref/config.h -I ../ref/params.h -I ../ref/api.h -I ../ref/sign.h -I ../ref/packing.h \
  -I ../ref/polyvec.h -I ../ref/poly.h -I ../ref/ntt.h \
  -I ../ref/reduce.h -I ../ref/rounding.h -I ../ref/symmetric.h -I ../ref/randombytes.h -I ../ref/fips202.h \
  -I common.h -I base64.h -I keypair.h -I uapi.h 
WEBASM_OUTPUT = dilithium.html

# base64.c
CLI_SOURCES = cli.c $(KECCAK_SOURCES)
CLI_OUTPUT = dilithium

.PHONY: all clean cli

all: \
   cli \
   web

web: $(WEBASM_SOURCES)
	$(WEBASM_COMPILER) $(WEBASM_SOURCES) $(WASM_HEADERS) \
	$(WEBASM_FLAGS) \
	-o $(WEBASM_OUTPUT)
	
cli: \
	cli_generate

cli_generate: $(CLI_SOURCES) $(HEADERS) 
	$(CC) \
	-fPIC $(CFLAGS) $(DILITHIUM_MODE) \
	-o $(CLI_OUTPUT) $(CLI_SOURCES)


release:
	cp -v wasm_test.html ../docs/index.html
	cp -v dilithium.js ../docs/
	cp -v dilithium.wasm ../docs/

clean:
	rm -f *.gcno *.gcda *.lcov
	rm -f dilithium
	rm -f dilithium.wasm
	rm -f dilithium.wasm.map
	rm -f dilithium.html
	rm -f dilithium.js