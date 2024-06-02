#pragma once
#include <stdint.h>

#define COLOR_BG 0xFC00
#define COLOR_FG 0x0000

typedef struct {
    const uint8_t data[1024];
} frame_t;

void frame_init();

uint32_t frame_get_clock();

uint32_t frame_get_voltage();

typedef enum {
    OrientationHorizontal = 0,
    OrientationHorizontalFlip = 1,
    OrientationVertical = 2,
    OrientationVerticalFlip = 3,
} Orientation;

void frame_parse_data(uint8_t orientation, const frame_t* frame, uint32_t timeout_ms);

void frame_set_color(uint16_t bg, uint16_t fg);
void frame_set_background(uint16_t bg);
void frame_set_foreground(uint16_t fg);
