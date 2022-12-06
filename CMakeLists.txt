cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

project(PiStrument VERSION 1.0.0)
pico_sdk_init()
 
add_executable(PiStrument
  src/main.c
  src/devices/audio_pio.c
  src/devices/audio_data.c
)

pico_generate_pio_header(PiStrument ${CMAKE_CURRENT_LIST_DIR}/src/devices/audio_pio.pio)

target_link_libraries(PiStrument
  pico_stdlib
  hardware_spi
  hardware_i2c
  hardware_pwm
  hardware_adc
  hardware_pio
  hardware_dma
)
 
pico_enable_stdio_usb(PiStrument 1)
pico_enable_stdio_uart(PiStrument 1)
pico_add_extra_outputs(PiStrument)
