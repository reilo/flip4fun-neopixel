#include "Flip4fun_NeoPixel.h"

SingleColorEffect::SingleColorEffect(uint32_t color, bool autoStop)
    : m_color(color), m_autoStop(autoStop), m_running(false) {}

void SingleColorEffect::start(unsigned long millis) {
  m_running = true;
  m_prevMillis = millis;
}

Wave::Wave(uint32_t period, uint32_t color)
    : SingleColorEffect(color, false), m_period(period), m_value(0), m_rising(true) {}

void Wave::start(unsigned long millis) {
  m_value = 0;
  m_rising = true;
  SingleColorEffect::start(millis);
}

uint32_t Wave::update(unsigned long millis) {

  if (!m_running) {
    return 0;
  }

  bool update = false;

  if (millis - m_prevMillis > m_period / (MAX_COLOR + 1) / 4) {
    m_prevMillis = millis;
    update = true;
  }

  if (update) {
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

  uint8_t rgb[3];
  RGB(m_color, rgb);
  for (int i = 0; i < 3; i++) {
    rgb[i] = rgb[i] * m_value / MAX_COLOR;
  }
  uint32_t color = Color(rgb);

  return color;
}

Flash::Flash(uint32_t period, uint32_t color)
    : SingleColorEffect(color ,true), m_period(period) {}

uint32_t Flash::update(unsigned long millis) {

  bool isOn = false;
  uint32_t color = 0;

  if (m_running) {
    isOn = (millis - m_prevMillis < m_period);
  }

  if (isOn) {
    color = m_color;
  } else {
    m_running = false;
  }

  return color;
}

FlashComplex::FlashComplex(uint16_t nIntervals, uint16_t *intervals,
                           uint32_t color)
    : SingleColorEffect(color, true), m_nIntervals(nIntervals),
      m_intervals(intervals) {}

void FlashComplex::start(unsigned long millis) {

  m_currentInterval = 0;
  SingleColorEffect::start(millis);
}

uint32_t FlashComplex::update(unsigned long millis) {

  bool isOn = false;

  if (!m_running) {
    return 0;
  }

  if (m_currentInterval == m_nIntervals) {
      m_running = false;
      return 0;
  }

  bool expired = (millis - m_prevMillis >= m_intervals[m_currentInterval]);
  isOn = (m_currentInterval % 2 == 0) ? !expired : expired;

  if (expired) {
    m_prevMillis = millis;
    m_currentInterval++;
  }

  if (m_currentInterval == m_nIntervals) {
    return 0;
  }

  if (isOn) {
    return m_color;
  }

  return 0;
}
