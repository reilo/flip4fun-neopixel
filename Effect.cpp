#include "Flip4fun_NeoPixel.h"

/*****************************************************************************/

Effect::Effect(bool autoStop) : m_autoStop(autoStop), m_running(false) {}

void Effect::start(unsigned long millis) {
  m_running = true;
  m_prevMillis = millis;
}

void Effect::stop() { m_running = false; }

bool Effect::running() { return m_running; }

/*****************************************************************************/

SingleColorEffect::SingleColorEffect(uint32_t color, bool autoStop)
    : Effect(autoStop), m_color(color) {}

uint32_t SingleColorEffect::getColor() { return m_running ? m_color : 0; }

void SingleColorEffect::setColor(uint32_t color) { m_color = color; }

/*****************************************************************************/

MovingEffect::MovingEffect(uint8_t size, bool autoStop)
    : Effect(autoStop), m_size(size), m_offset(0) {}

uint8_t MovingEffect::getOffset() { return m_offset; }

/*****************************************************************************/

Wave::Wave(uint32_t period, uint32_t color)
    : SingleColorEffect(color, false), Effect(false), m_period(period),
      m_value(0), m_rising(true) {}

void Wave::start(unsigned long millis) {
  SingleColorEffect::start(millis);
  m_value = 0;
  m_rising = true;
}

void Wave::update(unsigned long millis) {
  if (m_running) {
    if (millis - m_prevMillis > m_period / (MAX_COLOR + 1) / 4) {
      m_prevMillis = millis;
      if (m_rising) {
        if (m_value >= MAX_COLOR) {
          m_value--;
          m_rising = false;
        } else {
          m_value++;
        }
      } else {
        if (m_value <= 0) {
          m_value++;
          m_rising = true;
        } else {
          m_value--;
        }
      }
    }
  } else {
    m_value = 0;
  }
}

uint32_t Wave::getColor() {
  uint32_t color;
  if (m_running) {
    uint8_t rgb[3];
    RGB(m_color, rgb);
    for (int i = 0; i < 3; i++) {
      rgb[i] = rgb[i] * m_value / MAX_COLOR;
    }
    color = Color(rgb);
  }
  return color;
}

/*****************************************************************************/

Flash::Flash(uint32_t period, uint32_t color)
    : SingleColorEffect(color, true), Effect(true), m_period(period),
      m_on(false) {}

void Flash::update(unsigned long millis) {
  if (m_running) {
    m_running = (millis - m_prevMillis < m_period);
  }
}

/*****************************************************************************/

FlashComplex::FlashComplex(uint16_t nIntervals, uint16_t *intervals,
                           uint32_t color)
    : SingleColorEffect(color, true), Effect(true), m_nIntervals(nIntervals),
      m_intervals(intervals), m_on(false) {}

void FlashComplex::start(unsigned long millis) {

  m_currentInterval = 0;
  m_on = false;
  SingleColorEffect::start(millis);
}

void FlashComplex::update(unsigned long millis) {

  if (m_running) {
    if (m_currentInterval == m_nIntervals) {
      m_running = false;
    } else {
      bool expired = (millis - m_prevMillis >= m_intervals[m_currentInterval]);
      m_on = (m_currentInterval % 2 == 0) ? !expired : expired;
      if (expired) {
        m_prevMillis = millis;
        m_currentInterval++;
      }
    }
  }
}

uint32_t FlashComplex::getColor() { return m_running && m_on ? m_color : 0; }

/*****************************************************************************/

Racer::Racer(uint8_t size, uint32_t color, unsigned long period)
    : MovingEffect(size, true), SingleColorEffect(color, true), Effect(true),
      m_period(period) {}

void Racer::update(unsigned long millis) {
  if (m_running) {
    if (m_offset >= m_size) {
      m_running = false;
    } else {
      if (millis - m_prevMillis > m_period) {
        m_prevMillis = millis;
        m_offset++;
      }
    }
  }
}