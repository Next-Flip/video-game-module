#pragma once
#include <pico/stdlib.h>
#include <FreeRTOS.h>
#include <task.h>

#include "frame.h"

typedef union __attribute__((packed)) {
    struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
    uint32_t value : 24;
} RgbColor;

typedef enum {
    ScreenColorModeDefault,
    ScreenColorModeCustom,
    ScreenColorModeRainbow,
    _ScreenColorModeRgbBacklight, // FW will replace this with backlight mode
    ScreenColorModeCount,
} ScreenColorMode;

typedef union __attribute__((packed)) {
    struct {
        ScreenColorMode mode;
        RgbColor rgb;
    };
    uint32_t value;
} ScreenFrameColor;

typedef struct {
    TaskHandle_t thread;
    size_t current_color_index;
    uint8_t totalSteps;
    uint8_t currentStep;
    void (*set_color)(uint16_t color);
} State;

extern State bg_state;

extern State fg_state;

uint16_t rgb888_to_rgb565(RgbColor rgb);

void start_rainbow_mode(State* s);

void stop_rainbow_mode(State* s);
