#ifndef FLIP4FUN_EFFECT_H
#define FLIP4FUN_EFFECT_H

#include <Arduino.h>

class SingleColorEffect {
protected:
  uint32_t m_color;
  bool m_autoStop;
  unsigned long m_prevMillis;
  bool m_running;

public:
  SingleColorEffect(uint32_t color, bool autoStop);
  ~SingleColorEffect();
  virtual void start(unsigned long millis);
  virtual uint32_t update(unsigned long millis);
  uint32_t getColor() { return m_color; }
  void setColor(uint32_t color) { m_color = color; }
  virtual void stop() { m_running = false; }
  virtual bool running() { return m_running; }
};

class Wave : public SingleColorEffect {
protected:
  uint32_t m_period;
  uint32_t m_value;
  bool m_rising;

public:
  Wave(uint32_t period, uint32_t color);
  void start(unsigned long millis) override;
  uint32_t update(unsigned long millis) override;
};

class Flash : public SingleColorEffect {
protected:
  uint16_t m_period;

public:
  Flash(uint32_t period, uint32_t color);
  uint32_t update(unsigned long millis) override;
};

class FlashComplex : public SingleColorEffect {
protected:
  uint16_t m_nIntervals;
  uint16_t *m_intervals;
  uint16_t m_currentInterval;

public:
  FlashComplex(uint16_t nIntervals, uint16_t *intervals, uint32_t color);
  void start(unsigned long millis) override;
  uint32_t update(unsigned long millis) override;
};

#endif
