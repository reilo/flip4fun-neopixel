#include "Flip4Fun_NeoPixel.h"

Flip4fun_NeoPixel::Flip4fun_NeoPixel(uint16_t pin, uint16_t n,
                                     uint16_t brightness)
    : m_n(n), m_nEffects(0) {
  m_strip = new Adafruit_NeoPixel(n, pin, NEO_GRB + NEO_KHZ800);
  m_strip->setBrightness(brightness);
}

Flip4fun_NeoPixel::~Flip4fun_NeoPixel() {}

uint16_t Flip4fun_NeoPixel::add(Effect *effect) {
  m_effects[m_nEffects] = effect;
  return m_nEffects++;
}

void Flip4fun_NeoPixel::begin() {
  for (int i = 0; i < m_n; i++) {
    m_colors[i] = 0;
  }
  m_strip->begin();
  m_strip->show();
}

void Flip4fun_NeoPixel::beginEffect(uint16_t id) { m_effects[id]->begin(); }

void Flip4fun_NeoPixel::endEffect(uint16_t id) { m_effects[id]->end(); }

void Flip4fun_NeoPixel::update(unsigned long millis) {
  for (int i = 0; i < m_n; i++) {
    m_colors[i] = 0;
  }
  for (int i = 0; i < m_nEffects; i++) {
    Effect *effect = m_effects[i];
    effect->update(millis, m_colors);
  }
  for (int i = 0; i < m_n; i++) {
    m_strip->setPixelColor(i, m_strip->gamma32(m_colors[i]));
  }
  m_strip->show();
}
