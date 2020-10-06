#include "Effect.h"
#include "Base.h"

Effect::Effect(uint16_t n)
    : m_n(n), m_prevMillis(0), m_running(false), m_beginRequest(false),
      m_endRequest(false) {}

Effect::~Effect() {}

void Effect::begin() { m_beginRequest = true; }

void Effect::end() { m_endRequest = true; }

Wave::Wave(uint16_t n, uint32_t period, uint32_t color)
    : Effect(n), m_period(period), m_color(color), m_currVal(0),
      m_isRising(true) {}

void Wave::update(unsigned long millis, uint32_t colors[]) {

  if (m_beginRequest) {
    m_running = true;
    m_beginRequest = false;
  } else if (!m_running) {
    return;
  }

  bool update = false;

  if (millis - m_prevMillis > m_period / (MAX_COLOR + 1) / 2) {
    m_prevMillis = millis;
    update = true;
  }

  if (update) {
    if (m_isRising) {
      if (m_currVal >= MAX_COLOR) {
        m_currVal--;
        m_isRising = false;
      } else {
        m_currVal++;
      }
    } else {
      if (m_currVal <= 0) {
        m_currVal++;
        m_isRising = true;
      } else {
        m_currVal--;
      }
    }
  }

  uint8_t rgb[3];
  RGB(m_color, rgb);
  for (int i = 0; i < 3; i++) {
    rgb[i] = rgb[i] * m_currVal / MAX_COLOR;
  }
  uint32_t color = Color(rgb);

  for (int i = 0; i < m_n; i++) {
    colors[i] = color;
  }

  if (m_endRequest && m_currVal == 0) {
    m_running = m_endRequest = false;
  }
}

Flash::Flash(uint16_t n, uint32_t period, uint32_t color)
    : Effect(n), m_period(period), m_color(color) {}

void Flash::update(unsigned long millis, uint32_t colors[]) {

  bool isOn = false;

  if (m_beginRequest) {
    m_beginRequest = false;
    m_running = true;
    m_prevMillis = millis;
  }

  if (m_running) {
    isOn = (millis - m_prevMillis < m_period);
  }

  if (isOn) {
    for (int i = 0; i < m_n; i++) {
      colors[i] = m_color;
    }
  } else {
    if (m_endRequest) {
      m_running = m_endRequest = false;
    }
  }
}

FlashComplex::FlashComplex(uint16_t n, uint16_t len, uint16_t *intervals,
                           uint32_t color)
    : Effect(n), m_len(len), m_intervals(intervals), m_color(color) {}

void FlashComplex::update(unsigned long millis, uint32_t colors[]) {

  bool isOn = false;

  if (m_beginRequest) {
    m_beginRequest = false;
    m_running = true;
    m_prevMillis = millis;
    m_currentInterval = 0;
  }

  if (!m_running) {
    return;
  }

  if (m_currentInterval == m_len) {
    if (m_endRequest) {
      m_running = m_endRequest = false;
    }
    return;
  }

  bool expired = (millis - m_prevMillis >= m_intervals[m_currentInterval]);
  isOn = (m_currentInterval % 2 == 0) ? !expired : expired;

  if (expired) {
    m_prevMillis = millis;
    m_currentInterval++;
  }

  if (m_currentInterval == m_len) {
    return;
  }

  if (isOn) {
    for (int i = 0; i < m_n; i++) {
      colors[i] = m_color;
    }
  }
}

Racer::Racer(uint16_t n, uint32_t period, uint32_t color)
    : Effect(n), m_period(period), m_color(color), m_pos(0) {}

void Racer::update(unsigned long millis, uint32_t colors[]) {

  bool isOn = false;

  if (m_beginRequest) {
    m_beginRequest = false;
    m_running = true;
    m_pos = 0;
    m_prevMillis = millis;
  }

  if (m_running) {
    if (millis - m_prevMillis >= m_period) {
      m_pos++;
      m_prevMillis = millis;
    }
    isOn = (m_pos < m_n);
  }

  if (isOn) {
    colors[m_pos] = m_color;
  } else {
    if (m_endRequest) {
      m_running = m_endRequest = false;
    }
  }
}
