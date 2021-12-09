CC ?= /usr/bin/cc
CFLAGS += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
  -Wshadow -Wvla -Wpointer-arith -O3 -fomit-frame-pointer 
CFLAGS += -Wdeprecated 
DDILITHIUM_MODE = -DDILITHIUM_MODE=3
NISTFLAGS += -Wno-unused-result -O3 -fomit-frame-pointer
SOURCES = ../ref/sign.c ../ref/packing.c ../ref/polyvec.c ../ref/poly.c ../ref/ntt.c \
  ../ref/reduce.c ../ref/rounding.c ../ref/randombytes.c \
  base64.c keypair.c api.c
HEADERS = ../ref/config.h ../ref/params.h ../ref/api.h ../ref/sign.h ../ref/packing.h \
  ../ref/polyvec.h ../ref/poly.h ../ref/ntt.h \
  ../ref/reduce.h ../ref/rounding.h ../ref/symmetric.h ../ref/randombytes.h \
  base64.h keypair.h api.h
KECCAK_SOURCES = $(SOURCES) ../ref/fips202.c ../ref/symmetric-shake.c
KECCAK_HEADERS = $(HEADERS) ../ref/fips202.h
AES_SOURCES = $(SOURCES) ../ref/fips202.c ../ref/aes256ctr.c ../ref/symmetric-aes.c
AES_HEADERS = $(HEADERS) ../ref/fips202.h ../ref/aes256ctr.h

WEBASM_COMPILER = emcc
# -s EXPORT_ALL=1 -s LINKABLE=1 may be desireable for some scenarios
WEBASM_FLAGS = --profiling-funcs --source-map-base -g4 -s WASM=1 -s ASSERTIONS=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0 \
  -s SAFE_HEAP=1 \
  -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]' \
  -s EXPORTED_FUNCTIONS="[_generate, _sign, _verify, _version, _main]"

WEBASM_SOURCES = websign.c
WEBASM_OUTPUT = dilithium.html

# base64.c
CLI_SOURCES = cli.c $(KECCAK_SOURCES)
CLI_OUTPUT = dilithium

.PHONY: all clean

all: \
  cli \
  web

web: $(SOURCES) $(HEADERS) $(WEBASM_SOURCES)
	$(WEBASM_COMPILER) $(WEBASM_FLAGS) \
		-I . $(WEBASM_SOURCES) $(KECCAK_SOURCES) -o $(WEBASM_OUTPUT)
	
cli: $(CLI_SOURCES) $(HEADERS) 
	$(CC) \
		-lssl -lcrypto \
		-fPIC $(CFLAGS) $(DILITHIUM_MODE) \
		-o $(CLI_OUTPUT) $(CLI_SOURCES)

clean:
	rm -f *.gcno *.gcda *.lcov
	rm -f dilithium
	rm -f dilithium.wasm
	rm -f dilithium.html
	rm -f dilithium.js