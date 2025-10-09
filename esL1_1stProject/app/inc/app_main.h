//
// Created by skohl on 06.10.2025.
//

#ifndef ESL1_1STPROJECT_APP_MAIN_H
#define ESL1_1STPROJECT_APP_MAIN_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"
#define BUFFER_SIZE 256
#define SAI_BUF_LEN ( 4 * BUFFER_SIZE )

    void setup( void );
    void mainloop( void );

    void process_data( int16_t* saiRxBuffer, int16_t* saiTxBuffer );

#ifdef __cplusplus
}
#endif
#endif  // ESL1_1STPROJECT_APP_MAIN_H