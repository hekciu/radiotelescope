
#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

#define BIT(i) (1UL << (i))
#define IS_FLAG_SET(reg, i) (((reg) & BIT(i)) >> i == 1)

#endif
