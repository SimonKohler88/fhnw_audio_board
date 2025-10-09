//
// Created by skohl on 06.10.2025.
//

#include "app_main.h"
#include "fonts.h"
#include "ssd1306.h"
#include "tlv_control.h"

TLV_CTRL_t tlv_ctrl;

void setup( void )
{
    SSD1306_Init();
    SSD1306_DrawRectangle( 0, 0, 101, 63, SSD1306_COLOR_WHITE );
    SSD1306_GotoXY( 10, 5 );
    SSD1306_Puts( "FU", &Font_16x26, SSD1306_COLOR_WHITE );
    SSD1306_UpdateScreen();

    tlv_ctrl_init( &tlv_ctrl );
}

void mainloop( void )
{
    // HAL_GPIO_TogglePin( GPIOB, GPIO_PIN_3 );
    // HAL_Delay( 100 );
}

void process_data( int16_t* saiRxBuffer, int16_t* saiTxBuffer )
{
    HAL_GPIO_TogglePin( GPIOB, GPIO_PIN_3 );
    uint16_t index1, index2;
    static int16_t inputSignalLeft[ BUFFER_SIZE ], inputSignalRight[ BUFFER_SIZE ];
    static int16_t outputSignalLeft[ BUFFER_SIZE ], outputSignalRight[ BUFFER_SIZE ];
    // copy RxBuffer to leftSignalBuffer and rightSignalBuffer
    for ( index1 = 0, index2 = 0; index1 < BUFFER_SIZE; index1++ )
    {
        inputSignalLeft[ index1 ]  = saiRxBuffer[ index2++ ];
        inputSignalRight[ index1 ] = saiRxBuffer[ index2++ ];
    }
    // Here, the data of inputSignalLeft[] and inputSignalRight[] can be processed
    // The result should be stored in outputSignalLeft[] and outpuSignalRight[].
    // Note that the arrays contain BUFFER_SIZE values each


    for ( index1 = 0; index1 < BUFFER_SIZE; index1++ )
    {
        outputSignalLeft[ index1 ] = inputSignalLeft[ index1 ];
        outputSignalRight[ index1 ] = inputSignalRight[ index1 ];
    }

    // copy left and right txBuffer into TxBuffer
    for ( index1 = 0, index2 = 0; index1 < BUFFER_SIZE; index1++ )
    {
        saiTxBuffer[ index2++ ] = outputSignalLeft[ index1 ];
        saiTxBuffer[ index2++ ] = outputSignalRight[ index1 ];
    }
}
