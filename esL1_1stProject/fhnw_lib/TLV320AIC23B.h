/*
 * TLV320AIC23B.h
 *
 *  Created on: 20.10.2021
 *      Author: marku
 */

#ifndef INC_TLV320AIC23B_H_
#define INC_TLV320AIC23B_H_

#include <stdint.h>

#define CODEC_SAMPLE_RATE 48000

#define TLV320_ADDR 0x1A
//#define TLV320_ADDR 0x1B
#define TLV320_NUM_REGS 10

#define TLV320_LEFT_IN_VOL_REG 0x00
#define TLV320_RIGHT_IN_VOL_REG 0x01
#define TLV320_LEFT_HP_VOL_REG 0x02
#define TLV320_RIGHT_HP_VOL_REG 0x03
#define TLV320_ANALOG_AUDIO_PATH_REG 0x04
#define TLV320_DIGITAL_AUDIO_PATH_REG 0x05
#define TLV320_POWER_DOWN_REG 0x06
#define TLV320_DIGITAL_AUDIO_IF_FORMAT_REG 0x07
#define TLV320_SAMPLE_RATE_CTRL_REG 0x08
#define TLV320_DIGITAL_IF_ACTIVATION_REG 0x09
#define TLV320_RESET_REG 0x0F

typedef enum {
	LINE, MIC,
} input_t;

void codec_write(uint8_t, uint16_t);
void codec_init();
void codec_setInput(input_t);

#endif /* INC_TLV320AIC23B_H_ */

