#include "Flip4fun_NeoPixel.h"

Trigger::Trigger() {}

Trigger::~Trigger() {}

void Trigger::start(unsigned long millis) { m_startMillis = millis; }

/*****************************************************************************/

Tick::Tick(unsigned long period) : Trigger(), m_period(period) {}

bool Tick::read(unsigned long millis) {
  bool triggered = false;
  if (millis - m_startMillis >= m_period) {
    triggered = true;
    m_startMillis = millis;
  }
  return triggered;
}

/*****************************************************************************/

TickRandom::TickRandom(unsigned long minPeriod, unsigned long maxPeriod)
    : Tick(0), m_minPeriod(minPeriod), m_maxPeriod(maxPeriod) {}

void TickRandom::start(unsigned long millis) {
  Tick::start(millis);
  randomize();
}

bool TickRandom::read(unsigned long millis) {
  bool triggered = Tick::read(millis);
  if (triggered) {
    randomize();
  }
  return triggered;
}

void TickRandom::randomize() {
  m_period = rand() % (m_maxPeriod - m_minPeriod) + m_minPeriod;
}