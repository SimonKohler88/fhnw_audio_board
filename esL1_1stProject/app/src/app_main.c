//
// Created by skohl on 06.10.2025.
//

#include "app_main.h"
#include "fonts.h"
#include "ssd1306.h"
#include "tlv_control.h"
#include "arm_math.h"
#include "fir.h"

#include <stdio.h>
#define N_PLOT 100

TLV_CTRL_t tlv_ctrl;

arm_fir_instance_q15 filter;
arm_rfft_fast_instance_f32 fft_instance;

float32_t inputFFT[BUFFER_SIZE];
float32_t outputFFT[BUFFER_SIZE];

float32_t magFFT[BUFFER_SIZE/2];

volatile uint8_t fft_data_request;

void setup( void )
{
    SSD1306_Init();
    SSD1306_DrawRectangle( 0, 0, 101, 63, SSD1306_COLOR_WHITE );
    // SSD1306_GotoXY( 10, 5 );
    // SSD1306_Puts( "FU", &Font_16x26, SSD1306_COLOR_WHITE );
    SSD1306_UpdateScreen();

    tlv_ctrl_init( &tlv_ctrl );

    arm_rfft_fast_init_f32(&fft_instance, BUFFER_SIZE);

    arm_fir_init_q15(&filter, NTAPS, coefficients, filterState, BUFFER_SIZE);
}

void mainloop( void )
{
    // static uint32_t counter = 0;
    // char buffer[16];
    //
    // // Clear display
    // SSD1306_Clear();
    //
    // // Draw rectangle border
    // SSD1306_DrawRectangle( 0, 0, 101, 63, SSD1306_COLOR_WHITE );
    //
    // // Display counter
    // SSD1306_GotoXY( 10, 20 );
    // sprintf(buffer, "%lu", counter);
    // SSD1306_Puts( buffer, &Font_16x26, SSD1306_COLOR_WHITE );
    //
    // // Update screen
    // SSD1306_UpdateScreen();
    //
    // // Increment counter
    // counter++;
    
    // HAL_GPIO_TogglePin( GPIOB, GPIO_PIN_3 );
    if (fft_data_request == 1) return;

    arm_cmplx_mag_f32(outputFFT, magFFT, BUFFER_SIZE >> 1);

    arm_rfft_fast_f32(&fft_instance, inputFFT, outputFFT, 0);
    for (uint16_t i = 0; i < N_PLOT; i++) {
        int16_t y = (int16_t)(-8.686 * log(magFFT[i]) + 42.1);
        // int16_t y = (int16_t)( magFFT[i] );
        if (y > 59) {
            y = 59;
        }
        if (y < 0) {
            y = 0;
        }
        SSD1306_DrawLine(i + 1, 61, i + 1, y + 2, SSD1306_COLOR_WHITE);
        if (y > 0) {
            SSD1306_DrawLine(i + 1, 2, i + 1, y + 1, SSD1306_COLOR_BLACK);
        }
    }
    SSD1306_UpdateScreen();
    fft_data_request = 1;
    // HAL_Delay( 500 );
}

void process_data( int16_t* saiRxBuffer, int16_t* saiTxBuffer )
{
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
    // HAL_GPIO_WritePin( GPIOB, GPIO_PIN_3, GPIO_PIN_SET );
    // arm_fir_q15(&filter, inputSignalLeft, outputSignalLeft, BUFFER_SIZE);
    // HAL_GPIO_WritePin( GPIOB, GPIO_PIN_3, GPIO_PIN_RESET );

    if (fft_data_request) {
        arm_q15_to_float(inputSignalRight, inputFFT, BUFFER_SIZE);
        fft_data_request = 0;
    }

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
