#include "rgb.h"

// Define rainbow colors in RGB565 format
static const uint16_t rainbow_colors[] = {
    0xF800, // Red
    0xFC00, // Orange
    0xFFE0, // Yellow
    0x07E0, // Green
    0x001F, // Blue
    0x781F, // Indigo
    0xF81F // Violet
};

static const size_t rainbow_colors_count = sizeof(rainbow_colors) / sizeof(rainbow_colors[0]);

// Function to linearly interpolate between two colors in RGB565 format
uint16_t
    interpolate_color(uint16_t colorStart, uint16_t colorEnd, uint8_t step, uint8_t maxSteps) {
    if(step >= maxSteps) return colorEnd;

    int rStart = (colorStart >> 11) & 0x1F;
    int gStart = (colorStart >> 5) & 0x3F;
    int bStart = colorStart & 0x1F;

    int rEnd = (colorEnd >> 11) & 0x1F;
    int gEnd = (colorEnd >> 5) & 0x3F;
    int bEnd = colorEnd & 0x1F;

    int r = rStart + ((rEnd - rStart) * step / maxSteps);
    int g = gStart + ((gEnd - gStart) * step / maxSteps);
    int b = bStart + ((bEnd - bStart) * step / maxSteps);

    return (uint16_t)((r << 11) | (g << 5) | b);
}

// Modified function to cycle through the rainbow colors for the background with smooth transitions
void cycle_rainbow_background_colors_smooth(State* s) {
    uint16_t currentColor = rainbow_colors[s->current_color_index];
    uint16_t nextColor = rainbow_colors[(s->current_color_index + 1) % rainbow_colors_count];

    uint16_t interpolatedColor =
        interpolate_color(currentColor, nextColor, s->currentStep, s->totalSteps);
    s->set_color(interpolatedColor);

    s->currentStep++;
    if(s->currentStep >= s->totalSteps) {
        s->currentStep = 0;
        s->current_color_index =
            (s->current_color_index + 1) % rainbow_colors_count; // Move to the next color
    }
}

void RainbowBackgroundColorCyclerTask(void* pvParameters) {
    const TickType_t xDelay = 50 / portTICK_PERIOD_MS; // Adjust delay for smoother transitions

    while(1) {
        cycle_rainbow_background_colors_smooth(pvParameters);
        vTaskDelay(xDelay);
    }
}

uint16_t rgb888_to_rgb565(RgbColor rgb) {
    return (((uint16_t)rgb.r & 0xF8) << 8) + (((uint16_t)rgb.g & 0xFC) << 3) +
           ((rgb.b & 0xF8) >> 3);
}

void start_rainbow_mode(State* s) {
    if(s->thread) {
        vTaskResume(s->thread);
        return;
    }
    xTaskCreate(
        RainbowBackgroundColorCyclerTask, "RainbowBackgroundColorCycler", 256, s, 1, &s->thread);
}

void stop_rainbow_mode(State* s) {
    if(s->thread == NULL) return;
    vTaskSuspend(s->thread);
}
