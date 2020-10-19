#ifndef FLIP4FUN_SWITCH_H
#define FLIP4FUN_SWITCH_H

#include <Arduino.h>

class Switcher {
protected:
  unsigned long m_startMillis;

public:
  Switcher();
  ~Switcher();
  virtual void start(unsigned long millis);
  virtual bool read(unsigned long millis, bool isOn);
};

/*****************************************************************************/

class Blink : public Switcher {
protected:
  uint16_t m_minPeriod;
  uint16_t m_maxPeriod;
  bool m_running;
  uint16_t m_periods[2];
  uint8_t m_nextPeriod;
  bool m_currentState;

public:
  Blink(uint16_t minPeriod, uint16_t maxPeriod);
  void start(unsigned long millis) override;
  bool read(unsigned long millis, bool isOn) override;
};

#endif
