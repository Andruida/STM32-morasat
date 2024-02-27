#include "bitset.h"
#include <string.h>
#ifdef PC_DEBUG
#include <stdio.h>
#endif

#define BITSET_POOL_SIZE 6

static bitset bitset_pool_usage = {.size = BITSET_POOL_SIZE, .data = (uint8_t[(BITSET_POOL_SIZE+7)/8]){0}};

static bitset bitset_pool[BITSET_POOL_SIZE] = {
    {.size = 4,.data = (uint8_t[1]){0}},
    {.size = 7,.data = (uint8_t[1]){0}},
    {.size = 7,.data = (uint8_t[1]){0}},
    {.size = 144,.data = (uint8_t[18]){0}},
    {.size = 256,.data = (uint8_t[32]){0}},
    {.size = 256,.data = (uint8_t[32]){0}},  
};

bitset* bitset_alloc(size_t size) {
    for (uint8_t i = 0; i < BITSET_POOL_SIZE; i++) {
        if (bitset_get(&bitset_pool_usage, i) == false && bitset_pool[i].size == size) {
            bitset_set(&bitset_pool_usage, i, true);
            bitset* b = &(bitset_pool[i]);
            bitset_reset(b);
            return b;
        }
    }
    // bitset* b = malloc(sizeof(bitset));
    // b->size = size;
    // b->data = calloc(bitset_size_in_bytes(b), sizeof(uint8_t));
    // return b;
    return NULL;
}

void bitset_free(bitset* b) {
    for (uint8_t i = 0; i < BITSET_POOL_SIZE; i++) {
        if (b == &bitset_pool[i]) {
            bitset_set(&bitset_pool_usage, i, false);
            return;
        }
    }
    // free(b->data);
    // free(b);
}

size_t bitset_size(bitset* b) {
    return b->size;
}

size_t bitset_size_in_bytes(bitset* b) {
    return (b->size + 7) / 8;
}

bool bitset_get(bitset* b, size_t index) {
    if (index >= b->size) { // out of bounds handling
        #ifdef PC_DEBUG
        printf("out of bounds, index: %lu, size: %lu\n", index, b->size);
        #endif
        return false; // bad
    }
    return (b->data[index / 8] >> (index % 8)) & 1;
}

void bitset_set(bitset* b, size_t index, bool value) {
    if (index >= b->size) { // out of bounds handling
        #ifdef PC_DEBUG
        printf("out of bounds, index: %lu, size: %lu\n", index, b->size);
        #endif
        return; // bad
    }
    if (value) {
        b->data[index / 8] |= 1 << (index % 8);
    } else {
        b->data[index / 8] &= ~(1 << (index % 8));
    }
}


bitset* bitset_from_bitstring(char* str) {
    bitset* b = bitset_alloc(strlen(str));
    for (size_t i = 0; i < b->size; i++) {
        if (str[i] == '1') {
            bitset_set(b, b->size - (i+1), true);
        }
    }
    return b;
}

// LSB first
bitset* bitset_from_bytes(uint8_t* bytes, size_t size) {
    bitset* b = bitset_alloc(size * 8);
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < 8; j++) { // LSB first
            bitset_set(b, i * 8 + j, (bytes[i] >> j) & 1);
        }
    }
    return b;
}

// LSB first
void bitset_to_bytes(bitset* b, uint8_t* bytes) {
    for (size_t i = 0; i < bitset_size_in_bytes(b); i++) {
        bytes[i] = 0;
        for (size_t j = 0; j < 8; j++) { // LSB first
            bytes[i] |= bitset_get(b, i * 8 + j) << j;
        }
    }
}

void bitset_to_bitstring(bitset* b, char* str) {
    for (size_t i = 0; i < b->size; i++) {
        str[i] = bitset_get(b, b->size - (i+1)) ? '1' : '0';
    }
    str[b->size] = '\0';
}

void bitset_copy(bitset* b, bitset* dst) {
    if (dst->size != b->size) {
        //free(dst->data);
        // dst->data = calloc(bitset_size_in_bytes(b), sizeof(uint8_t));
        // dst->size = b->size;
        return;
    }
    memcpy(dst->data, b->data, bitset_size_in_bytes(b));
}

bitset* bitset_clone(bitset* b) {
    bitset* other = bitset_alloc(b->size);
    other->size = b->size;
    memcpy(other->data, b->data, bitset_size_in_bytes(b));
    return other;
}

bool bitset_eq(bitset* a, bitset* b) {
    if (a->size != b->size) {
        return false;
    }
    for (size_t i = 0; i < bitset_size_in_bytes(a); i++) {
        if (a->data[i] != b->data[i]) {
            return false;
        }
    }
    return true;
    // return memcmp(a->data, b->data, bitset_size_in_bytes(a)) == 0;
}

void bitset_reset(bitset* b) {
    memset(b->data, 0, bitset_size_in_bytes(b));
    // for (size_t i = 0; i < bitset_size_in_bytes(b); i++) {
    //     b->data[i] = 0;
    // }
}

#ifdef PC_DEBUG
void bitset_print_debug_info(bitset* b) {
    printf("bitset size: %lu\n", b->size);
    printf("{");
    for (int i = 0; i < bitset_size_in_bytes(b); i++) {
        printf("%d, ", b->data[i]);
    }
    printf("}\n");
}
#endif