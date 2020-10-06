#ifndef FLIP4FUN_NEOPIXEL_H
#define FLIP4FUN_NEOPIXEL_H

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#include <Base.h>
#include <Effect.h>
#include <Trigger.h>

class Flip4fun_NeoPixel {

protected:
  Adafruit_NeoPixel *m_strip;
  uint32_t m_n;
  uint32_t m_colors[MAX_LEDS];
  Effect *m_effects[MAX_EFFECTS];
  uint16_t m_nEffects;

public:
  Flip4fun_NeoPixel(uint16_t pin = 13, uint16_t n = 1,
                    uint16_t brightness = MAX_COLOR);
  ~Flip4fun_NeoPixel();
  uint16_t add(Effect *effect);
  void begin();
  void beginEffect(uint16_t id);
  void endEffect(uint16_t id);
  void update(unsigned long millis);
};

#endif
