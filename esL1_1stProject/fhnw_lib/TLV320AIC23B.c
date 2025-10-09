#include "TLV320AIC23B.h"
#include "stm32l4xx_hal.h"
#include <stdint.h>

extern I2C_HandleTypeDef hi2c1;

/**************************************************************************
 * Global Definitions
 ***************************************************************************/

const uint16_t TLV320_init_data[ 10 ] = {

    // *** Define belwo the value of each register ***
    ( 0b11011 ) | ( 0 << TLV320_LEFT_IN_LIM_Pos ),   // Reg 00: Left Line In (6dB, mute OFF)
    ( 0b11011 ) | ( 0 << TLV320_RIGHT_IN_RIM_Pos ),  // Reg 01: Right Line In (6dB, mute OFF)
    ( 0b1111001 ),                                   // Reg 02: Left Headphone out (-12dB)
    ( 0b1111001 ),                                   // Reg 03: Right Headphone out (-12dB)
    ( 1 << TLV320_ANALOG_AUDIO_PATH_DAC_Pos )
        | ( 1 << TLV320_ANALOG_AUDIO_PATH_MICM_Pos ),  // Reg 04: Analog Audio Path Control (DAC
                                                       // sel, Mute Mic)
    0x0000,                                            // Reg 05: Digital Audio Path Control
    0x0000,                                            // Reg 06: Power Down Control (All ON)
    ( 1 << TLV320_DIGITAL_AUDIO_IF_FORMAT_FOR1_Pos ),  // Reg 07: Digital Audio Interface Format
                                                       // (I2S, 16-bit, slave)
#if CODEC_SAMPLE_RATE == 96000
    ( 0b0111 << TLV320_SAMPLE_RATE_CTRL_SR0_Pos )
        | ( 0 << TLV320_SAMPLE_RATE_CTRL_BOSR_Pos ),  // Reg 08: Sampling Control (Clock Out divided
                                                      // by 1, 256x, 96k ADC/DAC)
#elif CODEC_SAMPLE_RATE == 48000
    0x0000,  // Reg 08: Sampling Control (Clock Out divided by 1, 256x, 48k ADC/DAC)
#elif CODEC_SAMPLE_RATE == 32000
    ( 0b0110 << TLV320_SAMPLE_RATE_CTRL_SR0_Pos )
        | ( 0 << TLV320_SAMPLE_RATE_CTRL_BOSR_Pos ),  // Reg 08: Sampling Control (Clock Out divided
                                                      // by 1, 256x, 32k ADC/DAC)
#elif CODEC_SAMPLE_RATE == 8000
    ( 0b0011 << TLV320_SAMPLE_RATE_CTRL_SR0_Pos )
        | ( 0 << TLV320_SAMPLE_RATE_CTRL_BOSR_Pos ),  // Reg 08: Sampling Control (Clock Out divided
                                                      // by 1, 256x, 8k ADC/DAC)
#else
    #error "sample rate must be in {8000, 32000, 48000, 96000}"
#endif
    0x0001  // Reg 09: Active Control
};

void codec_write( uint8_t reg, uint16_t data )
{
    uint8_t wdata[ 2 ];

    // Stuff the output buffer
    wdata[ 0 ] = ( ( reg << 1 ) & 0xFE ) | ( ( data >> 8 ) & 0x01 );
    wdata[ 1 ] = data & 0xff;
    // Send it
    HAL_I2C_Master_Transmit( &hi2c1, ( TLV320_ADDR << 1 ), wdata, 2, 1000 );
}

void codec_init()
{
    int i;
    // Reset
    codec_write( TLV320_RESET_REG, 0 );
    HAL_Delay( 10 );  // wait 10 ms
    // Configure registers
    for ( i = 0; i < TLV320_NUM_REGS; i++ )
    {
        codec_write( i, TLV320_init_data[ i ] );
    }
    codec_setInput( LINE );
}

void codec_setInput( input_t in )
{
    switch ( in )
    {
        case LINE :
            // Reg 04: Analog Audio Path Control (DAC sel, Mute Mic)
            codec_write( TLV320_ANALOG_AUDIO_PATH_REG, 0x012 );
            break;

        case MIC :
        default :
            // Reg 04: Analog Audio Path Control (DAC sel, Mic, 20dB boost)
            codec_write( TLV320_ANALOG_AUDIO_PATH_REG, 0x015 );
            break;
    }
}
