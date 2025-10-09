/*
 * TLV320AIC23B.h
 *
 *  Created on: 20.10.2021
 *      Author: marku
 */

#ifndef INC_TLV320AIC23B_H_
#define INC_TLV320AIC23B_H_

#include <stdint.h>

#define CODEC_SAMPLE_RATE                         48000

#define TLV320_ADDR                               0x1A
// #define TLV320_ADDR 0x1B
#define TLV320_NUM_REGS                           10

#define TLV320_LEFT_IN_VOL_REG                    0x00
#define TLV320_RIGHT_IN_VOL_REG                   0x01
#define TLV320_LEFT_HP_VOL_REG                    0x02
#define TLV320_RIGHT_HP_VOL_REG                   0x03
#define TLV320_ANALOG_AUDIO_PATH_REG              0x04
#define TLV320_DIGITAL_AUDIO_PATH_REG             0x05
#define TLV320_POWER_DOWN_REG                     0x06
#define TLV320_DIGITAL_AUDIO_IF_FORMAT_REG        0x07
#define TLV320_SAMPLE_RATE_CTRL_REG               0x08
#define TLV320_DIGITAL_IF_ACTIVATION_REG          0x09
#define TLV320_RESET_REG                          0x0F

/* LEFT_IN_REG bit definitions */
/*LRS Left/right line simultaneous volume/mute update
Simultaneous update 0 = Disabled 1 = Enabled
LIM Left line input mute 0 = Normal 1 = Muted
LIV[4:0] Left line input volume control (10111 = 0 dB default)
11111 = +12 dB down to 00000 = –34.5 dB in 1.5-dB steps
*/
#define TLV320_LEFT_IN_LRS_Pos                    8
#define TLV320_LEFT_IN_LIM_Pos                    7
#define TLV320_LEFT_IN_LIV0_Pos                   0

/* RIGHT_IN_REG bit definitions */
#define TLV320_RIGHT_IN_RLS_Pos                   8
#define TLV320_RIGHT_IN_RIM_Pos                   7
#define TLV320_RIGHT_IN_RIV0_Pos                  0

/* LEFT_HP_REG bit definitions */
/*LRS Left/right headphone channel simultaneous volume/mute update
Simultaneous update 0 = Disabled 1 = Enabled
LZC Left-channel zero-cross detect
Zero-cross detect 0 = Off 1 = On
LHV[6:0] Left Headphone volume control (1111001 = 0 dB default)
1111111 = +6 dB, 79 steps between +6 dB and −73 dB (mute), 0110000 = −73 dB (mute),
any thing below 0110000 does nothing − you are still muted*/
#define TLV320_LEFT_HP_LRS_Pos                    8
#define TLV320_LEFT_HP_LZC_Pos                    7
#define TLV320_LEFT_HP_LHV0_Pos                   0

/* RIGHT_HP_REG bit definitions */
#define TLV320_RIGHT_HP_RLS_Pos                   8
#define TLV320_RIGHT_HP_RZC_Pos                   7
#define TLV320_RIGHT_HP_RHV0_Pos                  0

/* ANALOG_AUDIO_PATH_REG bit definitions */
/*
STA[2:0] and STE
    STE STA2 STA1 STA0 ADDED SIDETONE
    1    1     X    X    0 dB
    1    0     0    0    −6 dB
    1    0     0    1    −9 dB
    1    0     1    0    −12 dB
    1    0     1    1    −18 dB
    0    X     X    X    Disabled
DAC DAC select 0 = DAC off 1 = DAC selected
BYP Bypass 0 = Disabled 1 = Enabled
3−4
INSEL Input select for ADC 0 = Line 1 = Microphone
MICM Microphone mute 0 = Normal 1 = Muted
MICB Microphone boost 0=dB 1 = 20dB
 */
#define TLV320_ANALOG_AUDIO_PATH_STA2_Pos         8
#define TLV320_ANALOG_AUDIO_PATH_STA1_Pos         7
#define TLV320_ANALOG_AUDIO_PATH_STA0_Pos         6
#define TLV320_ANALOG_AUDIO_PATH_STE_Pos          5
#define TLV320_ANALOG_AUDIO_PATH_DAC_Pos          4
#define TLV320_ANALOG_AUDIO_PATH_BYP_Pos          3
#define TLV320_ANALOG_AUDIO_PATH_INSEL_Pos        2
#define TLV320_ANALOG_AUDIO_PATH_MICM_Pos         1
#define TLV320_ANALOG_AUDIO_PATH_MICB_Pos         0

