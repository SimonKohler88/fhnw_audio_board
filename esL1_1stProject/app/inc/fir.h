//
// Created by skohl on 13.10.2025.
//

#ifndef ESL1_1STPROJECT_FIR_H
#define ESL1_1STPROJECT_FIR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "app_main.h"
#include "stdint.h"
#define NTAPS 100
    const int16_t coefficients[ 100 ] = {
        11,   24,   9,    11,   -4,   -17,  -31,  -36,  -31,  -13,  15,   45,    67,    72,    53,
        11,   -45,  -97,  -129, -124, -76,  7,    105,  187,  223,  193,  92,    -58,   -217,  -335,
        -366, -281, -88,  172,  427,  593,  597,  403,  31,   -441, -885, -1151, -1100, -647,  218,
        1410, 2766, 4070, 5096, 5661, 5661, 5096, 4070, 2766, 1410, 218,  -647,  -1100, -1151, -885,
        -441, 31,   403,  597,  593,  427,  172,  -88,  -281, -366, -335, -217,  -58,   92,    193,
        223,  187,  105,  7,    -76,  -124, -129, -97,  -45,  11,   53,   72,    67,    45,    15,
        -13,  -31,  -36,  -31,  -17,  -4,   11,   9,    24,   11 };


    int16_t filterState[NTAPS + BUFFER_SIZE - 1];

#ifdef __cplusplus
}
#endif
#endif  // ESL1_1STPROJECT_FIR_H
