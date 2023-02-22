#ifndef HARDWARE_H
#define HARDWARE_H

#include "analogMicrophone/analog_microphone.h"
#include "buttonMatrix/buttonMatrix.h"
#include "pico/audio_i2s.h"
#include "rotaryEncoder/rotaryEncoder.h"
#include "tftDisplay/st7789.h"
#include "leds/leds.h"

#define PIN_B0 3
#define PIN_B1 4
#define PIN_B2 5
#define PIN_B3 6
#define PIN_B4 7
#define PIN_B5 8
#define PIN_B6 9
#define PIN_B7 10
#define PIN_B8 16
#define PIN_ENCA 27
#define PIN_ENCB 28
#define PIN_ENCBtn 22

#define PIN_LCD_SPI spi1
#define PIN_LCD_SCK 14
#define PIN_LCD_MISO 12
#define PIN_LCD_MOSI 15
#define PIN_LCD_TCS 13
#define PIN_LCD_DC 11

#define PIN_SD_CS 17

#define PIN_LED_SPI spi0
#define PIN_LED_SCK 18
#define PIN_LED_TX 19
#define PIN_LED_LATCH 20
#define PIN_LED8 21
#define LED_LATCH_DELAY_US 5
#define LED_BAUDRATE 11500

#define PIN_I2S_DATA 2
#define PIN_I2S_CLOCK_BASE 0

#define PIN_ADC_MIC 26
#define IN_ADC_MIC 0

#define LCD_WIDTH 240
#define LCD_HEIGHT 320

#define SAMPLES_PER_BUFFER 256

extern st7789_config lcdConfig;
extern analog_microphone_config analogMicConfig;
extern audio_format_t outAudioFormat;
extern audio_buffer_format outProducerFormat;

void initHardware();
void updateHardware();
audio_buffer_pool *initAudioOut();

#endif
