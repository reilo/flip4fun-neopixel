#ifndef FLIP4FUN_EFFECT_H
#define FLIP4FUN_EFFECT_H

#include <Arduino.h>

class Effect {
protected:
  uint16_t m_n;
  unsigned long m_prevMillis;
  bool m_beginRequest;
  bool m_running;
  bool m_endRequest;

public:
  Effect(uint16_t n);
  ~Effect();
  virtual void begin();
  virtual void update(unsigned long millis, uint32_t colors[]);
  virtual void end();
};

class Wave : public Effect {
protected:
  uint32_t m_period;
  uint32_t m_color;
  uint32_t m_currVal;
  bool m_isRising;

public:
  Wave(uint16_t n, uint32_t period, uint32_t color);
  void update(unsigned long millis, uint32_t colors[]) override;
};

class Flash : public Effect {
protected:
  uint16_t m_period;
  uint32_t m_color;

public:
  Flash(uint16_t n, uint32_t period, uint32_t color);
  void update(unsigned long millis, uint32_t colors[]) override;
};

class FlashComplex : public Effect {
protected:
  uint16_t m_len;
  uint16_t *m_intervals;
  uint32_t m_color;
  uint16_t m_currentInterval;

public:
  FlashComplex(uint16_t n, uint16_t len, uint16_t *intervals, uint32_t color);
  void update(unsigned long millis, uint32_t colors[]) override;
};

class Racer : public Effect {
protected:
  uint16_t m_period;
  uint32_t m_color;
  uint16_t m_pos;

public:
  Racer(uint16_t n, uint32_t period, uint32_t color);
  void update(unsigned long millis, uint32_t colors[]) override;
};

#endif
