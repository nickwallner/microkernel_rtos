#ifndef COMMON_H_
#define COMMON_H_

#include <stddef.h>
#include <stdint.h>

/* macros */
#define UNUSED(x) (void)(x);

#define BIT(x)                   (1UL << (x)) // get a bitfield with only bit x set
#define IS_BIT_SET(reg, bit_num) ((reg & BIT(bit_num)) == BIT(bit_num)) // check if a bit is set in a register

#define SET_BIT(reg, bit_num)   (reg |= BIT(bit_num)) // set a bit in a register
#define RESET_BIT(reg, bit_num) (reg &= ~(1UL << BIT(bit_num))) // reset a bit in a register

#define BITMASK8(x)  ((uint8_t)(1UL << (x)))  // get an 8-bit bitmask with bit x set
#define BITMASK16(x) ((uint16_t)(1UL << (x))) // get a 16-bit bitmask with bit x set
#define BITMASK32(x) ((uint32_t)(1UL << (x))) // get a 32-bit bitmask with bit x set

#endif // COMMON_H_