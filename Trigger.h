#ifndef FLIP4FUN_TRIGGER_H
#define FLIP4FUN_TRIGGER_H

#include <Arduino.h>

class Trigger {
protected:
  unsigned long m_startMillis;

public:
  Trigger();
  ~Trigger();
  virtual void start(unsigned long millis);
  virtual bool read(unsigned long millis);
};

/*****************************************************************************/

class Tick : public Trigger {
protected:
  unsigned long m_period;

public:
  Tick(unsigned long period);
  bool read(unsigned long millis) override;
};

/*****************************************************************************/

class TickRandom : public Tick {
protected:
  unsigned long m_minPeriod;
  unsigned long m_maxPeriod;
  void randomize();

public:
  TickRandom(unsigned long minPeriod, unsigned long maxPeriod);
  void start(unsigned long millis) override;
  bool read(unsigned long millis) override;
};

#endif