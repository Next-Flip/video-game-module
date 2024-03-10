#pragma once

typedef enum {
    VgmColorModeDefault,
    VgmColorModeCustom,
    VgmColorModeRainbow,
    VgmColorModeRgbBacklight,
    VgmColorModeCount,
} VgmColorMode;

void start_rainbow_mode();

void stop_rainbow_mode();