/* DIGITAL_AUDIO_PATH_REG bit definitions */
/*
DACM DAC soft mute 0 = Disabled 1 = Enabled
DEEMP[1:0] De-emphasis control 00 = Disabled 01 = 32 kHz 10 = 44.1 kHz 11 = 48 kHz
ADCHP ADC high-pass filter 1 = Disabled 0 = Enabled*/
#define TLV320_DIGITAL_AUDIO_PATH_DACM_Pos        3
#define TLV320_DIGITAL_AUDIO_PATH_DEEMP1_Pos      2
#define TLV320_DIGITAL_AUDIO_PATH_DEEMP0_Pos      1
#define TLV320_DIGITAL_AUDIO_PATH_ADCHP_Pos       0

/* POWER_DOWN_REG bit definitions */
/*
OFF Device power 0 = On 1 = Off
CLK Clock 0 = On 1 = Off
OSC Oscillator 0 = On 1 = Off
OUT Outputs 0 = On 1 = Off
DAC DAC 0 = On 1 = Off
ADC ADC 0 = On 1 = Off
MIC Microphone input 0 = On 1 = Off
LINE Line input 0 = On 1 = Off
*/
#define TLV320_POWER_DOWN_OFF_Pos                 7
#define TLV320_POWER_DOWN_CLK_Pos                 6
#define TLV320_POWER_DOWN_OSC_Pos                 5
#define TLV320_POWER_DOWN_OUT_Pos                 4
#define TLV320_POWER_DOWN_DAC_Pos                 3
#define TLV320_POWER_DOWN_ADC_Pos                 2
#define TLV320_POWER_DOWN_MIC_Pos                 1
#define TLV320_POWER_DOWN_LINE_Pos                0

/* DIGITAL_AUDIO_IF_FORMAT_REG bit definitions */
/*
MS Master/slave mode 0 = Slave 1 = Master
LRSWAP DAC left/right swap 0 = Disabled 1 = Enabled
LRP DAC left/right phase 0 = Right channel on, LRCIN high
1 = Right channel on, LRCIN low
DSP mode
1 = MSB is available on 2nd BCLK rising edge after LRCIN rising edge
0 = MSB is available on 1st BCLK rising edge after LRCIN rising edge
IWL[1:0] Input bit length 00 = 16 bit 01 = 20 bit 10 = 24 bit 11 = 32 bit
FOR[1:0] Data format 11 = DSP format, frame sync followed by two data words
10 = I2S format, MSB first, left – 1 aligned
01 = MSB first, left aligned
00 = MSB first, right aligned
*/
#define TLV320_DIGITAL_AUDIO_IF_FORMAT_MS_Pos     6
#define TLV320_DIGITAL_AUDIO_IF_FORMAT_LRSWAP_Pos 5
#define TLV320_DIGITAL_AUDIO_IF_FORMAT_LRP_Pos    4
#define TLV320_DIGITAL_AUDIO_IF_FORMAT_IWL1_Pos   3
#define TLV320_DIGITAL_AUDIO_IF_FORMAT_IWL0_Pos   2
#define TLV320_DIGITAL_AUDIO_IF_FORMAT_FOR1_Pos   1
#define TLV320_DIGITAL_AUDIO_IF_FORMAT_FOR0_Pos   0

/* SAMPLE_RATE_CTRL_REG bit definitions */
/*
CLKIN Clock input divider 0 = MCLK 1 = MCLK/2
CLKOUT Clock output divider 0 = MCLK 1 = MCLK/2
SR[3:0] Sampling rate control
BOSR Base oversampling rate
USB mode: 0 = 250 fs 1 = 272 fs
Normal mode: 0 = 256 fs 1 = 384 fs
USB/Normal Clock mode select: 0 = Normal 1 = USB
*/
#define TLV320_SAMPLE_RATE_CTRL_CLKOUT_Pos        7
#define TLV320_SAMPLE_RATE_CTRL_CLKIN_Pos         6
#define TLV320_SAMPLE_RATE_CTRL_SR3_Pos           5
#define TLV320_SAMPLE_RATE_CTRL_SR2_Pos           4
#define TLV320_SAMPLE_RATE_CTRL_SR1_Pos           3
#define TLV320_SAMPLE_RATE_CTRL_SR0_Pos           2
#define TLV320_SAMPLE_RATE_CTRL_BOSR_Pos          1
#define TLV320_SAMPLE_RATE_CTRL_USB_Pos           0

/* DIGITAL_IF_ACTIVATION_REG bit definitions */
/*
ACT Activate interface 0 = Inactive 1 = Active
*/
#define TLV320_DIGITAL_IF_ACTIVATION_ACT_Pos      0

typedef enum
{
    LINE,
    MIC,
} input_t;

void codec_write( uint8_t, uint16_t );

void codec_init();

void codec_setInput( input_t );

#endif /* INC_TLV320AIC23B_H_ */
