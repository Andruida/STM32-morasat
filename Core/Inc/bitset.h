#ifndef BITSET_H
#define BITSET_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#define bitset(b) bitset_ ## b

typedef struct bitset {
    size_t size;
    uint8_t *data;
} bitset;

typedef bitset bitset_1;
typedef bitset bitset_4;
typedef bitset bitset_7;
typedef bitset bitset_8;
typedef bitset bitset_32;
typedef bitset bitset_112;
typedef bitset bitset_144;
typedef bitset bitset_256;

bitset* bitset_alloc(size_t size);
void bitset_free(bitset* b);
bitset* bitset_from_bitstring(char* str);
bitset* bitset_from_bytes(uint8_t* bytes, size_t bytes_len);

void bitset_to_bytes(bitset* b, uint8_t* bytes);
void bitset_to_bitstring(bitset* b, char* str);


void bitset_copy(bitset* b, bitset* dst);
bitset* bitset_clone(bitset* b);
bool bitset_get(bitset* b, size_t index);
void bitset_set(bitset* b, size_t index, bool value);
size_t bitset_size(bitset* b);
size_t bitset_size_in_bytes(bitset* b);

bool bitset_eq(bitset* a, bitset* b);
void bitset_reset(bitset* b);

#ifdef PC_DEBUG
void bitset_print_debug_info(bitset* b);
#endif

// Nice to have, but not necessary now:

// bool bitset_all(bitset* b);
// bool bitset_any(bitset* b);
// bool bitset_none(bitset* b);

// int bitset_count(bitset* b);

// bool bitset_neq(bitset* a, bitset* b);

// void bitset_and(bitset* a, bitset* b);
// void bitset_or(bitset* a, bitset* b);
// void bitset_xor(bitset* a, bitset* b);
// void bitset_not(bitset* b);

// void bitset_set_and(bitset* a, size_t index, bool value);
// void bitset_set_or(bitset* a, size_t index, bool value);
// void bitset_set_xor(bitset* a, size_t index, bool value);
// void bitset_set_not(bitset* a, size_t index);


// void bitset_shl(bitset* b, size_t n);
// void bitset_shr(bitset* b, size_t n);

#endif // BITSET_H