
/**
 * https://github.com/aappleby/smhasher/blob/master/src/MurmurHash3.h
 *
 */
#ifndef DATASTRUCTURE_HASH_H
#define DATASTRUCTURE_HASH_H

#include <stdint.h> // include uint32_t add etc.

void murmurHash_32(const void * key, int len, uint32_t seed, void* out);

void murmurHash_x86_128(const void* key, int len, uint32_t seed, void* out);

void murmurHash_x64_128(const void* key, int len, uint32_t seed, void* out);

#endif //DATASTRUCTURE_HASH_H
