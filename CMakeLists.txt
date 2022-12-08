cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
include(pico_extras_import.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(PiStrument VERSION 1.0.0)
pico_sdk_init()

add_executable(PiStrument src/main.cpp src/RotaryEncoder.cpp src/st7789.c src/analog_microphone.c)

target_link_libraries(PiStrument
  pico_stdlib
  hardware_spi
  hardware_i2c
  hardware_pwm
  hardware_adc
  hardware_pio
  hardware_dma
  pico_audio_i2s
)

target_compile_definitions(PiStrument PRIVATE
  PICO_AUDIO_I2S_MONO_INPUT=1
  PICO_AUDIO_DMA_IRQ=1
)

pico_generate_pio_header(PiStrument ${CMAKE_CURRENT_LIST_DIR}/src/pio_rotary_encoder.pio)

pico_enable_stdio_usb(PiStrument 1)
pico_enable_stdio_uart(PiStrument 0)
pico_add_extra_outputs(PiStrument)
