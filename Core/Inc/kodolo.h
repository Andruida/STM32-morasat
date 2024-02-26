#ifndef KODOLO_H
#define KODOLO_H

#include "bitset.h"

/** Bekéri az eredeti 144-es bitsort és visszadja a 256-os kódolt bitsort
 * @param bit_in a 144 bites bemeneti bitsor
 * @param bit_out a 256 bites kódolt kimeneti bitsor
 */
void kodolo_encode(bitset(144)* bit_in, bitset(256)* bit_out);

/** Bekéri a 256-os kódolt bitsort és visszadja a 144-es eredeti/javított bitsort
 * @param bit_in a 256 bites kódolt bemeneti bitsor
 * @param res_bit a 144 bites eredeti kimeneti bitsor
 */
void kodolo_decode(bitset(256) * bit_in, bitset(144) * res_bit);


/**
 * Bekéri a kódolandó adatsort és hibajavított és kódolt adatsort.
 * @param bytes_in a kódolandó adatsor (18 bájt)
 * @param bytes_out a kódolt adatsor (32 bájt)
*/
void kodolo_encode_bytes(uint8_t* bytes_in, uint8_t* bytes_out);

/**
 * Bekéri a kódolt adatsort és visszadja az eredeti/javított adatot.
 * @param bytes_in a fogadott (sérült) adatsor (32 bájt)
 * @param bytes_out a javított adatsor (18 bájt)
 */
void kodolo_decode_bytes(uint8_t* bytes_in, uint8_t* bytes_out);

#endif // KODOLO_H
