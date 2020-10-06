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

class Oscillation : public Effect {
protected:
  uint32_t m_period;
  uint32_t m_color;
  uint32_t m_currVal;
  bool m_isRising;

public:
  Oscillation(uint16_t n, uint32_t period, uint32_t color);
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

class Arrow : public Effect {
protected:
  uint16_t m_period;
  uint32_t m_color;
  uint16_t m_pos;

public:
  Arrow(uint16_t n, uint32_t period, uint32_t color);
  void begin() override;
  void update(unsigned long millis, uint32_t colors[]) override;
};

#endif
