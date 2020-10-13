#include "Flip4fun_NeoPixel.h"

Switcher::Switcher() {}

Switcher::~Switcher() {}

void Switcher::start(unsigned long millis) { m_startMillis = millis; }

bool Switcher::read(unsigned long millis, bool isOn) { return isOn; }

Blink::Blink(uint16_t minPeriod, uint16_t maxPeriod)
    : Switcher(), m_minPeriod(minPeriod), m_maxPeriod(maxPeriod),
      m_nextPeriod(0), m_running(false) {}

bool Blink::read(unsigned long millis, bool isOn) {

  if (!m_running) {
    m_running = true;
    m_startMillis = millis;
    m_currentState = isOn;
    m_nextPeriod = 0;
    m_periods[0] = m_periods[1] = 0;
  } else if (isOn != m_currentState) {
    m_periods[m_nextPeriod] = millis - m_startMillis;
    m_nextPeriod = (m_nextPeriod + 1) % 2;
    m_currentState = isOn;
    m_startMillis = millis;
  } else if (millis - m_startMillis > m_maxPeriod) {
    return false;
  }
  return m_periods[0] >= m_minPeriod && m_periods[0] <= m_maxPeriod &&
         m_periods[1] >= m_minPeriod && m_periods[1] <= m_maxPeriod;
}