#ifndef FLIP4FUN_BASE_H
#define FLIP4FUN_BASE_H

#define MAX_COLOR 255
#define MAX_LEDS 64
#define MAX_EFFECTS 16

#define RED 0x00ff0000
#define GREEN 0x0000ff00
#define BLUE 0x000000ff
#define CYAN 0x0000ffff
#define MAGENTA 0x00ff00ff
#define YELLOW 0x00ffff00
#define WHITE 0x00ffffff
#define ORANGE 0x00ff7f00

static uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

static uint32_t Color(uint8_t rgb[]) {
  return ((uint32_t)rgb[0] << 16) | ((uint32_t)rgb[1] << 8) | rgb[2];
}

static void RGB(uint32_t color, uint8_t rgb[]) {
  rgb[0] = (uint8_t)((0x00ff0000 & color) >> 16);
  rgb[1] = (uint8_t)((0x0000ff00 & color) >> 8);
  rgb[2] = (uint8_t)(0x000000ff & color);
}

#endif

// Trigger