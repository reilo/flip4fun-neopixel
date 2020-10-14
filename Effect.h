#ifndef FLIP4FUN_EFFECT_H
#define FLIP4FUN_EFFECT_H

#include <Arduino.h>

/*****************************************************************************/

class Effect {
protected:
  bool m_autoStop;
  unsigned long m_prevMillis;
  bool m_running;

public:
  Effect(bool autoStop);
  virtual void start(unsigned long millis);
  virtual void update(unsigned long millis);
  virtual void stop();
  virtual bool running();
};

/*****************************************************************************/

class SingleColorEffect : public Effect {
protected:
  uint32_t m_color;

public:
  SingleColorEffect(uint32_t color, bool autoStop);
  ~SingleColorEffect();
  virtual uint32_t getColor();
  virtual void setColor(uint32_t color);
};

/*****************************************************************************/

class Wave : public SingleColorEffect {
protected:
  uint32_t m_period;
  uint32_t m_value;
  bool m_rising;

public:
  Wave(uint32_t period, uint32_t color);
  void start(unsigned long millis) override;
  void update(unsigned long millis) override;
  uint32_t getColor() override;
};

/*****************************************************************************/

class Flash : public SingleColorEffect {
protected:
  uint16_t m_period;
  bool m_on;

public:
  Flash(uint32_t period, uint32_t color);
  void update(unsigned long millis) override;
};

/*****************************************************************************/

class FlashComplex : public SingleColorEffect {
protected:
  uint16_t m_nIntervals;
  uint16_t *m_intervals;
  uint16_t m_currentInterval;
  bool m_on;

public:
  FlashComplex(uint16_t nIntervals, uint16_t *intervals, uint32_t color);
  void start(unsigned long millis) override;
  void update(unsigned long millis) override;
  uint32_t getColor() override;
};

#endif
