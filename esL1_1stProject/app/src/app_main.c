//
// Created by skohl on 06.10.2025.
//

#include "app_main.h"
#include "ssd1306.h"
#include "fonts.h"
#include "tlv_control.h"

TLV_CTRL_t tlv_ctrl;

void setup(void) {
    SSD1306_Init() ;
    SSD1306_DrawRectangle(0,0,101,63, SSD1306_COLOR_WHITE);
    SSD1306_GotoXY(10,5);
    SSD1306_Puts("FU", &Font_16x26, SSD1306_COLOR_WHITE);
    SSD1306_UpdateScreen();
    
    tlv_ctrl_init(&tlv_ctrl);
}

void mainloop(void) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
    HAL_Delay(100);

}