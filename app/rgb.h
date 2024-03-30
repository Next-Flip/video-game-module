#pragma once
#include <pico/stdlib.h>

typedef enum {
    VgmColorModeDefault,
    VgmColorModeCustom,
    VgmColorModeRainbow,
    VgmColorModeRgbBacklight,
    VgmColorModeCount,
} VgmColorMode;

typedef union __attribute__((packed)) {
    uint32_t value : 24;
    struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
} RgbColor;

typedef union __attribute__((packed)) {
    uint32_t value;
    struct {
        VgmColorMode mode : 8;
        RgbColor rgb;
    };
} RgbColorTransmit;

typedef union __attribute__((packed)) {
    uint32_t value : 24;
    struct {
        uint8_t h;
        uint8_t s;
        uint8_t v;
    };
} HsvColor;

typedef union __attribute__((packed)) {
    uint16_t value;
    struct {
        uint8_t b : 5;
        uint8_t g : 6;
        uint8_t r : 5;
    };
} Rgb565Color;

uint16_t rgb888_to_rgb565(RgbColor rgb);

void start_rainbow_mode();

void stop_rainbow_mode();
